#pragma once

#include <ose/typedef.h>

namespace ose::memory {

    template<std::size_t size, std::size_t alignment = alignof(std::max_align_t)>
    class StackMemoryArea final
    {
    public:
        StackMemoryArea() = default;

        StackMemoryArea(const StackMemoryArea&) = delete;
        StackMemoryArea(StackMemoryArea&&) = delete;

        StackMemoryArea& operator=(const StackMemoryArea&) = delete;
        StackMemoryArea& operator=(StackMemoryArea&&) = delete;

        void* begin() { return static_cast<void*>(&m_storage[0]); }
        void* end() { return static_cast<void*>(&m_storage[0] + size); };

    private:
        alignas(alignment) OSEbyte m_storage[size];
    };

}