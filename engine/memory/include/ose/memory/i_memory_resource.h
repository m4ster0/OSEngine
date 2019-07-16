#pragma once

#include <ose/typedef.h>
#include <ose/debug.h>

namespace ose::memory {

    class IMemoryResource
    {
    public:
        IMemoryResource() = default;
        virtual ~IMemoryResource() = default;

        IMemoryResource(const IMemoryResource&) = delete;
        IMemoryResource(IMemoryResource&&) = delete;

        IMemoryResource& operator=(const IMemoryResource&) = delete;
        IMemoryResource& operator=(IMemoryResource&&) = delete;

        /**
         * Allocates memory of given size and alignment
         * @param bytes size of allocation
         * @param alignment min alignment of allocation. By default max possible alignment for platform
         * @return pointer to allocated memory or nullptr if allocation fails
         */
        inline void* allocate(std::size_t bytes, std::size_t alignment = alignof(std::max_align_t))
        {
            return internalAllocate(bytes, alignment);
        }

        /**
         * Deallocates memory pointed by given ptr.
         * @param ptr Pointer to allocated memory, must be not null and 
         * pointing to memory allocated by this resource otherwise behaviour is undefined
         * @return void
         */
        inline void deallocate(void* ptr)
        {
            internalDeallocate(ptr);
        }

        /**
         * Gives size of given allocation
         * @param ptr Pointer to allocated memory, must be not null and
         * pointing to memory allocated by this resource otherwise behaviour is undefined
         * @return allocation size
         */
        inline std::size_t allocationSize(void* ptr)
        {
            return internalAllocationSize(ptr);
        }

    protected:
        virtual void*       internalAllocate(std::size_t bytes, std::size_t alignment) = 0;
        virtual void        internalDeallocate(void* ptr) = 0;
        virtual std::size_t internalAllocationSize(void* ptr) = 0;
    };

    inline bool operator==(const IMemoryResource& lhs, const IMemoryResource& rhs)
    {
        return &lhs == &rhs;
    }

    inline bool operator!=(const IMemoryResource& lhs, const IMemoryResource& rhs)
    {
        return &lhs != &rhs;
    }
}