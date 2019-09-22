#include "ose/memory/allocator/linear_allocator.h"

#include "ose/memory/i_memory_resource.h"
#include "ose/memory/detail/ptr_algorithms.h"

#include <ose/debug.h>

namespace ose::memory {

    // struct BlockNode
    // {
    //     BlockNode*  next;
    // };

    // struct BlockNodeTraits
    // {
    //     using Node          = BlockNode;
    //     using NodePtr       = BlockNode*;
    //     using ConstNodePtr  = const BlockNode*;

    //     static NodePtr  getNext(ConstNodePtr n) { return n->next; }
    //     static void     setNext(NodePtr n, NodePtr next) { n->next = next; }
    // };


    // namespace {
    //     using SListAlgo = SListAlgorithms<BlockNodeTraits>;

    //     constexpr std::size_t c_headerSize{ (sizeof(BlockNode) + ptr_algorithm::c_alignMaxMinus1) & ~ptr_algorithm::c_alignMaxMinus1 };

    //     std::size_t increaseNextBufferSize(std::size_t currentSize, float growthFactor)
    //     {
    //         const std::size_t maxSize{ std::numeric_limits<std::size_t>::max() };
    //         return maxSize / growthFactor < currentSize ? maxSize : currentSize * growthFactor;
    //     }

    //     std::size_t getMinimalBufferSize(std::size_t nextBufferSize, std::size_t minimalSize)
    //     {
    //         if(nextBufferSize < minimalSize)
    //             return minimalSize;

    //         return nextBufferSize;
    //     }
    // }

    namespace {
        struct AllocHeader { std::size_t size; };

        constexpr std::size_t c_allocOffset = sizeof(AllocHeader);
        constexpr std::size_t c_allocMinAlignment = alignof(AllocHeader);

        constexpr std::size_t c_maxAllocSize = std::size_t( -1 ) - 2 * c_allocOffset - 1;
    }

    LinearAllocator::LinearAllocator(void* begin, void* end):
        m_buffer{ begin }, m_currentPosition{ begin }
    {
        const std::size_t size = reinterpret_cast<std::uintptr_t>(end) - reinterpret_cast<std::uintptr_t>(begin);

        OSE_ASSERT_ADDRESS(m_buffer);
        OSE_ASSERT(size > 0, "Buffer size must be greater than 0");

        m_bufferSize = size;
        m_currentSize = size;
    }

    LinearAllocator::LinearAllocator(std::size_t size, IMemoryResource& upstream):
        m_upstream{ &upstream }
    {
        if(void* alloc = m_upstream->allocate(size); alloc != nullptr)
        {
            m_buffer = alloc;
            m_currentPosition = alloc;
            m_bufferSize = size;
            m_currentSize = size;
        }
    }

    LinearAllocator::~LinearAllocator()
    {
        if(m_buffer != nullptr && m_upstream != nullptr)
            m_upstream->deallocate(m_buffer);
    }

    void* LinearAllocator::allocate(std::size_t bytes, std::size_t alignment)
    {
        const std::size_t totalBytes = bytes + c_allocOffset;
        OSE_ASSERT(bytes > 0 && bytes <= c_maxAllocSize, "allocation size {} is not within bounds ({}, {})", bytes, 0, c_maxAllocSize);

        const std::size_t allocAlignment = std::max(c_allocMinAlignment, alignment);

        std::size_t alignAdjustment;
        if( remainingSize(allocAlignment, alignAdjustment) >= totalBytes )
        {
            void* allocPtr = ptr_algorithm::add(m_currentPosition, alignAdjustment);
            AllocHeader* header = nullptr;
            header = new(allocPtr) AllocHeader;
            header->size = bytes;
            m_currentPosition = ptr_algorithm::add(allocPtr, totalBytes);
            m_bufferSize -= alignAdjustment + totalBytes;
            return ptr_algorithm::add(allocPtr, c_allocOffset);
        }

        return nullptr;
    }

    void LinearAllocator::clear()
    {
        m_currentPosition = m_buffer;
        m_currentSize = m_bufferSize;
    }

