const { Command } = require("commander");
const pc = require("picocolors");

const pkg = require("../package.json");

const { runLanding } = require("./ui/landing");
const { createProject } = require("./commands/create");
const { listTemplates } = require("./commands/list");

function run(argv) {
  const program = new Command();

  program
    .name("create-drogon-app")
    .description("Scaffold Drogon (C++) starter projects")
    .version(pkg.version)
    .argument("[projectName]", "Project folder to create")
    .option("-t, --template <template>", "Template name (folder under templates/)")
    .option("-f, --force", "Overwrite target directory if it exists", false)
    .option("-y, --yes", "Skip prompts and use defaults when possible", false)
    .action(async (projectName, options) => {
      if (!projectName) {
        await runLanding();
        return;
      }

      await createProject({
        projectName,
        template: options.template,
        force: options.force,
        yes: options.yes,
      });
    });

  program
    .command("create")
    .description("Create a new project")
    .argument("[projectName]", "Project folder to create")
    .option("-t, --template <template>", "Template name (folder under templates/)")
    .option("-f, --force", "Overwrite target directory if it exists", false)
    .option("-y, --yes", "Skip prompts and use defaults when possible", false)
    .action(async (projectName, options) => {
      await createProject({
        projectName,
        template: options.template,
        force: options.force,
        yes: options.yes,
      });
    });

  program
    .command("list")
    .description("List available templates")
    .action(async () => {
      const templates = await listTemplates();
      if (templates.length === 0) {
        // eslint-disable-next-line no-console
        console.log("No templates found.");
        return;
      }

      // eslint-disable-next-line no-console
      console.log(pc.bold("Available templates:"));
      for (const template of templates) {
        const desc = template.description ? ` - ${template.description}` : "";
        // eslint-disable-next-line no-console
        console.log(`- ${pc.cyan(template.id)}${desc}`);
      }
    });

  program.parseAsync(argv).catch((err) => {
    // eslint-disable-next-line no-console
    console.error(pc.red(err?.message || String(err)));
    process.exitCode = 1;
  });
}

module.exports = { run };
