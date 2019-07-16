#pragma once

#include "ose/memory/i_memory_resource.h"

#include "ose/memory/detail/ptr_algorithms.h"

#include <ose/typedef.h>
#include <ose/debug.h>

namespace ose::memory {

    template<class Allocator, class Tracker, class BoundsChecker>
    class MemoryResource: public IMemoryResource
    {
    public:
        template<typename T>
        using ClearMethodT = decltype(std::declval<T&>().clear());

        template<typename... AllocatorArgs>
        MemoryResource(AllocatorArgs&&... allocatorArgs)
            : m_allocator{ std::forward<AllocatorArgs>(allocatorArgs)... }
        { }

        virtual ~MemoryResource() = default;

        const Allocator& getAllocator() const { return m_allocator; }
        const Tracker& getTracker() const { return m_tracker; }

        //if allocator.clear() void clear()
        //std::enable_if_t<ose::stl::is_detected_exact<void, ClearMethodT, Allocator>::value, void>
        //   clear()

    protected:
        Allocator m_allocator;
        Tracker m_tracker{ };
        BoundsChecker m_boundsChecker{ };

        virtual void* internalAllocate(std::size_t bytes, std::size_t alignment) override
        {
            constexpr std::size_t offset = BoundsChecker::getSize();
            constexpr std::size_t maxBytes = std::size_t( -1 ) - (2 * offset);

            OSE_ASSERT(offset % alignment == 0, "bounds checker size ({}) must be multiple of alignment ({})", offset, alignment);
            OSE_ASSERT(bytes <= maxBytes, "size ({}) exceeds size max value ({})", bytes, maxBytes);

            const std::size_t totalSize = offset + bytes + offset;
            if(void* allocPtr = m_allocator.allocate(totalSize, alignment))
            {
                OSEbyte* ptr = static_cast<OSEbyte*>(allocPtr) + offset;

                m_tracker.allocate(allocPtr, totalSize, alignment);
                m_boundsChecker.guard(ptr - offset);
                m_boundsChecker.guard(ptr + bytes);

                return static_cast<void*>(ptr);
            }

            return nullptr;
        }

        virtual void internalDeallocate(void* ptr) override
        {
            constexpr std::size_t offset = BoundsChecker::getSize();

            void* allocPtr = ptr_algorithm::subtract(ptr, offset); //returns ptr to total allocated memory

            const std::size_t allocSize = m_allocator.allocationSize(allocPtr);
            const std::size_t originalSize = allocSize - (2 * offset);

            OSEbyte* bytePtr = static_cast<OSEbyte*>(ptr);
            m_boundsChecker.validate(bytePtr - offset);
            m_boundsChecker.validate(bytePtr + originalSize);

            m_tracker.deallocate(allocPtr, allocSize);

            m_allocator.deallocate(allocPtr);
        }

        virtual std::size_t internalAllocationSize(void* ptr) override
        {
            return m_allocator.allocationSize(ptr);
        }
    };

}