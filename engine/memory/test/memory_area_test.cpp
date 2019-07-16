#define BOOST_CONFIG_SUPPRESS_OUTDATED_MESSAGE
#define BOOST_TEST_MAIN

#include <boost/test/unit_test.hpp>

#include <ose/memory/area/stack_memory_area.h>
#include <ose/memory/detail/ptr_algorithms.h>

#include <cstdint>
#include <iostream>

BOOST_AUTO_TEST_CASE(StackMemoryTest)
{
    constexpr std::size_t stackSize{ 16u };
    ose::memory::StackMemoryArea<stackSize> area;

    //check size range returned
    const std::size_t areaSize = reinterpret_cast<std::uintptr_t>(area.end()) - reinterpret_cast<std::uintptr_t>(area.begin());
    BOOST_CHECK(stackSize == areaSize);

    //check total area memory size
    const std::size_t totalSize = stackSize;
    BOOST_CHECK(totalSize == sizeof(ose::memory::StackMemoryArea<stackSize>));

    BOOST_CHECK(ose::memory::ptr_algorithm::isAddressAligned(area.begin(), alignof(std::max_align_t)));
}

BOOST_AUTO_TEST_CASE(VirtualMemoryAreaTest)
{
    
}