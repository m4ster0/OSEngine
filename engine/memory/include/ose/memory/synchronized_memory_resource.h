#pragma once

#include "ose/memory/memory_resource.h"

#include <mutex>
#include <type_traits>

namespace ose::memory {

    template<class SynchronizationPrimitive, class MemoryResourceT> //requires std::is_base_of<IMemoryResource, MemoryResourceT>::value
    class SynchronizedMemoryResource final: public MemoryResourceT
    {
        static_assert(std::is_base_of<IMemoryResource, MemoryResourceT>::value, "MemoryResourceT must be derived from IMemoryResource");

    public:
        template<typename... Args>
        SynchronizedMemoryResource(Args&&... args)
            : MemoryResourceT(std::forward<Args>(args)...)
        {}

    protected:
        SynchronizationPrimitive m_sychronizationPrimitive{ };

        void* internalAllocate(std::size_t bytes, std::size_t alignment) override
        {
            std::unique_lock{ m_sychronizationPrimitive };

            return MemoryResourceT::internalAllocate(bytes, alignment);
        }

        void internalDeallocate(void* ptr) override
        {
            std::unique_lock{ m_sychronizationPrimitive };

            MemoryResourceT::internalDeallocate(ptr);
        }
    };

}