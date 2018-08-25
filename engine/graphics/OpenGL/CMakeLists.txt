
set( SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src )
set( PLATFORM_INCLUDE_DIR ${SRC_DIR} )
set( INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include )

set( SOURCES
   ${SRC_DIR}/GLDevice.cpp
   ${SRC_DIR}/GLShader.cpp
   ${SRC_DIR}/GLProgram.cpp )

set( PLATFORM_LIBRARIES )

if ( ANDROID )
    set( PLATFORM_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/Android )
    list( APPEND SOURCES
        ${SRC_DIR}/Android/AndroidGLContext.cpp
        ${SRC_DIR}/Android/AndroidGLDevice.cpp )
    list( APPEND PLATFORM_LIBRARIES 
        EGL
        GLESv2 )
endif (  )

if ( WIN32 )
    set( PLATFORM_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/Win32 )
    list( APPEND SOURCES 
        ${SRC_DIR}/Win32/Win32GLContext.cpp
        ${SRC_DIR}/Win32/Win32GLDevice.cpp )
    list( APPEND PLATFORM_LIBRARIES 
        libglew_static )
endif (  )

add_library( oceansoul-graphics-gl STATIC ${SOURCES} )

set_target_properties( oceansoul-graphics-gl PROPERTIES
		                    ARCHIVE_OUTPUT_NAME "oceansoul-graphics-gl"
		                    DEBUG_POSTFIX _d )

target_include_directories(oceansoul-graphics-gl
    PUBLIC ${INCLUDE_DIR}
    PRIVATE ${PLATFORM_INCLUDE_DIR} )

target_link_libraries(oceansoul-graphics-gl 
                        PUBLIC 
                            ${PLATFORM_LIBRARIES}
                        PRIVATE
                            oceansoul-core )