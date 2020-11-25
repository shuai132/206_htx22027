#pragma once

#include <functional>
#include <cstdint>

#include "typedef.h"

/**
 * 数据发送实现
 * num指的是架位
 */
using SendFrameImpl = std::function<void(int num, uint8_t ST, Frame SP)>;

void ioCheckInit(SendFrameImpl SendFrame, bool hwInit = false);
void ioCheckClose();
void ioCheck();
