const fs = require("fs/promises");
const path = require("path");

async function pathExists(p) {
  try {
    await fs.access(p);
    return true;
  } catch {
    return false;
  }
}

async function ensureDir(p) {
  await fs.mkdir(p, { recursive: true });
}

async function ensureEmptyDir(p) {
  await ensureDir(p);
}

async function removeDir(p) {
  await fs.rm(p, { recursive: true, force: true });
}

async function readJsonIfExists(p) {
  try {
    const raw = await fs.readFile(p, "utf8");
    return JSON.parse(raw);
  } catch {
    return null;
  }
}

function isExcluded(relPath, excludeList) {
  if (!excludeList || excludeList.length === 0) return false;

  // Excludes are path segments or top-level folders. Example: "build" excludes build/**
  const parts = relPath.split(path.sep).filter(Boolean);
  return excludeList.some((ex) => {
    if (!ex) return false;
    if (parts.includes(ex)) return true;
    // Also allow exact match on first segment
    return parts[0] === ex;
  });
}

module.exports = {
  ensureDir,
  ensureEmptyDir,
  isExcluded,
  pathExists,
  readJsonIfExists,
  removeDir,
};
