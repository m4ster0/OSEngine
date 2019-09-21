cmake_minimum_required(VERSION 3.10.0)

project(oceansoul-engine)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set( SUPPORTED_PLATFORMS
        OSE_WIN OSE_MACOS OSE_LINUX
        OSE_ANDROID OSE_IOS )

if(NOT DEFINED TARGET_PLATFORM)
    message( FATAL_ERROR "Target platform was not specified. Supported platforms: ${SUPPORTED_PLATFORMS}" )
endif()

if(NOT ${TARGET_PLATFORM} IN_LIST SUPPORTED_PLATFORMS)
    message( FATAL_ERROR "Target platform ${TARGET_PLATFORM} not supported. Supported platforms: ${SUPPORTED_PLATFORMS}")
endif()

option(${TARGET_PLATFORM} "Target platform option" ON)

add_subdirectory(dependencies)
add_subdirectory(core)
add_subdirectory(memory)