    std::size_t LinearAllocator::allocationSize(void* ptr)
    {
        void* allocPtr = ptr_algorithm::subtract(ptr, c_allocOffset);
        AllocHeader* header = static_cast<AllocHeader*>(allocPtr);
        return header->size;
    }

    std::size_t LinearAllocator::remainingSize(std::size_t alignment, std::size_t& alignAdjustment)
    {
        const std::size_t offsetAlignAdjustment = ptr_algorithm::adjustAlignment(m_currentPosition, alignment, c_allocOffset);
        OSE_ASSERT(offsetAlignAdjustment >= c_allocOffset, "Offset included align adjustment {} is less than header offset {}", offsetAlignAdjustment, c_allocOffset);
        alignAdjustment = offsetAlignAdjustment - c_allocOffset;
        return alignAdjustment >= m_currentSize ? 0u : m_currentSize - alignAdjustment;
    }

    // void* LinearAllocator::allocate(std::size_t bytes, std::size_t alignment)
    // {
    //     //assert alignment (< max_alignment && pow2)

    //     std::size_t alignAdjustment;
    //     if(getRemainingSize(alignment, alignAdjustment) < bytes && m_options.growthEnabled)
    //     {
    //         auto blockSize = getMinimalBufferSize(m_nextBlockSize, bytes);
    //         BlockNode* node = allocateBlock(blockSize);
    //         if(node != nullptr)
    //         {
    //             setCurrentBuffer(node, blockSize);
    //             SListAlgo::linkAfter(m_initialBuffer, node);
    //             m_nextBlockSize = increaseNextBufferSize(m_nextBlockSize, m_options.growthFactor);
    //         }
    //     }

    //     return allocateCurrent(bytes, alignAdjustment);
    // }

    // void LinearAllocator::clear()
    // {
    //     BlockNode* n = BlockNodeTraits::getNext(m_initialBuffer);
    //     while(n != nullptr)
    //     {
    //         void* ptr = static_cast<void*>(n);
    //         n = BlockNodeTraits::getNext(n);
    //         m_upstream->deallocate(ptr);
    //     }

    //     SListAlgo::init(m_initialBuffer);
    //     // setCurrentBuffer(m_initialBuffer, m_options.initialSize);
    // }

    // std::size_t LinearAllocator::getRemainingSize(std::size_t alignment, std::size_t& alignAdjustment) const
    // {
    //     alignAdjustment = ptr_algorithm::adjustAlignment(m_currentBuffer, alignment);
    //     return alignAdjustment >= m_currentBufferSize ? 0u : m_currentBufferSize - alignAdjustment;
    // }


    // void* LinearAllocator::allocateCurrent(std::size_t bytes, std::size_t alignAdjustment)
    // {
    //     std::size_t totalSize{ bytes + alignAdjustment };
    //     if(totalSize <= m_currentBufferSize)
    //     {
    //         void* ptr = ptr_algorithm::add(m_currentBuffer, alignAdjustment);
    //         m_currentBuffer = ptr_algorithm::add(m_currentBuffer, totalSize);
    //         m_currentBufferSize -= totalSize;
    //         return ptr;
    //     }

    //     //add warn fail -> totalSize > m_currentBufferSize
    //     return nullptr;
    // }

    // BlockNode* LinearAllocator::allocateBlock(std::size_t bytes)
    // {
    //     OSE_ASSERT(bytes <= (std::size_t( -1 ) - c_headerSize), "Block size must be less than {}", ((std::size_t( -1 ) - c_headerSize)));
    //     return static_cast<BlockNode*>(m_upstream->allocate(bytes + c_headerSize));
    // }

    // void LinearAllocator::setCurrentBuffer(BlockNode* node, std::size_t size)
    // {
    //     OSE_ASSERT_ADDRESS(node);
    //     void* ptr = static_cast<void*>(node);
    //     m_currentBuffer = ptr_algorithm::add(ptr, c_headerSize);
    //     m_currentBufferSize = size;
    // }

}
