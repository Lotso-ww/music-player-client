#pragma once

#include <cstdint>
#include <string>

namespace qqmusic {

struct BackendConfig {
    std::string listenAddress;
    std::uint16_t listenPort;
    std::string mysqlHost;
    std::uint16_t mysqlPort;
    std::string mysqlDatabase;
    std::string mysqlUser;
    std::string mysqlPassword;
};

BackendConfig loadConfigFromEnvironment();

}  // namespace qqmusic
