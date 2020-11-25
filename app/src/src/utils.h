#pragma once

#include <cstdint>
#include <cstddef>

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

void printHex(void* data, size_t len);
void printHex(std::vector<uint8_t> data);

bool hex2string(const uint8_t* in, size_t inlen, char *out, size_t *outlen);

}

#define FOR(i, n)   for(std::remove_reference<std::remove_const<typeof(n)>::type>::type i = 0; i < n; i++)
