const path = require("path");
const pc = require("picocolors");
const {
  confirm,
  intro,
  outro,
  select,
  spinner,
  text,
  isCancel,
  cancel,
  note,
} = require("@clack/prompts");

const { discoverTemplates, getTemplateById } = require("../templates/discover");
const { copyDir } = require("../lib/copy");
const { ensureEmptyDir, pathExists, removeDir } = require("../lib/fs");

function defaultProjectName() {
  return "my-drogon-service";
}

async function createProject({ projectName, template, force = false, yes = false } = {}) {
  const templates = await discoverTemplates();
  if (templates.length === 0) {
    throw new Error("No templates found under templates/.");
  }

  const templateId = template || templates[0].id;

  const templateInfo = await getTemplateById(templateId);
  if (!templateInfo) {
    const available = templates.map((t) => t.id).join(", ");
    throw new Error(`Unknown template '${templateId}'. Available: ${available}`);
  }

  if (!projectName && yes) {
    projectName = defaultProjectName();
  }

  if (!projectName) {
    intro(`${pc.bold("Create project")} ${pc.dim(`(${templateInfo.id})`)}`);

    const pickedTemplate = await select({
      message: "Choose a template",
      options: templates.map((t) => ({
        value: t.id,
        label: t.id,
        hint: t.description || undefined,
      })),
      initialValue: templateInfo.id,
    });

    if (isCancel(pickedTemplate)) {
      cancel("Aborted.");
      return;
    }

    templateInfo.id = pickedTemplate;

    const name = await text({
      message: "Project name",
      placeholder: defaultProjectName(),
      validate: (value) => {
        if (!value) return "Project name is required";
        if (value.includes(path.sep)) return "Project name must be a single folder name";
        return;
      },
    });

    if (isCancel(name)) {
      cancel("Aborted.");
      return;
    }

    projectName = name;
  }

  const resolvedTemplate = await getTemplateById(templateInfo.id);
  if (!resolvedTemplate) {
    throw new Error(`Template not found: ${templateInfo.id}`);
  }

  const targetDir = path.resolve(process.cwd(), projectName);

  if (await pathExists(targetDir)) {
    if (!force && yes) {
      throw new Error(`Target directory already exists: ${targetDir}. Use --force to overwrite.`);
    }

    if (!force && !yes) {
      note(pc.dim(targetDir), "Target folder exists");
      const ok = await confirm({
        message: "Overwrite the existing folder?",
        initialValue: false,
      });

      if (isCancel(ok) || !ok) {
        cancel("Aborted.");
        return;
      }

      force = true;
    }

    if (force) {
      await removeDir(targetDir);
    }
  }

  await ensureEmptyDir(targetDir);

  const s = spinner();
  s.start(`Copying template ${pc.cyan(resolvedTemplate.id)}…`);

  await copyDir(resolvedTemplate.dir, targetDir, {
    exclude: resolvedTemplate.exclude,
  });

  s.stop("Project created.");

  outro(
    `${pc.green("Success!")} Created ${pc.bold(projectName)} using ${pc.cyan(resolvedTemplate.id)}\n` +
      `${pc.dim("Next:")} cd ${projectName}`
  );
}

module.exports = { createProject };
