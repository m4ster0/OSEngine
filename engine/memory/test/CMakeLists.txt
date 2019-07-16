set(Boost_USE_STATIC_LIBS        ON) # only find static libs
find_package(Boost 1.65.0 COMPONENTS unit_test_framework)

if(Boost_FOUND)

    function(create_test FILE)
        string(TOLOWER "${FILE}" file_name)
        string(LENGTH "${FILE}" file_name_length)
        if(NOT "${file_name}" MATCHES ".cpp$") 
            message( FATAL_ERROR "Test file \"${FILE}\" is not recognised as cpp file" )
        endif()
        math(EXPR length "${file_name_length} - 4")
        string(SUBSTRING "${file_name}" 0 ${length} TEST_NAME)

        message(STATUS "Building test ${TEST_NAME}")

        add_executable(${TEST_NAME} "${CMAKE_CURRENT_SOURCE_DIR}/${FILE}")
        target_include_directories(${TEST_NAME} PRIVATE ${Boost_INCLUDE_DIRS})
        target_link_libraries(${TEST_NAME} PRIVATE
                        ose-memory
                        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} )
        add_test(${TEST_NAME} ${TEST_NAME})
    endfunction()

    create_test(memory_area_test.cpp)
    create_test(system_allocator_test.cpp)
    create_test(memory_resource_test.cpp)

endif()