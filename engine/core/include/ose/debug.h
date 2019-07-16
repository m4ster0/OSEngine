#pragma once

#include "ose/debug/assertion.h"
#include "ose/debug/debugger.h"

#define OSE_FILE_INFO ose::debug::FileInfo(__FILE__, __LINE__)

#ifdef DEBUG_OSE
    #define OSE_ASSERT(condition, format, ...) (condition) ? (void) 0 : (ose::debug::Assertion(OSE_FILE_INFO, "Assertion \"" #condition "\" failed. " format).raise(__VA_ARGS__), ose::debug::debugbreak())
#else
    #define OSE_ASSERT(condition, format, ...)
#endif // DEBUG_OSE

#define OSE_ASSERT_ADDRESS(address) OSE_ASSERT((address) != nullptr, "{} ptr is nullptr", #address)