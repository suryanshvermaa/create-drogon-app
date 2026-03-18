const pc = require("picocolors");
const {
  intro,
  outro,
  select,
  isCancel,
  cancel,
} = require("@clack/prompts");

const { createProject } = require("../commands/create");
const { listTemplates } = require("../commands/list");

function banner() {
  return [
    "  ____                _        ____                                ",
    " / ___|_ __ ___  __ _| |_ ___ |  _ \\ _ __ ___   __ _  ___  _ __   ",
    "| |   | '__/ _ \\/ _` | __/ _ \\| | | | '__/ _ \\ / _` |/ _ \\| '_ \\  ",
    "| |___| | |  __/ (_| | ||  __/| |_| | | | (_) | (_| | (_) | | | | ",
    " \\____|_|  \\___|\\__,_|\\__\\___||____/|_|  \\___/ \\__, |\\___/|_| |_| ",
    "                                             |___/                 ",
    "                         create drogon app                         ",
  ].join("\n");
}

async function runLanding() {
  // eslint-disable-next-line no-console
  console.log(pc.cyan(banner()));
  intro(pc.dim("Drogon C++ project generator"));

  const action = await select({
    message: "What do you want to do?",
    options: [
      { value: "create", label: "Create a new project" },
      { value: "list", label: "List templates" },
      { value: "exit", label: "Exit" },
    ],
  });

  if (isCancel(action)) {
    cancel("Aborted.");
    return;
  }

  if (action === "list") {
    const templates = await listTemplates();
    if (templates.length === 0) {
      outro("No templates found under templates/.");
      return;
    }

    // eslint-disable-next-line no-console
    console.log(pc.bold("\nAvailable templates:"));
    for (const t of templates) {
      const desc = t.description ? ` - ${t.description}` : "";
      // eslint-disable-next-line no-console
      console.log(`- ${pc.cyan(t.id)}${desc}`);
    }

    outro("Done.");
    return;
  }

  if (action === "exit") {
    outro("Bye.");
    return;
  }

  await createProject({});
}

module.exports = { runLanding };
