#pragma once

#include <ose/typedef.h>

namespace ose::memory { class IMemoryResource; }

namespace ose::memory {

    /**
     *  Linear allocator.
     *  Not possible to free single allocation, only whole buffer can be reset.
     */
    class LinearAllocator final
    {
    public:
        LinearAllocator(void* begin, void* end);
        LinearAllocator(std::size_t size, IMemoryResource& upstream);
        ~LinearAllocator();

        LinearAllocator(const LinearAllocator&) = delete;
        LinearAllocator& operator=(const LinearAllocator&) = delete;

        LinearAllocator(LinearAllocator&&);
        LinearAllocator& operator=(LinearAllocator&&);

        void*       allocate(std::size_t bytes, std::size_t alignment);
        void        clear();

        std::size_t allocationSize(void* ptr);

    private:
        std::size_t remainingSize(std::size_t alignment, std::size_t& alignAdjustment);

        void* m_buffer{ nullptr };
        void* m_currentPosition{ nullptr };
        std::size_t m_bufferSize{ 0u };
        std::size_t m_currentSize{ 0u };
        IMemoryResource* m_upstream{ nullptr };
    };

}
