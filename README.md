# 🚀 create-drogon-app

Generate a ready-to-build **Drogon (C++)** backend in seconds. ⚡

This is an npm CLI that scaffolds a new project folder from one of the included templates. 🧱

---

## ✅ Quick Start

Create a new service:

```bash
npm create drogon-app@latest
```

If your npm version requires `--` to pass args:

```bash
npm create drogon-app@latest --
```

Prefer `npx`? (optional)

```bash
npx create-drogon-app
```

---

## 🧭 Interactive (Landing UI)

Run with no arguments to open the interactive “landing page” menu:

```bash
create-drogon-app
```

---

## 🧩 Templates

List available templates:

```bash
create-drogon-app list
```

Create using a specific template:

```bash
create-drogon-app create my-service --template drogon-starter
```

---

## 🛠️ Commands

Classic create (backwards compatible):

```bash
create-drogon-app my-service
```

Explicit create command:

```bash
create-drogon-app create my-service
```

---

## ⚙️ Options

- `-t, --template <name>`: pick a template (use `list` to see names)
- `-y, --yes`: skip prompts and use defaults when possible
- `-f, --force`: overwrite the target directory if it already exists

---

## 📦 Prerequisites

### For the generator

- Node.js (recommended: active LTS) 🟩
- npm

### For building/running the generated C++ project

- C++17 toolchain (GCC/Clang)
- CMake >= 3.15
- Python 3 + pip
- Conan
- Docker (optional; some templates use it for local services like PostgreSQL) 🐳

---

## 🏗️ After Generation (Build & Run)

Most templates follow this flow (your template README may add extra steps):

```bash
# 1) local env + config
cp .env.example .env
cp config/config.example.json config/config.json

# 2) (optional) start services (e.g. Postgres)
docker compose up -d

# 3) install C++ deps
conan profile detect --force
conan install . --output-folder=build --build=missing -s build_type=Release

# 4) configure + build
cmake --preset conan-release
cmake --build --preset conan-release

# 5) run (binary name can vary by template)
./build/Drogon_Starter
```

Health check (template-dependent):

```bash
curl -s http://localhost:3000/health
```

---

## ✨ What You Get (Typical)

- 🧰 CMake project + Conan dependencies
- 🌐 A sample Drogon route (often `GET /health`)
- 🧪 A sensible dev setup (may include Docker services depending on template)
- 🔐 `.env`-based configuration (template-dependent)

---

## 🧑‍💻 Maintainer Docs

Want to understand or extend the CLI itself (not the generated templates)?

- See [docs/CODEBASE.md](docs/CODEBASE.md)

## 📄 License

MIT
