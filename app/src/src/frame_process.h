#pragma once

#include <FrameParser.h>

void initProcess(const std::shared_ptr<FrameParser>& frameParser,
                 const std::shared_ptr<Hardware>& hardware);
