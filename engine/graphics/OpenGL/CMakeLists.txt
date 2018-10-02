
set( SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src )
set( PLATFORM_INCLUDE_DIR ${SRC_DIR} )
set( INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include )


set( SOURCES
   ${SRC_DIR}/GLDevice.cpp
   ${SRC_DIR}/GLContext.cpp
   ${SRC_DIR}/GLProgram.cpp
   ${SRC_DIR}/GLProgramUniform.cpp
   ${SRC_DIR}/GLBuffer.cpp
   ${SRC_DIR}/GLVertexLayout.cpp
   ${SRC_DIR}/GLVertexArray.cpp
   ${SRC_DIR}/GLTexture.cpp
   ${SRC_DIR}/GLResourceProxy.cpp
   ${SRC_DIR}/GLRenderer.cpp)

if ( WIN32 OR _APPLE_ )
    find_package(OpenGL REQUIRED)

    add_library( glad STATIC ${SRC_DIR}/Desktop/Vendor/glad/src/glad.c )
    target_include_directories( glad PUBLIC ${SRC_DIR}/Desktop/Vendor/glad/include )
    target_link_libraries( glad ${OPENGL_gl_LIBRARY} )

	list( APPEND SOURCES
        ${SRC_DIR}/Desktop/GLExtensions.cpp )
endif ( )

if ( ANDROID OR IOS )
    add_library( glad STATIC ${SRC_DIR}/Mobile/Vendor/glad/src/glad.c )
    target_include_directories( glad PUBLIC ${SRC_DIR}/Mobile/Vendor/glad/include )
    target_link_libraries( glad GLESv2 )

	list( APPEND SOURCES
        ${SRC_DIR}/Mobile/GLExtensions.cpp )
endif ( )

set( PLATFORM_LIBRARIES glad )

if ( ANDROID )
    set( PLATFORM_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/Mobile/Android )
    list( APPEND SOURCES
        ${SRC_DIR}/Mobile/Android/AndroidGLContext.cpp
        ${SRC_DIR}/Mobile/Android/AndroidGLDevice.cpp )
    list( APPEND PLATFORM_LIBRARIES
        EGL )
endif (  )

if ( WIN32 )
    set( PLATFORM_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/Desktop/Win32 )
    list( APPEND SOURCES
        ${SRC_DIR}/Desktop/Win32/Win32GLContext.cpp
        ${SRC_DIR}/Desktop/Win32/Win32GLDevice.cpp )
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