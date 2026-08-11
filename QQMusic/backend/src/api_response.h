#pragma once

#include <drogon/HttpRequest.h>
#include <drogon/HttpResponse.h>

#include <json/value.h>

#include <string>

namespace qqmusic::api {

std::string requestId(const drogon::HttpRequestPtr &request);

Json::Value errorBody(const std::string &code,
                      const std::string &message,
                      const std::string &requestId);

drogon::HttpResponsePtr errorResponse(drogon::HttpStatusCode status,
                                      const std::string &code,
                                      const std::string &message,
                                      const std::string &requestId);

drogon::HttpResponsePtr dataResponse(const Json::Value &data,
                                     const std::string &requestId);

}  // namespace qqmusic::api
