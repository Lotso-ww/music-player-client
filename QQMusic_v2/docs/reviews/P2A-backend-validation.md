# P2A C++ 后端技术验证

## 基本信息

- SPEC 编号：P2A-01 至 P2A-04
- Git 分支：master
- 关键提交：`214e4ac` 至 `f42ffc0`
- 完成日期：2026-08-11
- 状态：已完成

## 本次目标

- 为后续账号、曲库和同步服务确认单一 C++ Web 框架。
- 最小验证 HTTP、JSON、异步 MySQL、自动测试和 Ubuntu 24.04 Docker 构建路径。
- 在业务模块开始前固定 REST 版本、错误和日志安全边界。

## 实际变更

- 新增 `backend/` C++17/Drogon 子工程，Qt 5/C++11 客户端不受影响。
- 新增 `GET /api/v1/health`：异步执行 `SELECT 1`，仅返回数据库可用性，不返回 SQL 或连接信息。
- 成功体固定为 `data + request_id`；错误体固定为 `error.code + error.message + error.request_id`；所有响应带 `X-Request-Id`。
- 服务器生成请求 ID，不信任客户端传入值；显式日志写入前对 password、token、Authorization 和 URL 查询参数进行脱敏。
- 新增 MySQL schema 版本初始化、`.env.example`、Ubuntu 24.04 多阶段 Dockerfile、Docker Compose 和 PowerShell 端到端验证脚本。
- 新增 ADR 0001，选择 Drogon，不并行维护 oatpp/Crow。

## 架构与关键决策

- 后端采用 Drogon/C++17，目录隔离于 `backend/`；客户端继续使用既有 Qt 5.14.2/C++11/qmake 工程。
- MySQL 连接由 Drogon 连接池管理；健康检查只检验可连接性，避免提前引入账号或同步数据模型。
- 容器构建固定 Drogon `v1.9.10`，使用 Ubuntu 24.04，运行时通过环境变量接收数据库配置；真实 `.env` 被 Git 忽略。
- 仅在 Docker 验证失败或无法满足 P2 需求时才根据 ADR 重新评估 oatpp/Crow。

## 验证记录

- `g++ -std=c++17 -Wall -Wextra -Wpedantic -Werror -c backend/src/log_sanitizer.cc`：通过。
- `git diff --check`：通过。
- 使用 MinGW 生成器执行 `cmake -S backend ...`：CMake 解析工程成功，随后因本机没有 `DrogonConfig.cmake` 停在 `find_package(Drogon)`；默认 Visual Studio 生成器另受当前环境的 Windows SDK 路径权限限制。Docker Engine 也不可用。
- `scripts/verify-p2a.ps1` 已覆盖 Compose 配置、镜像构建、MySQL 健康等待、`/api/v1/health`、404 错误契约及请求 ID 一致性，但本机无法运行。
- Ubuntu 24.04 LTS 服务器执行 `docker compose ... build api`：通过；Drogon `v1.9.10`、MariaDB Connector/C、后端二进制均构建成功，CTest `1/1` 通过。
- 应用 MySQL 账号执行 `SELECT 1`：通过。
- `GET /api/v1/health`：HTTP `200`，返回 `data.database=available`、`data.status=ok`；响应头和 JSON 内的请求 ID 一致。
- `GET /api/v1/not-found`：HTTP `404`，返回 `error.code=route_not_found`；响应头和 JSON 内的请求 ID 一致。
- 验收脚本执行 `docker compose ... down -v --remove-orphans` 后检查：Compose 项目为空，无遗留 `backend-*` 容器或验证 MySQL 卷。

## 遗留事项

- Docker 构建使用 Gitee Drogon 镜像和可配置的 Trantor 代理地址，适配无法直接访问 GitHub 的服务器网络；具备 GitHub 访问能力的环境可通过构建参数替换源地址。
- 运行容器使用非 root UID `65534`，并以 `/var/lib/qqmusic` 作为可写工作目录，避免 Drogon 默认上传临时目录在根目录下创建失败。MySQL 配置零初始化，明确使用 `utf8mb4` 和 5 秒连接超时。
- 当前不含账户、Token、同步、曲库或下载业务逻辑，符合 P2A 技术验证边界。

## 面试回顾

- 为什么隔离后端：客户端维持 Qt/C++11 兼容性，Linux 服务端可以独立使用 C++17 和 Docker 工具链，避免无关迁移风险。
- 为什么健康检查要访问 MySQL：进程存活不能证明服务依赖可用；`SELECT 1` 能验证连接池、网络和数据库凭据，但不会泄露表结构或错误详情。
- 如何防止日志泄密：服务端只生成请求 ID；认证字段和 URL 查询中的敏感值在写日志前统一替换为 `[REDACTED]`，错误响应不回显异常或 SQL。
