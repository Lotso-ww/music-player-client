# ADR 0001: Select Drogon for the P2 C++ REST backend

- Status: Accepted for P2A technical validation
- Date: 2026-08-11

## Context

The Qt desktop client remains on C++11. The server is an independent Linux/Docker workload and may use C++17. P2 needs asynchronous HTTP, JSON, MySQL support, testability, and a Docker-based deployment path. The project must not maintain multiple web frameworks in parallel.

## Decision

Use Drogon with C++17 for the P2 server validation. The validation uses an explicit versioned `/api/v1/health` endpoint, Drogon's asynchronous MySQL client, CTest/Drogon tests, and an Ubuntu 24.04 Docker build.

## Alternatives considered

| Framework | Decision | Reason |
|---|---|---|
| Drogon | Chosen | Native asynchronous HTTP, JSON support, integrated ORM/MySQL client, CMake support, and suitable Linux container workflow. |
| oatpp | Not selected | Viable, but no demonstrated advantage for this project's first server module after Drogon's validation is accepted. |
| Crow | Not selected | Lightweight HTTP option, but the database and production integration path would require more assembly for the planned P2 scope. |

## Consequences

- P2 server code targets C++17 and is isolated under `backend/`; Qt client code remains unchanged.
- New routes must be under `/api/v1`, use the standard error body, issue server-generated request IDs, and redact credential-like values from explicit logs.
- Framework replacement requires a new ADR and a failing/insufficient P2A validation record. No parallel framework subtree is introduced.
- Runtime validation still requires Docker Engine on an Ubuntu-capable host; credentials are supplied through an ignored `.env` file.
