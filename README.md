# create-drogon-app 🚀

Scaffold **Drogon (C++)** backend projects from ready-to-build templates.

## Quick start ⚡

Create a new project using npm:

```bash
npm create drogon-app@latest
```

Or run via npx:

```bash
npx create-drogon-app
```

If your npm version requires `--` to forward arguments:

```bash
npm create drogon-app@latest -- create my-service -t drogon-starter
```

## Usage 🧭

Interactive mode (no arguments):

```bash
create-drogon-app
```

Create a project (legacy positional form):

```bash
create-drogon-app my-service
```

Create a project (explicit subcommand):

```bash
create-drogon-app create my-service
```

List templates:

```bash
create-drogon-app list
```

Help/version:

```bash
create-drogon-app --help
create-drogon-app --version
```

## Options ⚙️

- `-t, --template <template>`: template ID (folder name under `templates/`)
- `-y, --yes`: skip prompts and use defaults when possible
- `-f, --force`: overwrite the target directory if it already exists

Examples:

```bash
create-drogon-app create my-service -t drogon-jwt-postgres-s3
```

```bash
create-drogon-app create -y -t drogon-starter
```

## Templates 📦

Template IDs are the folder names under `templates/`. If `--template` is not provided, the CLI uses the first template in alphabetical order.

| Template | Includes | Best for |
|---|---|---|
| `drogon-starter` | Drogon starter + PostgreSQL (Docker Compose) + `GET /health` sample route | A clean baseline backend |
| `drogon-jwt-postgres` | PostgreSQL (Docker Compose) + JWT auth + `GET /health` | Authenticated APIs |
| `drogon-jwt-postgres-s3` | PostgreSQL (Docker Compose) + JWT auth + AWS S3 integration (AWS SDK) + local MinIO | Auth + object storage |
| `drogon-postgres-s3` | PostgreSQL (Docker Compose) + AWS S3 integration (AWS SDK) + local MinIO | Object storage without JWT |

Each generated project includes its own `README.md` with template-specific setup commands.

## Prerequisites ✅

For the generator:

- Node.js (recommended: active LTS)
- npm

For building/running the generated C++ project:

- C++17 toolchain (GCC/Clang)
- CMake >= 3.15
- Python 3 + pip
- Conan
- Docker (optional; templates use it for local services like PostgreSQL/MinIO)

## What the CLI copies 🗂️

The CLI creates the target folder (relative to your current working directory) and copies the selected template into it.

By default it excludes: `.git`, `node_modules`, `build`, `dist`, `.cache`.

## Maintainer docs 🧑‍💻

See [docs/CODEBASE.md](docs/CODEBASE.md).

## License 📄

MIT
