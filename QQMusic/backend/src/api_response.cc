#include "api_response.h"

namespace qqmusic::api {

std::string requestId(const drogon::HttpRequestPtr &request)
{
    const auto value = request->getAttributes()->get<std::string>("request_id");
    return value.empty() ? "unknown" : value;
}

Json::Value errorBody(const std::string &code,
                      const std::string &message,
                      const std::string &id)
{
    Json::Value body(Json::objectValue);
    body["error"]["code"] = code;
    body["error"]["message"] = message;
    body["error"]["request_id"] = id;
    return body;
}

drogon::HttpResponsePtr errorResponse(drogon::HttpStatusCode status,
                                      const std::string &code,
                                      const std::string &message,
                                      const std::string &id)
{
    const auto response = drogon::HttpResponse::newHttpJsonResponse(errorBody(code, message, id));
    response->setStatusCode(status);
    response->addHeader("X-Request-Id", id);
    return response;
}

drogon::HttpResponsePtr dataResponse(const Json::Value &data, const std::string &id)
{
    Json::Value body(Json::objectValue);
    body["data"] = data;
    body["request_id"] = id;
    const auto response = drogon::HttpResponse::newHttpJsonResponse(body);
    response->addHeader("X-Request-Id", id);
    return response;
}

}  // namespace qqmusic::api
