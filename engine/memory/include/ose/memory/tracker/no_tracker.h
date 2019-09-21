#pragma once

#include <ose/typedef.h>

namespace ose::memory {

    class NoTracker
    {
    public:
        inline void allocate(void*, std::size_t, std::size_t) { }
        inline void deallocate(void*, std::size_t) { }
        inline void clear() { }
    };

}
