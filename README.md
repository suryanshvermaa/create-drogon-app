# 🚀 create-drogon-app

A tiny Node.js CLI that scaffolds a ready-to-build **Drogon (C++)** backend.
It copies the template from `templates/drogon-starter` into a new folder.

---

## ✨ What you get

The generated project includes:

- ⚙️ **CMake** project (CMake >= 3.15)
- 📦 **Conan** dependency management (`drogon/1.9.12`)
- 🐘 **PostgreSQL** dev database via `docker compose`
- 🐳 A **Dockerfile** to build/run the app in a container
- 🩺 A sample `GET /health` route
- 🔌 Loads `PORT` from `.env` (defaults to `3000`)

---

## ✅ Prerequisites

### For the generator

- Node.js (recommended: an active LTS)
- npm

### For building the generated C++ project

- C++17 toolchain (e.g. GCC/Clang)
- CMake >= 3.15
- Python 3 + pip
- Conan
- Docker (optional, used for PostgreSQL and/or building the image)

---

## 📥 Install

### Option A (recommended): use as a starter via npm

```bash
npm create drogon-app@latest my-service
```

Then:

```bash
cd my-service
```

> If your npm version requires `--` to pass args, use: `npm create drogon-app@latest -- my-service`.

### Option B: use locally from this repo (development)

```bash
# from the repo root
npm install -g .
create-drogon-app my-service
```

### Option C: run without installing globally

```bash
node ./bin/index.js my-service
```

---

## 🧪 Usage

### Interactive (landing UI)

Run with no args to open the landing menu:

```bash
create-drogon-app
```

### Create (classic)

Create a new Drogon project (backwards compatible with the old CLI):

```bash
npm create drogon-app@latest my-service
cd my-service
```

### Commands

List templates:

```bash
create-drogon-app list
```

Create using a specific template:

```bash
create-drogon-app create my-service --template drogon-starter
```

The CLI prints basic build commands. For a more complete local setup (recommended), run:

```bash
# 1) local env + config
cp .env.example .env
cp config/config.example.json config/config.json

# 2) (optional) start Postgres
docker compose up -d

# 3) install dependencies
conan profile detect --force
conan install . --output-folder=build --build=missing -s build_type=Release

# 4) configure + build
cmake --preset conan-release
cmake --build --preset conan-release

# 5) run
./build/Drogon_Starter
```

Hit the health endpoint:

```bash
curl -s http://localhost:3000/health
```

---

## 🗂️ Template details

Templates live at:

- `templates/drogon-starter/`

It is copied **as-is** into your new project directory.

### Adding your own templates (no code changes)

Drop a new folder under `templates/` (e.g. `templates/drogon-aws-s3/`).
The CLI discovers templates dynamically, so it will automatically show up in:

- the landing UI template picker
- `create-drogon-app list`

Optional: add `template.json` inside the template folder to improve the UI:

```json
{
	"name": "Drogon + AWS S3",
	"description": "Starter with S3 upload integration",
	"exclude": ["build", "node_modules", ".git"]
}
```
For full template documentation, see:

- `templates/drogon-starter/README.md`

---

## 🛠️ How it works

- Entry point: `bin/index.js`
- It reads the project name from the first CLI argument.
- It copies `templates/drogon-starter` to `./<projectName>` using Node’s `fs.cpSync(..., { recursive: true })`.

---

## 🧩 Development (this repo)

Typical workflow:

```bash
# edit files under templates/drogon-starter/
node ./bin/index.js _tmp_test_app
rm -rf _tmp_test_app
```

---

## 📄 License

MIT
