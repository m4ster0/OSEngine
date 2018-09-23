set( SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src )
set( INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include )

set(SRC_FILES
    ${SRC_DIR}/Math/Geometry.cpp
    ${SRC_DIR}/Math/Plane.cpp
    ${SRC_DIR}/Math/Cube.cpp
    ${SRC_DIR}/Timer.cpp
    ${SRC_DIR}/Logger.cpp
    ${SRC_DIR}/GraphicsResourceDescriptor.cpp
    ${SRC_DIR}/Platform.cpp
    ${SRC_DIR}/Image.cpp
    ${SRC_DIR}/ImageFactory.cpp
    ${SRC_DIR}/File.cpp
    ${SRC_DIR}/FileDevice.cpp
    ${SRC_DIR}/FileSystem.cpp )

set(PLATFORM_INCLUDE )
set(PLATFORM_SRC_FILES )
set(PLATFORM_LIBS )
set(PLATFORM_LIBS_PRIVATE )

if (WIN32)
    set(PLATFORM_SRC_FILES
           ${SRC_DIR}/Win32/Win32Platform.cpp
           ${SRC_DIR}/Win32/Win32ConsoleLogSink.cpp
           ${SRC_DIR}/Win32/Win32File.cpp
           ${SRC_DIR}/Win32/Win32FileDiskDevice.cpp
           ${SRC_DIR}/Win32/ose_main_win32.cpp )

    set(PLATFORM_INCLUDE
           ${SRC_DIR}/Win32 )
elseif (ANDROID)
    add_library(native-app-glue STATIC
           ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c )

    target_include_directories(native-app-glue PUBLIC
           ${ANDROID_NDK}/sources/android/native_app_glue )

    set(PLATFORM_SRC_FILES
           ${SRC_DIR}/Android/AndroidPlatform.cpp
           ${SRC_DIR}/Android/AndroidConsoleLogSink.cpp
           ${SRC_DIR}/Android/AndroidAssetFile.cpp
           ${SRC_DIR}/Android/AndroidAssetFileDevice.cpp
           ${SRC_DIR}/Android/PosixFile.cpp
           ${SRC_DIR}/Android/PosixFileDiskDevice.cpp
           ${SRC_DIR}/Android/ose_main_android.cpp)

    set(PLATFORM_INCLUDE
           ${SRC_DIR}/Android )

    set(PLATFORM_LIBS
           android
           log )

    set(PLATFORM_LIBS_PRIVATE
           native-app-glue )
endif()


add_library( oceansoul-core STATIC
             ${SRC_FILES}
             ${PLATFORM_SRC_FILES} )

set_target_properties( oceansoul-core
                       PROPERTIES
		                   ARCHIVE_OUTPUT_NAME "oceansoul-core"
		                   DEBUG_POSTFIX _d )

target_include_directories( oceansoul-core
                            PUBLIC
                                ${INCLUDE_DIR}
                                ${PLATFORM_INCLUDE} )

target_link_libraries( oceansoul-core
                       PUBLIC ${PLATFORM_LIBS}
                       PRIVATE ${PLATFORM_LIBS_PRIVATE} )

target_compile_definitions( oceansoul-core
                            PUBLIC $<$<CONFIG:DEBUG>:DEBUG_OSE> )

# tests
if ( ose-cmake_BUILD_TESTS )
    set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test )

    set(TEST_SRC
            ${TEST_DIR}/MainTest.cpp
            ${TEST_DIR}/SignalTest.cpp
            ${TEST_DIR}/EventBusTest.cpp
            ${TEST_DIR}/TimerTest.cpp
            ${TEST_DIR}/Math/VectorTest.cpp
            ${TEST_DIR}/Math/MatrixTest.cpp
            ${TEST_DIR}/Math/OperationTest.cpp)

    add_executable(oceansoul-core-tests ${TEST_SRC})
    target_include_directories(oceansoul-core-tests PRIVATE ${Boost_INCLUDE_DIRS})
    target_link_libraries(oceansoul-core-tests PRIVATE
                            oceansoul-core
                            ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} )

    add_test(core_tests oceansoul-core-tests)
endif ( )