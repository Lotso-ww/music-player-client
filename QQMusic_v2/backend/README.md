# QQMusic P2A Backend Validation

This directory is an isolated C++17/Drogon technical validation. It deliberately contains no account, sync, catalog, or recommendation business logic from later P2 modules.

## Contract

- `GET /api/v1/health` verifies the API process and MySQL connectivity.
- Successful responses use `{ "data": ..., "request_id": "..." }`.
- Errors use `{ "error": { "code": "...", "message": "...", "request_id": "..." } }`.
- Every response contains the same `X-Request-Id` value as its body. The server generates it and does not trust an inbound value.
- `404` is represented as `route_not_found`; database failures return `503 dependency_unavailable` without SQL details.

## Local CMake build

Drogon with MySQL ORM support must be installed first. The Dockerfile is the reference reproducible environment.

```powershell
cmake -S backend -B backend/build -DQQMUSIC_BACKEND_BUILD_TESTS=ON
cmake --build backend/build --config Release
ctest --test-dir backend/build -C Release --output-on-failure
```

## Docker Compose validation

```powershell
Copy-Item backend/.env.example backend/.env
# Edit backend/.env with non-default local development passwords.
docker compose --env-file backend/.env -f backend/docker-compose.yml up --build --wait
curl.exe -i http://localhost:8080/api/v1/health
curl.exe -i http://localhost:8080/api/v1/not-found
docker compose --env-file backend/.env -f backend/docker-compose.yml down -v
```

Expected health response is HTTP `200` with `data.status=ok` and `data.database=available`. The unknown route must return HTTP `404` with `error.code=route_not_found`; both responses must contain an `X-Request-Id` header.

`down -v` removes the local MySQL validation volume. Do not use it against a deployment that contains data to keep.
