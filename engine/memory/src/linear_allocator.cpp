#include "ose/memory/allocator/linear_allocator.h"

#include "ose/memory/i_memory_resource.h"

#include "ose/memory/detail/slist_algorithms.h"
#include "ose/memory/detail/ptr_algorithms.h"

#include <ose/debug.h>

#include <limits>

namespace ose::memory {

    struct BlockNode
    {
        BlockNode*  next;
    };

    struct BlockNodeTraits
    {
        using Node          = BlockNode;
        using NodePtr       = BlockNode*;
        using ConstNodePtr  = const BlockNode*;

        static NodePtr  getNext(ConstNodePtr n) { return n->next; }
        static void     setNext(NodePtr n, NodePtr next) { n->next = next; }
    };


    namespace {
        using SListAlgo = SListAlgorithms<BlockNodeTraits>;

        constexpr std::size_t c_headerSize{ (sizeof(BlockNode) + ptr_algorithm::c_alignMaxMinus1) & ~ptr_algorithm::c_alignMaxMinus1 };

        std::size_t increaseNextBufferSize(std::size_t currentSize, float growthFactor)
        {
            const std::size_t maxSize{ std::numeric_limits<std::size_t>::max() };
            return maxSize / growthFactor < currentSize ? maxSize : currentSize * growthFactor;
        }

        std::size_t getMinimalBufferSize(std::size_t nextBufferSize, std::size_t minimalSize)
        {
            if(nextBufferSize < minimalSize)
                return minimalSize;

            return nextBufferSize;
        }
    }

    LinearAllocator::LinearAllocator(std::size_t initialSize, IMemoryResource& upstream, const Options& options):
        m_options{ options }
    {
        // m_options.initialSize = options.initialSize + !options.initialSize;
        // m_nextBlockSize = increaseNextBufferSize(m_options.initialSize, m_options.growthFactor);

        // m_initialBuffer = allocateBlock(m_options.initialSize);
        // setCurrentBuffer(m_initialBuffer, m_options.initialSize);
        // SListAlgo::init(m_initialBuffer);
    }

    LinearAllocator::~LinearAllocator()
    {
        clear();
        
        void* ptr = static_cast<void*>(m_initialBuffer);
        m_upstream->deallocate(ptr);

        m_initialBuffer = nullptr;
        m_currentBuffer = nullptr;
        m_currentBufferSize = 0u;
    }

    void* LinearAllocator::allocate(std::size_t bytes, std::size_t alignment)
    {
        //assert alignment (< max_alignment && pow2)

        std::size_t alignAdjustment;
        if(getRemainingSize(alignment, alignAdjustment) < bytes && m_options.growthEnabled)
        {
            auto blockSize = getMinimalBufferSize(m_nextBlockSize, bytes);
            BlockNode* node = allocateBlock(blockSize);
            if(node != nullptr)
            {
                setCurrentBuffer(node, blockSize);
                SListAlgo::linkAfter(m_initialBuffer, node);
                m_nextBlockSize = increaseNextBufferSize(m_nextBlockSize, m_options.growthFactor);
            }
        }

        return allocateCurrent(bytes, alignAdjustment);
    }

    void LinearAllocator::clear()
    {
        BlockNode* n = BlockNodeTraits::getNext(m_initialBuffer);
        while(n != nullptr)
        {
            void* ptr = static_cast<void*>(n);
            n = BlockNodeTraits::getNext(n);
            m_upstream->deallocate(ptr);
        }

        SListAlgo::init(m_initialBuffer);
        // setCurrentBuffer(m_initialBuffer, m_options.initialSize);
    }

    std::size_t LinearAllocator::getRemainingSize(std::size_t alignment, std::size_t& alignAdjustment) const
    {
        alignAdjustment = ptr_algorithm::adjustAlignment(m_currentBuffer, alignment);
        return alignAdjustment >= m_currentBufferSize ? 0u : m_currentBufferSize - alignAdjustment;
    }


    void* LinearAllocator::allocateCurrent(std::size_t bytes, std::size_t alignAdjustment)
    {
        std::size_t totalSize{ bytes + alignAdjustment };
        if(totalSize <= m_currentBufferSize)
        {
            void* ptr = ptr_algorithm::add(m_currentBuffer, alignAdjustment);
            m_currentBuffer = ptr_algorithm::add(m_currentBuffer, totalSize);
            m_currentBufferSize -= totalSize;
            return ptr;
        }

        //add warn fail -> totalSize > m_currentBufferSize
        return nullptr;
    }

    BlockNode* LinearAllocator::allocateBlock(std::size_t bytes)
    {
        OSE_ASSERT(bytes <= (std::size_t( -1 ) - c_headerSize), "Block size must be less than {}", ((std::size_t( -1 ) - c_headerSize)));
        return static_cast<BlockNode*>(m_upstream->allocate(bytes + c_headerSize));
    }

    void LinearAllocator::setCurrentBuffer(BlockNode* node, std::size_t size)
    {
        OSE_ASSERT_ADDRESS(node);
        void* ptr = static_cast<void*>(node);
        m_currentBuffer = ptr_algorithm::add(ptr, c_headerSize);
        m_currentBufferSize = size;
    }

}