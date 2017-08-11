#pragma once

#include <iterator>
#include <numeric>

namespace qlib {
namespace math {

template <class It> auto mean(It begin, It end);
template <class It> auto median(It begin, It end);

template <class It>
auto mean(It begin, It end) {
    auto sum = std::accumulate(begin, end, 0.0);
    return sum / std::distance(begin, end);
}

template <class It>
auto median(It begin, It end) {
    size_t dist = std::distance(begin, end);
    if (dist % 2 == 0) {
        It one = begin + (dist / 2);
        return qlib::math::mean(one, one + 1);
    } else {
        return *(begin + (dist / 2));
    }
}

}
}
