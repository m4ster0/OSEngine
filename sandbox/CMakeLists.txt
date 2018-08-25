set( SRC_COMMON
    ${CMAKE_CURRENT_SOURCE_DIR}/Common/src/TestGame.cpp )

add_library( sandbox-common STATIC
    ${SRC_COMMON} )

target_include_directories( sandbox-common PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Common/include )

target_link_libraries( sandbox-common PUBLIC
    oceansoul-core
    oceansoul-graphics-gl )

if (WIN32)
	add_executable( sandbox WIN32
	    ${CMAKE_CURRENT_SOURCE_DIR}/Win32/src/main.cpp )

    target_link_libraries( sandbox PUBLIC 
	    sandbox-common )

    add_custom_command( TARGET sandbox PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E remove_directory
        ${CMAKE_CURRENT_BINARY_DIR}/Assets)
		
    add_custom_command( TARGET sandbox POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/Assets
        ${CMAKE_CURRENT_BINARY_DIR}/Assets)

elseif (ANDROID)
	add_library(sandbox SHARED
		${CMAKE_CURRENT_SOURCE_DIR}/Android/app/src/main/cpp/main.cpp )
		
	target_link_libraries( sandbox PUBLIC
	    sandbox-common )

    set_target_properties(sandbox PROPERTIES LINK_FLAGS "-u android_main")
endif ()