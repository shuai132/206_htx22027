#pragma once

#include <functional>
#include <memory>
#include <utility>

namespace {

struct DeferOp {
    using DeferHelper = std::unique_ptr<void, std::function<void(void*)>>;

    template <typename Func>
    DeferHelper operator<<(Func && func) {
        return DeferHelper((void*)1, [func = std::forward<Func>(func)](void*){
            func();
        });
    }
};

#define __DEFER_CAT_(a, b) a##b
#define __DEFER_CAT(a, b) __DEFER_CAT_(a, b)
#define defer auto __DEFER_CAT(__defer__, __COUNTER__) = DeferOp()<<

}
