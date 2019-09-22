#pragma once

#include <ose/typedef.h>

namespace ose::memory {

    /**
     * System allocator using internally alignment aware system malloc/free functions.
     * Does not accept overaligned allocations.
     */
    class SystemAllocator final
    {
    public:
        void*       allocate(std::size_t bytes, std::size_t alignment);
        void        deallocate(void* ptr);

        std::size_t allocationSize(void* ptr);
    };

}
