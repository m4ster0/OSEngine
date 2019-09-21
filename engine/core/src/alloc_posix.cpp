#include "ose/alloc.h"

#include <stdlib.h>

namespace ose {

    void* aligned_malloc(std::size_t size, std::size_t alignment)
    {
        void* result;
        if(::posix_memalign(&result, alignment, size))
            result = nullptr;

        return result;
    }

    void aligned_free(void* ptr)
    {
        ::free(ptr);
    }
}
