#pragma once

#include <ose/typedef.h>

namespace ose::memory {

    class NoTracker
    {
    public:
        inline void allocate([[maybe_unused]] void*, [[maybe_unused]] std::size_t, [[maybe_unused]] std::size_t) { }
        inline void deallocate([[maybe_unused]] void*, [[maybe_unused]] std::size_t) { }
        inline void clear() { }
    };

}