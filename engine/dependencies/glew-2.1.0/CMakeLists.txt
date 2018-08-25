cmake_minimum_required( VERSION 3.4.1 )
project( "glew" )

set( SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src )
set( INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include )
set( RC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build )

option( glew-cmake_BUILD_SINGLE_CONTEXT "Build the single context glew library" ON )
option( glew-cmake_BUILD_MULTI_CONTEXT "Build the multi context glew library" OFF )

set( LIBGLEW_SRCS ${SRC_DIR}/glew.c )

if ( MSVC )
	list( APPEND LIBGLEW_SRCS ${RC_DIR}/glew.rc )
endif (  )

find_package(OpenGL REQUIRED)

if ( glew-cmake_BUILD_SINGLE_CONTEXT )
	add_library( libglew_static STATIC ${LIBGLEW_SRCS} )
	set_target_properties( libglew_static 
                            PROPERTIES
		                        ARCHIVE_OUTPUT_NAME "glew"
		                        DEBUG_POSTFIX d )

    target_compile_definitions( libglew_static INTERFACE GLEW_STATIC GLEW_NO_GLU )
    if ( WIN32 )
        target_compile_definitions( libglew_static 
            PRIVATE 
                WIN32_MEAN_AND_LEAN
                VC_EXTRALEAN
                GLEW_BUILD
                _CRT_SECURE_NO_WARNINGS )
    endif (  )

	target_include_directories( libglew_static PUBLIC ${INCLUDE_DIR} )
	target_link_libraries( libglew_static ${OPENGL_gl_LIBRARY} )
endif (  )

if ( glew-cmake_BUILD_MULTI_CONTEXT )
	add_library( libglewmx_static STATIC ${LIBGLEW_SRCS} )
	set_target_properties( libglewmx_static 
                            PROPERTIES
		                        ARCHIVE_OUTPUT_NAME "glewmx"
		                        DEBUG_POSTFIX d )

	target_compile_definitions( libglewmx_static INTERFACE GLEW_MX GLEW_STATIC GLEW_NO_GLU )
    if ( WIN32 )
        target_compile_definitions( libglewmx_static 
            PRIVATE 
                WIN32_MEAN_AND_LEAN
                VC_EXTRALEAN
                GLEW_BUILD
                _CRT_SECURE_NO_WARNINGS )
    endif (  )

	target_include_directories( libglewmx_static PUBLIC ${INCLUDE_DIR} )
	target_link_libraries( libglewmx_static ${OPENGL_gl_LIBRARY} )
endif (  )