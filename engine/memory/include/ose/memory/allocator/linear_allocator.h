#pragma once

#include <ose/typedef.h>

namespace ose::memory { class IMemoryResource; }

namespace ose::memory {

    struct BlockNode;

    /**
     *  Linear allocator with optional overgrowth.
     *  Not possible to free single allocation, only whole buffer can be reset.
     *  Reset causes to deallocate any overgrowth blocks allocated from upstream. 
     */
    class LinearAllocator final
    {
    public:
        struct Options
        {
            bool            growthEnabled{ false };
            float           growthFactor{ 2.0f };
        };

        LinearAllocator(void* begin, void* end);
        LinearAllocator(std::size_t initialSize, IMemoryResource& upstream, const Options& options);
        ~LinearAllocator();

        LinearAllocator(const LinearAllocator&) = delete;
        LinearAllocator(LinearAllocator&&) = delete;
        LinearAllocator& operator=(const LinearAllocator&) = delete;
        LinearAllocator& operator=(LinearAllocator&&) = delete;

        void*       allocate(std::size_t bytes, std::size_t alignment);
        void        clear();

    private:
        std::size_t     getRemainingSize(std::size_t alignment, std::size_t& alignAdjustment) const;
        void*           allocateCurrent(std::size_t bytes, std::size_t alignAdjustment);

        BlockNode*      allocateBlock(std::size_t bytes);
        void            setCurrentBuffer(BlockNode* node, std::size_t size);

        Options m_options{ };
        IMemoryResource* m_upstream{ nullptr };

        BlockNode* m_initialBuffer{ nullptr };
        void* m_currentBuffer{ nullptr };
        std::size_t m_currentBufferSize{ 0u };

        std::size_t m_nextBlockSize{ 0u };
    };

}