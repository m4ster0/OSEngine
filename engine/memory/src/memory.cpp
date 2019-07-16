#include "ose/memory.h"

void* operator new(std::size_t count, std::size_t align, ose::memory::IMemoryResource& resource)
{
    return resource.allocate(count, align);
}

void operator delete(void* ptr, [[maybe_unused]] std::size_t align, ose::memory::IMemoryResource& resource)
{
    resource.deallocate(ptr);
}