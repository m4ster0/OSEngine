cmake_minimum_required(VERSION 3.4.1)

project(oceansoul-engine)

option( ose-cmake_BUILD_TESTS "Build tests" ON )

if ( (NOT ANDROID) AND ose-cmake_BUILD_TESTS )
    set(Boost_USE_STATIC_LIBS ON)
    find_package(Boost COMPONENTS unit_test_framework REQUIRED)
    enable_testing()
endif (  )
add_subdirectory(dependencies)
add_subdirectory(core)
add_subdirectory(graphics)