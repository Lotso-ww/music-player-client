#include "api_response.h"
#include "config.h"
#include "health_service.h"
#include "log_sanitizer.h"
#include "request_id.h"

#include <drogon/drogon.h>

#include <exception>
#include <string>

int main()
{
    try {
        const qqmusic::BackendConfig config = qqmusic::loadConfigFromEnvironment();

        drogon::app().setLogLevel(trantor::Logger::kInfo);
        drogon::app().registerPreRoutingAdvice(
            [](const drogon::HttpRequestPtr &request,
               drogon::AdviceCallback &&,
               drogon::AdviceChainCallback &&chainCallback) {
                request->attributes()->insert("request_id", qqmusic::newRequestId());
                chainCallback();
            });
        drogon::app().setCustomErrorHandler(
            [](drogon::HttpStatusCode status, const drogon::HttpRequestPtr &request) {
                const std::string id = qqmusic::api::requestId(request);
                if (status == drogon::k404NotFound) {
                    return qqmusic::api::errorResponse(status,
                                                       "route_not_found",
                                                       "The requested API route was not found.",
                                                       id);
                }
                return qqmusic::api::errorResponse(status,
                                                   "request_failed",
                                                   "The request could not be completed.",
                                                   id);
            });
        drogon::app().addListener(config.listenAddress, config.listenPort);
        drogon::orm::DbConfig databaseConfig;
        databaseConfig.rdbms = "mysql";
        databaseConfig.host = config.mysqlHost;
        databaseConfig.port = config.mysqlPort;
        databaseConfig.databaseName = config.mysqlDatabase;
        databaseConfig.user = config.mysqlUser;
        databaseConfig.password = config.mysqlPassword;
        databaseConfig.connectionNum = 2;
        databaseConfig.name = "qqmusic";
        drogon::app().addDbClient(databaseConfig);
        qqmusic::registerHealthEndpoint();
        LOG_INFO << "QQMusic API listening on " << config.listenAddress << ':' << config.listenPort;
        drogon::app().run();
        return 0;
    } catch (const std::exception &exception) {
        LOG_ERROR << "QQMusic API startup failed: " << qqmusic::sanitizeLogValue(exception.what());
        return 1;
    }
}
