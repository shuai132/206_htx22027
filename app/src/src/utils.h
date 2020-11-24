#pragma once

#include <cstdint>

namespace utils {

template <typename T, bool little_end = true>
inline T raw(const void* p) {
    static_assert(little_end, "Only support little_end for now!");
    T t{};
    auto size = sizeof(T);
    if (little_end) {
        for(size_t i=0; i<size; i++) {
            T tmp = *((uint8_t*)p+i);
            tmp <<= 8u * i;
            t |= tmp;
        }
    }
    return t;
}

inline void printHex(void* data, size_t len) {
#ifndef NDEBUG
    for (size_t i=0; i<len; i++) {
        printf("%02X ", ((uint8_t*)data)[i]);
    }
    printf("\n");
#endif
}
inline void printHex(std::vector<uint8_t> data) {
    printHex(data.data(), data.size());
}

}
