#include "Hardware.h"

#include <utility>

Hardware::Hardware(MacAddr local, MacAddr remote)
        : local(std::move(local))
        , remote(std::move(remote))
{}

void cb::error(const char* msg) {
    LOGE("cb: error: %s", msg);
}

void cb::warn(const char* msg) {
    LOGW("cb: warn: %s", msg);
}
