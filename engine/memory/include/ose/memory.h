#pragma once

#include "ose/memory/i_memory_resource.h"

#include <new>

void* operator new(std::size_t count, std::size_t align, ose::memory::IMemoryResource& resource);
void operator delete(void* ptr, std::size_t align, ose::memory::IMemoryResource& resource);

namespace ose {

    template<typename T, typename... Args>
    inline T* construct(memory::IMemoryResource& resource, Args&&... args);

    template<typename T>
    inline T* construct_default(memory::IMemoryResource& resource);

    template<typename T, typename... Args>
    inline T* construct_array(memory::IMemoryResource& resource, std::size_t size, Args&&... args);

    template<typename T>
    inline T* construct_array_default(memory::IMemoryResource& resource, std::size_t size);

    template<typename T>
    inline void destruct(T* ptr, memory::IMemoryResource& resource);

    template<typename T>
    inline void destruct_array(T* ptr, std::size_t size, memory::IMemoryResource& resource);

}

#include "ose/memory.inl"