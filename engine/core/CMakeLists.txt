cmake_minimum_required(VERSION 3.10.0)

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(SOURCES )

if(OSE_WIN)
    list(APPEND SOURCES ${SRC_DIR}/alloc_win.cpp)
endif()

if(OSE_ANDROID)
    list(APPEND SOURCES ${SRC_DIR}/alloc_posix.cpp)
endif()

if(OSE_MACOS)
    list(APPEND SOURCES ${SRC_DIR}/alloc_posix.cpp)
endif()

if(OSE_IOS)
    list(APPEND SOURCES ${SRC_DIR}/alloc_posix.cpp)
endif()

file(GLOB_RECURSE HEADERS
    ${INCLUDE_DIR} *.h
    ${INCLUDE_DIR} *.hpp
    ${INCLUDE_DIR} *.inl)

add_library( ose-core STATIC ${SOURCES} ${HEADERS} )
add_library( ose::core ALIAS ose-core )

source_group(TREE ${INCLUDE_DIR} PREFIX headers FILES ${HEADERS})
source_group(TREE ${SRC_DIR} PREFIX sources FILES ${SOURCES})

target_compile_definitions( ose-core PUBLIC
    $<$<CONFIG:Debug>:DEBUG_OSE>
    $<$<CONFIG:Profile>:PROFILE_OSE>
    $<$<CONFIG:Release>:RELEASE_OSE> )

target_include_directories( ose-core PUBLIC
    ${INCLUDE_DIR} )

target_link_libraries( ose-core
    PUBLIC fmt::fmt-header-only )
