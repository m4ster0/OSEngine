#pragma once

#include "ose/typedef.h"

namespace ose {

    void* aligned_malloc(std::size_t size, std::size_t alignment);
    void  aligned_free(void* ptr);

}
