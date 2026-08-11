#include "config.h"

#include <cstdlib>
#include <limits>
#include <stdexcept>

namespace {

std::string environmentOrDefault(const char *name, const char *defaultValue)
{
    const char *value = std::getenv(name);
    return value == nullptr || *value == '\0' ? defaultValue : value;
}

std::uint16_t portFromEnvironment(const char *name, std::uint16_t defaultValue)
{
    const std::string value = environmentOrDefault(name, "");
    if (value.empty()) return defaultValue;

    std::size_t parsedLength = 0;
    const unsigned long parsed = std::stoul(value, &parsedLength, 10);
    if (parsedLength != value.size() || parsed == 0 ||
        parsed > std::numeric_limits<std::uint16_t>::max()) {
        throw std::runtime_error(std::string("Invalid port in ") + name);
    }
    return static_cast<std::uint16_t>(parsed);
}

}  // namespace

namespace qqmusic {

BackendConfig loadConfigFromEnvironment()
{
    BackendConfig config;
    config.listenAddress = environmentOrDefault("API_LISTEN_ADDRESS", "0.0.0.0");
    config.listenPort = portFromEnvironment("API_LISTEN_PORT", 8080);
    config.mysqlHost = environmentOrDefault("MYSQL_HOST", "127.0.0.1");
    config.mysqlPort = portFromEnvironment("MYSQL_PORT", 3306);
    config.mysqlDatabase = environmentOrDefault("MYSQL_DATABASE", "qqmusic");
    config.mysqlUser = environmentOrDefault("MYSQL_USER", "qqmusic_app");
    config.mysqlPassword = environmentOrDefault("MYSQL_PASSWORD", "");
    return config;
}

}  // namespace qqmusic
