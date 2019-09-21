set(Boost_USE_STATIC_LIBS        ON) # only find static libs
find_package(Boost 1.65.0 COMPONENTS unit_test_framework)

if(Boost_FOUND)

    function(create_test TEST_NAME)
        message(STATUS "Building test ${TEST_NAME}")

        add_executable(${TEST_NAME} "${ARGN}")
        target_include_directories(${TEST_NAME} PRIVATE ${Boost_INCLUDE_DIRS})
        target_link_libraries(${TEST_NAME} PRIVATE
                        ose-memory
                        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} )
        add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
        set_target_properties(${TEST_NAME} PROPERTIES FOLDER ose-memory-tests)
    endfunction()

    create_test("ose-memory-area-test" memory_area_test.cpp)
    create_test("ose-memory-allocator-test" system_allocator_test.cpp)
    create_test("ose-memory-resource-test" memory_resource_test.cpp)

endif()