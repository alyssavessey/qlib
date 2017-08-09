#pragma once
#include <iterator>

namespace qlib {
namespace sort {

template <class RandomIt>
void slowsort(RandomIt first, RandomIt last) {
    if (first >= last) {
        return;
    }

    RandomIt mid = first + (std::distance(first, last) / 2);
    qlib::sort::slowsort(first, mid);
    qlib::sort::slowsort(mid + 1, last);

    if (*last < *mid) {
        std::iter_swap(mid, last);
    }

    qlib::sort::slowsort(first, last - 1);
}

template <class RandomIt, class Compare>
void slowsort(RandomIt first, RandomIt last, Compare comp) {
    if (first >= last) {
        return;
    }

    RandomIt mid = first + (std::distance(first, last) / 2);
    qlib::sort::slowsort(first, mid);
    qlib::sort::slowsort(mid + 1, last);

    if (comp(*last, *mid)) {
        std::iter_swap(mid, last);
    }

    qlib::sort::slowsort(first, last - 1);
}

}
}
