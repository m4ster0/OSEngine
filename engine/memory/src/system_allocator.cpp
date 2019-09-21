#include "ose/memory/allocator/system_allocator.h"

#include "ose/memory/detail/ptr_algorithms.h"

#include <ose/debug.h>
#include <ose/alloc.h>

#include <cstdlib>

namespace ose::memory {

    namespace {
        struct AllocHeader { std::size_t size; };

        constexpr std::size_t c_alignment = 16;
        constexpr std::size_t c_maxAllocSize = std::size_t( -1 ) - 2 * c_alignment - 1;

        static_assert(sizeof(AllocHeader) <= c_alignment, "allocation header size is larger than max supported alignment");
        static_assert(alignof(AllocHeader) <= c_alignment, "allocation header alignment must be less or equal than max supported alignment");
    }

    void* SystemAllocator::allocate(std::size_t bytes, [[maybe_unused]] std::size_t alignment)
    {
        OSE_ASSERT(bytes > 0, "allocation size is zero");
        OSE_ASSERT(alignment <= c_alignment, "overaligned allocation is not supported in this allocator: alignment={}, maxAlignment={}", alignment, c_alignment);
        OSE_ASSERT(bytes <= c_maxAllocSize, "allocation size {} is greater than max supported allocation size {}", bytes, c_maxAllocSize);

        const std::size_t totalSize = ptr_algorithm::adjustSize(bytes + c_alignment, c_alignment);

        if(void* allocPtr = ose::aligned_malloc(totalSize, c_alignment))
        {
            AllocHeader* header = nullptr;
            header = new(allocPtr) AllocHeader;
            header->size = bytes;
            return ptr_algorithm::add(allocPtr, c_alignment);
        }

        return nullptr;
    }

    void SystemAllocator::deallocate(void* ptr)
    {
        void* allocPtr = ptr_algorithm::subtract(ptr, c_alignment);
        ose::aligned_free(allocPtr);
    }

    std::size_t SystemAllocator::allocationSize(void* ptr)
    {
        void* allocPtr = ptr_algorithm::subtract(ptr, c_alignment);
        AllocHeader* header = static_cast<AllocHeader*>(allocPtr);
        return header->size;
    }
}
