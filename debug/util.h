#pragma once

#include <cstddef>
#include <string>

namespace qlib {
namespace debug {

std::string bufferToString(const void* buffer, size_t len);

}
}
