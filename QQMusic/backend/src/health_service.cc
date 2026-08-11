#include "health_service.h"

#include "api_response.h"
#include "log_sanitizer.h"

#include <drogon/drogon.h>

#include <functional>

namespace qqmusic {

void registerHealthEndpoint()
{
    drogon::app().registerHandler(
        "/api/v1/health",
        [](const drogon::HttpRequestPtr &request,
           std::function<void(const drogon::HttpResponsePtr &)> &&callback) {
            const std::string id = api::requestId(request);
            const auto client = drogon::app().getDbClient("qqmusic");
            if (!client) {
                callback(api::errorResponse(drogon::k503ServiceUnavailable,
                                            "dependency_unavailable",
                                            "Service is temporarily unavailable.",
                                            id));
                return;
            }

            client->execSqlAsync(
                "SELECT 1",
                [callback, id](const drogon::orm::Result &) {
                    Json::Value data(Json::objectValue);
                    data["status"] = "ok";
                    data["database"] = "available";
                    callback(api::dataResponse(data, id));
                },
                [callback, id](const drogon::orm::DrogonDbException &exception) {
                    LOG_WARN << "health database check failed: "
                             << sanitizeLogValue(exception.base().what());
                    callback(api::errorResponse(drogon::k503ServiceUnavailable,
                                                "dependency_unavailable",
                                                "Service is temporarily unavailable.",
                                                id));
                });
        },
        {drogon::Get});
}

}  // namespace qqmusic
