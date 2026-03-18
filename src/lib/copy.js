const fs = require("fs/promises");
const path = require("path");

const { ensureDir, isExcluded } = require("./fs");

async function copyFile(src, dest) {
  await ensureDir(path.dirname(dest));
  await fs.copyFile(src, dest);
}

async function copySymlink(src, dest) {
  const link = await fs.readlink(src);
  await ensureDir(path.dirname(dest));
  await fs.symlink(link, dest);
}

async function copyDir(srcDir, destDir, { exclude = [], rootSrc = srcDir } = {}) {
  const entries = await fs.readdir(srcDir, { withFileTypes: true });
  await ensureDir(destDir);

  for (const ent of entries) {
    const srcPath = path.join(srcDir, ent.name);
    const destPath = path.join(destDir, ent.name);
    const rel = path.relative(rootSrc, srcPath);

    // rel here is just ent.name; the deeper exclusion is handled in recursion
    if (isExcluded(rel, exclude)) {
      continue;
    }

    if (ent.isDirectory()) {
      await copyDir(srcPath, destPath, { exclude, rootSrc });
      continue;
    }

    if (ent.isSymbolicLink()) {
      await copySymlink(srcPath, destPath);
      continue;
    }

    if (ent.isFile()) {
      await copyFile(srcPath, destPath);
    }
  }
}

module.exports = { copyDir };
