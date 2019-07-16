cmake_minimum_required(VERSION 3.10.0)

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library( ose-core INTERFACE )
add_library( ose::core ALIAS ose-core )

target_compile_definitions( ose-core INTERFACE 
    $<$<CONFIG:Debug>:DEBUG_OSE>
    $<$<CONFIG:Profile>:PROFILE_OSE>
    $<$<CONFIG:Release>:RELEASE_OSE> )

target_include_directories( ose-core INTERFACE 
    $<BUILD_INTERFACE:${INCLUDE_DIR}> )

target_link_libraries( ose-core
    INTERFACE fmt::fmt-header-only )