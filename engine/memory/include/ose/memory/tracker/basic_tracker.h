#pragma once

#include <ose/typedef.h>
#include <ose/debug.h>

#include <algorithm>

namespace ose::memory {

    class BasicTracker
    {
        std::size_t m_currentAllocations{ 0u };
        std::size_t m_allocSize{ 0u };

        std::size_t m_allocations{ 0u };
        std::size_t m_deallocations{ 0u };
        std::size_t m_allocPeakSize{ 0u };

    public:
        inline ~BasicTracker()
        {
            OSE_ASSERT(m_allocSize == 0, "on resource destroy total allocation size {} is not zero", m_allocSize);
            OSE_ASSERT(m_currentAllocations == 0, "on resource destroy total allocation count {} is not zero", m_currentAllocations);
        }

        inline void allocate(void* ptr, std::size_t size, [[maybe_unused]] std::size_t alignment)
        {
            ++m_allocations;
            ++m_currentAllocations;

            m_allocSize += size;
            m_allocPeakSize = std::max(m_allocPeakSize, m_allocSize);
        }

        inline void deallocate(void* ptr, std::size_t size)
        {
            OSE_ASSERT(m_allocations > 0, "Allocation count: {} must be greater than 0", m_allocations);
            OSE_ASSERT(m_allocSize >= size, "Alloc size ({}) is less than deallocations size ({}) ", m_allocSize, size);

            ++m_deallocations;
            --m_currentAllocatins;

            m_allocSize -= size;
        }

        inline void clear() 
        {
            m_currentAllocations = 0;
            m_allocSize = 0;
        }
    };

}