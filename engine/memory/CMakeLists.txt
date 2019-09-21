cmake_minimum_required(VERSION 3.10.0)

option(OSE_MEMORY_PEDANTIC "Enable extra warnings." ${OSE_PEDANTIC})
option(OSE_MEMORY_WERROR "Error on compiler warnings." ${OSE_WERROR})

# Options that control generation of various targets.
option(OSE_MEMORY_TEST "Generate the test target." ${OSE_TEST})

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(OSE_PEDANTIC_COMPILE_FLAGS -Wall -Wextra -pedantic -Wconversion -Wno-sign-conversion -Wzero-as-null-pointer-constant)
    set(OSE_WERROR_FLAG -Werror)
endif ()

if (MSVC)
    set(OSE_PEDANTIC_COMPILE_FLAGS /W3)
    set(OSE_WERROR_FLAG /WX)
endif ()

set( INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include )
set( SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src )

file(GLOB_RECURSE HEADERS
    ${INCLUDE_DIR} *.h
    ${INCLUDE_DIR} *.hpp
    ${INCLUDE_DIR} *.inl)

set( SOURCES
    ${SRC_DIR}/memory.cpp
    ${SRC_DIR}/system_allocator.cpp
    ${SRC_DIR}/linear_allocator.cpp )

add_library( ose-memory STATIC ${SOURCES} ${HEADERS} )
add_library( ose::memory ALIAS ose-memory )

source_group(TREE ${INCLUDE_DIR} PREFIX headers FILES ${HEADERS})
source_group(TREE ${SRC_DIR} PREFIX sources FILES ${SOURCES})

set_target_properties( ose-memory PROPERTIES
		                    ARCHIVE_OUTPUT_NAME "ose-memory"
		                    DEBUG_POSTFIX -d )

target_compile_features( ose-memory PUBLIC cxx_std_17)

if (OSE_MEMORY_PEDANTIC)
    target_compile_options(ose-memory PRIVATE ${OSE_PEDANTIC_COMPILE_FLAGS})
endif ()
if (OSE_MEMORY_WERROR)
    target_compile_options(ose-memory PRIVATE ${OSE_WERROR_FLAG})
endif ()

target_include_directories(ose-memory
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> )

target_link_libraries(ose-memory PUBLIC ose-core )

if ( OSE_MEMORY_TEST )
    enable_testing()
    add_subdirectory(test)
endif (  )