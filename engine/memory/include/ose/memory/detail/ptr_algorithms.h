#pragma once

#include <ose/typedef.h>

namespace ose::memory {

    namespace ptr_algorithm
    {
        constexpr std::size_t c_alignMaxMinus1{ alignof(std::max_align_t) - 1u };

        inline constexpr bool isPowerOf2(std::size_t num)
        {
            return num > 0 && ((num & (num - 1)) == 0);
        }

        inline const void* add(const void* ptr, std::size_t bytes)
        {
            const OSEbyte* bytePtr = static_cast<const OSEbyte*>(ptr);
            return static_cast<const void*>(bytePtr + bytes);
        }

        inline void* add(void* ptr, std::size_t bytes)
        {
            OSEbyte* bytePtr = static_cast<OSEbyte*>(ptr);
            return static_cast<void*>(bytePtr + bytes);
        }

        inline const void* subtract(const void* ptr, std::size_t bytes)
        {
            const OSEbyte* bytePtr = static_cast<const OSEbyte*>(ptr);
            return static_cast<const void*>(bytePtr - bytes);
        }

        inline void* subtract(void* ptr, std::size_t bytes)
        {
            OSEbyte* bytePtr = static_cast<OSEbyte*>(ptr);
            return static_cast<void*>(bytePtr - bytes);
        }

        inline std::size_t adjustAlignment(void* ptr, std::size_t alignment, std::size_t offset)
        {
            const std::uintptr_t alignmentMinus1{ alignment - 1u };
            const std::uintptr_t addressOffset{ static_cast<std::uintptr_t>(offset) };
            const std::uintptr_t currAddress{ reinterpret_cast<std::uintptr_t>(ptr) };
            const std::uintptr_t alignedAddress{ (currAddress + addressOffset + alignmentMinus1) & ~alignmentMinus1 };
            return alignedAddress - currAddress;
        }

        inline std::size_t adjustAlignment(void* ptr, std::size_t alignment)
        {
            return adjustAlignment(ptr, alignment, 0u);
        }

        inline constexpr std::size_t adjustSize(std::size_t size, std::size_t alignment)
        {
            constexpr std::size_t alignmentMinus1{ alignment - 1u };
            return (size + alignmentMinus1) & ~alignmentMinus1;
        }

        inline bool isAddressAligned(void* ptr, std::size_t alignment)
        {
            const std::uintptr_t alignmentMinus1{ alignment - 1u };
            const std::uintptr_t currAddress{ reinterpret_cast<std::uintptr_t>(ptr) };
            return (currAddress & alignmentMinus1) == 0;
        }
    }

}
