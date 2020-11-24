#pragma once

#include <vector>
#include <queue>
#include <string>

/**
 * 一些数据结构
 */
using Frame = std::vector<uint8_t>;
using MacAddr = std::vector<uint8_t>;
using FrameQueue = std::queue<Frame>;

struct DataFrame {
    static const uint16_t HEAD = 0x7E7E;
    static const uint16_t HEAD_LEN = 5;

    uint16_t len;
    uint8_t cmd;
    Frame xp;   // CP or SP
    uint16_t crc;
};

struct MacFrame {
    MacAddr macTo;
    MacAddr macFrom;
    uint16_t len;
    DataFrame dataFrame;
};
