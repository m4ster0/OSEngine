#include "ose/alloc.h"

#include <malloc.h>

namespace ose {

    void* aligned_malloc(std::size_t size, std::size_t alignment)
    {
        return ::_aligned_malloc(size, alignment);
    }

    void aligned_free(void* ptr)
    {
        ::_aligned_free(ptr);
    }
}
