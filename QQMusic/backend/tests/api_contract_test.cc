#include "api_response.h"
#include "log_sanitizer.h"
#include "request_id.h"

#include <iostream>
#include <regex>

namespace {

bool check(bool condition, const char *message)
{
    if (condition) return true;
    std::cerr << "FAILED: " << message << '\n';
    return false;
}

}  // namespace

int main()
{
    bool passed = true;

    const std::string id = qqmusic::newRequestId();
    const std::regex uuidV4(
        "^[0-9a-f]{8}-[0-9a-f]{4}-4[0-9a-f]{3}-[89ab][0-9a-f]{3}-[0-9a-f]{12}$");
    passed &= check(std::regex_match(id, uuidV4), "request ID must be a UUID v4");

    const Json::Value body = qqmusic::api::errorBody("route_not_found", "Not found.", "test-id");
    passed &= check(body["error"]["code"].asString() == "route_not_found",
                    "error code must be stable");
    passed &= check(body["error"]["message"].asString() == "Not found.",
                    "error message must be preserved");
    passed &= check(body["error"]["request_id"].asString() == "test-id",
                    "error request ID must be preserved");

    const std::string sanitized = qqmusic::sanitizeLogValue(
        "password=secret token=abc Authorization: Bearer eyJhbGci password=\"has spaces\" /x?refresh_token=def");
    passed &= check(sanitized.find("secret") == std::string::npos,
                    "password must be redacted");
    passed &= check(sanitized.find("abc") == std::string::npos,
                    "token must be redacted");
    passed &= check(sanitized.find("eyJhbGci") == std::string::npos,
                    "authorization must be redacted");
    passed &= check(sanitized.find("has spaces") == std::string::npos,
                    "quoted password must be redacted");
    passed &= check(sanitized.find("def") == std::string::npos,
                    "query token must be redacted");
    passed &= check(sanitized.find("[REDACTED]") != std::string::npos,
                    "redaction marker must be present");

    return passed ? 0 : 1;
}
