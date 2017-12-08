#include <cstddef>
#include <cstdint>
#include <iomanip>
#include <sstream>
#include <string>

#include "util.h"

using namespace qlib::debug;

std::string qlib::debug::bufferToString(const void* data, size_t len) {
    std::stringstream ss;

    if (data != NULL) {
        const uint8_t* buffer = static_cast<const uint8_t*>(data);
        ss << std::hex << std::setfill('0');
        ss << "0x";

        for (size_t i = 0; i < len; ++i) {
            ss << std::setw(2) << static_cast<int>(buffer[i]) << " ";
        }

        ss << std::endl;
    }

    return ss.str();
}
