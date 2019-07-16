#pragma once

#include <ose/typedef.h>

namespace ose::memory {

    class NoBoundsChecker
    {
        static constexpr std::size_t sc_guardSize{ 0u };

    public:
        inline void guard([[maybe_unused]] OSEbyte*) { }
        inline void validate([[maybe_unused]] OSEbyte*) { }
        
        static constexpr std::size_t getSize() { return sc_guardSize; }
    };

}