#define BOOST_CONFIG_SUPPRESS_OUTDATED_MESSAGE
#define BOOST_TEST_MAIN

#include <boost/test/unit_test.hpp>

#include <ose/memory/allocator/system_allocator.h>
#include <ose/memory/detail/ptr_algorithms.h>

using namespace ose::memory;

void allocationTest(const std::size_t size, const std::size_t align)
{
    SystemAllocator allocator;

    void* alloc = allocator.allocate(size, align);

    BOOST_CHECK(ptr_algorithm::isAddressAligned(alloc, align));
    BOOST_CHECK(allocator.allocationSize(alloc) == size);

    allocator.deallocate(alloc);
}

BOOST_AUTO_TEST_CASE(AllocationTest)
{
    allocationTest(16, 1);
    allocationTest(16, 2);
    allocationTest(16, 4);
    allocationTest(16, 8);
    allocationTest(16, 16);

    allocationTest(128, 8);
    allocationTest(12, 16);
    allocationTest(31, 1);
    allocationTest(63, 2);


    allocationTest(1024 * 1024 * 16, 16); //16 mb alloc
    allocationTest(1024 * 1024 * 64, 16); //64 mb alloc
}

BOOST_AUTO_TEST_CASE(AlignmentFailureTest)
{
    SystemAllocator allocator;

    constexpr std::size_t size = 2048;
    void* alloc = allocator.allocate(size, size);

    BOOST_CHECK(!ptr_algorithm::isAddressAligned(alloc, size)); //it is possible for allocation to be aligned correctly but this is highly unlikely
    BOOST_CHECK(allocator.allocationSize(alloc) == size);

    allocator.deallocate(alloc);
}

BOOST_AUTO_TEST_CASE(AllocationFailureTest)
{
    SystemAllocator allocator;

    constexpr std::size_t size = std::size_t( -1 ) - 31u;
    constexpr std::size_t align = 16;
    void* alloc = allocator.allocate(size, align);

    BOOST_CHECK( alloc == nullptr );
}