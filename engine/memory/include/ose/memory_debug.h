#pragma once

#include <ose/debug.h>

#if defined(OSE_ASSERT_ALLOC_FAIL)
#define OSE_ALLOC_FAIL(size, align) OSE_ASSERT_FAIL("Allocation(size={}, align={}) failed", size, align)
#else
#define OSE_ALLOC_FAIL(size, align)
#endif
