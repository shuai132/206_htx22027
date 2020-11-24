#include <cstdio>
#include <vector>

#include "utils.h"

namespace utils {

void printHex(void *data, size_t len) {
#ifndef NDEBUG
    for (size_t i=0; i<len; i++) {
        printf("%02X ", ((uint8_t*)data)[i]);
    }
    printf("\n");
#endif
}

bool hex2string(const uint8_t *in, size_t inlen, char *out, size_t *outlen) {
    if(outlen == nullptr || *outlen < 2*inlen + 1)
        return false;

    char *pos = out;
    for(size_t i = 0; i < inlen; i += 1)
        pos += sprintf(pos, "%02hhx", in[i]);

    *outlen = pos - out + 1;
    return true;
}

void printHex(std::vector<uint8_t> data) {
    printHex(data.data(), data.size());
}

}
