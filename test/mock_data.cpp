#include <functional>

#include "mock_data.h"
#include "typedef.h"
#include "log/log.h"

/**              |   目的MAC   |   源MAC   | 长度 |head len CO     CP      CRC |  FCS  */
auto MOCK_DATA = "0605040302DA 0605040302CA 0C00 7E7E 0A00 13 1122334455 4158 5AAAAAA5";

static void parserHexStr(const std::string& hexStr, const std::function<void(uint8_t)>& onHexCb) {
    bool isFirst = true;
    uint8_t tmp = 0;
    for (uint8_t c : hexStr) {
        if (c == ' ') {
            continue;
        }

        uint8_t v;
        if ('0' <= c && c <= '9') {
            v = c - '0';
        } else if('A' <= c && c <= 'F') {
            v = c - 'A' + 10;
        } else if('a' <= c && c <= 'f') {
            v = c - 'a' + 10;
        } else {
            FATAL("unknown char");
        }

        tmp += v;

        if (isFirst) {
            tmp *= 16;
            isFirst = false;
        } else {
            onHexCb(tmp);
            isFirst = true;
            tmp = 0;
        }
    }
}

Frame getMockFrame() {
    Frame frame;
    parserHexStr(MOCK_DATA, [&](uint8_t d) {frame.push_back(d);});
    return frame;
}

