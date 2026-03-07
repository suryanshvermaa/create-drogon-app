#!/usr/bin/env node

const fs = require("fs");
const path = require("path");

const projectName = process.argv[2];

if (!projectName) {
  console.log("Please provide a project name.");
  process.exit(1);
}

const targetDir = path.join(process.cwd(), projectName);
const templateDir = path.join(__dirname, "../templates/drogon-starter");

fs.cpSync(templateDir, targetDir, { recursive: true });

console.log(`🚀 Drogon project created: ${projectName}`);
console.log(`cd ${projectName}`);
console.log(`conan install . --output-folder=build --build=missing`);
console.log(`cmake --preset conan-release && cmake --build --preset conan-release`);