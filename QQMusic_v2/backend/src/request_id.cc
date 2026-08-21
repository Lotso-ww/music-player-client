#include "request_id.h"

#include <array>
#include <iomanip>
#include <random>
#include <sstream>

namespace qqmusic {

std::string newRequestId()
{
    thread_local std::mt19937_64 generator(std::random_device{}());
    std::array<unsigned char, 16> bytes{};
    for (auto &byte : bytes) byte = static_cast<unsigned char>(generator());
    bytes[6] = static_cast<unsigned char>((bytes[6] & 0x0fU) | 0x40U);
    bytes[8] = static_cast<unsigned char>((bytes[8] & 0x3fU) | 0x80U);

    std::ostringstream stream;
    stream << std::hex << std::setfill('0');
    for (std::size_t index = 0; index < bytes.size(); ++index) {
        stream << std::setw(2) << static_cast<unsigned int>(bytes[index]);
        if (index == 3 || index == 5 || index == 7 || index == 9) stream << '-';
    }
    return stream.str();
}

}  // namespace qqmusic
