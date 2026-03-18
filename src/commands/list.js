const { discoverTemplates } = require("../templates/discover");

async function listTemplates() {
  return discoverTemplates();
}

module.exports = { listTemplates };
