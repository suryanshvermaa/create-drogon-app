## IEEE Conference Backend

C++ backend API built with Drogon.

- Database: PostgreSQL
- Object storage: MinIO (S3-compatible) via AWS SDK
- API contract: OpenAPI at `routes/openapi.yaml`

## Prerequisites

- C++ toolchain (gcc/clang)
- CMake (>= 3.15)
- Conan 2.x
- Docker (recommended for local Postgres + MinIO)

## Local services (Postgres + MinIO)

Start the dependencies:

```bash
docker compose up -d
```

This uses `docker-compose.yml` and provisions:

- PostgreSQL: `localhost:5432` (db `ieee_conference_db`, user `postgres`, pass `postgres`)
- MinIO S3 API: `http://localhost:9000`
- MinIO Console: `http://localhost:9001`

MinIO dev credentials (from `docker-compose.yml`):

- Access key: `suryansh`
- Secret key: `suryansh`

DB schema initialization:

- SQL files in `sql/` are mounted into `/docker-entrypoint-initdb.d` (tables: `users`, `notifications`).

## Environment variables

The server loads environment variables from a local `.env` file at startup.

```bash
cp .env.example .env
```

Required / commonly used:

- `PORT` (defaults to `3000`)
- `JWT_SECRET`
- `S3_ENDPOINT`, `S3_REGION`, `S3_ACCESS_KEY`, `S3_SECRET_KEY`, `S3_BUCKET`, `S3_USE_SSL`

Notes:

- `S3_BUCKET` must be set or S3 operations will fail.
- By default, `.env.example` targets local MinIO at `http://127.0.0.1:9000`.

## Build (local)

```bash
conan profile detect --force
conan install . \
  --output-folder=build \
  --build=missing \
  -c tools.system.package_manager:mode=install \
  -c tools.system.package_manager:sudo=True

cmake --preset conan-release
cmake --build --preset conan-release
```

Outputs:

- `build/build/Release/IEEE_Conference_Backend` (main server)
- `build/build/Release/createAdmin` (CLI helper)

## Run (local)

Important: the server loads `./config/config.json` using a relative path, so run it from inside this `backend/` directory.

```bash
./build/build/Release/IEEE_Conference_Backend
```

Database config comes from `config/config.json`.

## Create an admin user (optional)

Build first, then run:

```bash
./build/build/Release/createAdmin ./config/config.json
```

The prompt asks for email/username/password and inserts a user with role `admin`.

## API

- Health: `GET /health`
- Versioned routes: `/api/v1/...`
- OpenAPI spec: `routes/openapi.yaml` (import into Swagger UI or Postman)

## Container (optional)

Production compose builds/runs the backend container:

```bash
docker compose -f docker-compose.prod.yml up --build
```

Notes:

- `docker-compose.prod.yml` maps host `3000:3000`, so set `PORT=3000` in `.env` for the container.
- The `Dockerfile` currently declares `EXPOSE 8080`, but the app listens on `PORT` (default `3000`).