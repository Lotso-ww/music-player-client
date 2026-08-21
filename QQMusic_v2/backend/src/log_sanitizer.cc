#include "log_sanitizer.h"

#include <regex>

namespace qqmusic {

std::string sanitizeLogValue(const std::string &value)
{
    std::string sanitized = value;
    const std::regex authorization(
        R"(((authorization\s*[=:]\s*[\"']?)([A-Za-z]+\s+)?)([^\s,\"'&}]+))",
        std::regex_constants::icase);
    sanitized = std::regex_replace(sanitized, authorization, "$1[REDACTED]");

    const std::regex quotedKeyValue(
        R"(((password|token|access_token|refresh_token)\s*[=:]\s*[\"'])([^\"']*)([\"']))",
        std::regex_constants::icase);
    sanitized = std::regex_replace(sanitized, quotedKeyValue, "$1[REDACTED]$4");

    const std::regex keyValue(
        R"(((password|token|access_token|refresh_token)\s*[=:]\s*[\"']?)([^\s,\"'&}]+))",
        std::regex_constants::icase);
    sanitized = std::regex_replace(sanitized, keyValue, "$1[REDACTED]");

    const std::regex queryValue(
        R"(([?&](authorization|password|token|access_token|refresh_token)=)([^&\s]+))",
        std::regex_constants::icase);
    return std::regex_replace(sanitized, queryValue, "$1[REDACTED]");
}

}  // namespace qqmusic
