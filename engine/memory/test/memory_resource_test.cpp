#define BOOST_CONFIG_SUPPRESS_OUTDATED_MESSAGE
#define BOOST_TEST_MAIN

#include <boost/test/unit_test.hpp>

#include <ose/memory.h>
#include <ose/memory/memory_resource.h>
#include <ose/memory/allocator/system_allocator.h>
#include <ose/memory/tracker/no_tracker.h>
#include <ose/memory/bounds_checker/no_bounds_checker.h>

BOOST_AUTO_TEST_CASE(MemoryResourceSanityTest)
{
    using namespace ose::memory;

    MemoryResource<SystemAllocator, NoTracker, NoBoundsChecker> systemResource{ };

    int* intPtr = ose::construct<int>(systemResource, 10);
    int* intPtr2 = ose::construct_default<int>(systemResource);

    int* intArray = ose::construct_array<int>(systemResource, 10, 2);

    int* intArray2 = ose::construct_array_default<int>(systemResource, 10);

    BOOST_CHECK(intPtr != nullptr);
    BOOST_CHECK(*intPtr == 10);

    ose::destruct_array(intArray2, 10, systemResource);
    intArray2 = nullptr;

    ose::destruct_array(intArray, 10, systemResource);
    intArray = nullptr;

    ose::destruct(intPtr2, systemResource);
    intPtr2 = nullptr;

    ose::destruct(intPtr, systemResource);
    intPtr = nullptr;

}

BOOST_AUTO_TEST_CASE(TimerReset)
{

}