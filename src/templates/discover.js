const fs = require("fs/promises");
const path = require("path");

const { readJsonIfExists } = require("../lib/fs");

function packageRootFromHere() {
  // src/ -> package root
  return path.resolve(__dirname, "..", "..");
}

function templatesRoot() {
  return path.join(packageRootFromHere(), "templates");
}

async function isDirectory(p) {
  try {
    const st = await fs.stat(p);
    return st.isDirectory();
  } catch {
    return false;
  }
}

function normalizeTemplateId(dirName) {
  return dirName;
}

async function readTemplateMetadata(templateDir) {
  // Optional metadata file for richer UI; safe default if absent.
  // Example templates/<id>/template.json:
  // {"name":"Drogon Starter","description":"...","exclude":["build",".git"]}
  const metadataPath = path.join(templateDir, "template.json");
  const meta = await readJsonIfExists(metadataPath);

  if (!meta) return null;

  return {
    name: typeof meta.name === "string" ? meta.name : undefined,
    description: typeof meta.description === "string" ? meta.description : undefined,
    exclude: Array.isArray(meta.exclude) ? meta.exclude.filter((x) => typeof x === "string") : undefined,
  };
}

async function discoverTemplates() {
  const root = templatesRoot();

  let entries;
  try {
    entries = await fs.readdir(root, { withFileTypes: true });
  } catch {
    return [];
  }

  const templates = [];
  for (const ent of entries) {
    if (!ent.isDirectory()) continue;
    if (ent.name.startsWith(".")) continue;

    const id = normalizeTemplateId(ent.name);
    const dir = path.join(root, ent.name);

    // Skip empty/non-dir just in case
    if (!(await isDirectory(dir))) continue;

    const meta = await readTemplateMetadata(dir);

    templates.push({
      id,
      dir,
      name: meta?.name,
      description: meta?.description,
      exclude: meta?.exclude,
    });
  }

  templates.sort((a, b) => a.id.localeCompare(b.id));
  return templates;
}

async function getTemplateById(templateId) {
  const templates = await discoverTemplates();
  const t = templates.find((x) => x.id === templateId);
  if (!t) return null;

  // Default excludes (can be extended per-template)
  const defaultExclude = [
    ".git",
    "node_modules",
    "build",
    "dist",
    ".cache",
  ];

  const mergedExclude = Array.from(new Set([...(defaultExclude || []), ...(t.exclude || [])]));

  return {
    ...t,
    exclude: mergedExclude,
  };
}

module.exports = {
  discoverTemplates,
  getTemplateById,
};
