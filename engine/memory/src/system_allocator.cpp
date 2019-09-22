#include "ose/memory/allocator/system_allocator.h"

#include "ose/memory/detail/ptr_algorithms.h"

#include <ose/debug.h>
#include <ose/alloc.h>

#include <cstdlib>

namespace ose::memory {

    namespace {
        struct AllocHeader { std::size_t size; };

        constexpr std::size_t c_allocOffset = 16;
        constexpr std::size_t c_maxAllocSize = std::size_t( -1 ) - 2 * c_allocOffset - 1;

        static_assert(sizeof(AllocHeader) <= c_allocOffset, "allocation header size is larger than max supported size");
        static_assert(alignof(AllocHeader) <= c_allocOffset, "allocation header alignment is larger than max supported alignment");
    }

    void* SystemAllocator::allocate(std::size_t bytes, [[maybe_unused]] std::size_t alignment)
    {
        OSE_ASSERT(bytes > 0 && bytes <= c_maxAllocSize, "allocation size {} is not within bounds ({}, {})", bytes, 0, c_maxAllocSize);
        OSE_ASSERT(alignment <= c_allocOffset, "overaligned allocation is not supported in this allocator: alignment={}, maxAlignment={}", alignment, c_allocOffset);

        const std::size_t totalSize = ptr_algorithm::adjustSize(bytes + c_allocOffset, c_allocOffset);

        if(void* allocPtr = ose::aligned_malloc(totalSize, c_allocOffset); allocPtr != nullptr)
        {
            AllocHeader* header = nullptr;
            header = new(allocPtr) AllocHeader;
            header->size = bytes;
            return ptr_algorithm::add(allocPtr, c_allocOffset);
        }

        return nullptr;
    }

    void SystemAllocator::deallocate(void* ptr)
    {
        void* allocPtr = ptr_algorithm::subtract(ptr, c_allocOffset);
        ose::aligned_free(allocPtr);
    }

    std::size_t SystemAllocator::allocationSize(void* ptr)
    {
        void* allocPtr = ptr_algorithm::subtract(ptr, c_allocOffset);
        AllocHeader* header = static_cast<AllocHeader*>(allocPtr);
        return header->size;
    }
}
