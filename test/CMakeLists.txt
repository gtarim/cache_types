cmake_minimum_required(VERSION 3.5)

project(${CMAKE_PROJECT_NAME_TEST})

enable_testing()

include(GoogleTest)

include_directories(../)

set(TEST_SOURCES test.cpp)
add_executable(${CMAKE_PROJECT_NAME_TEST} ${TEST_SOURCES})

target_link_libraries(${CMAKE_PROJECT_NAME_TEST} gtest gtest_main)

add_test(NAME ${CMAKE_PROJECT_NAME_TEST} COMMAND ${CMAKE_PROJECT_NAME_TEST})
gtest_discover_tests(${CMAKE_PROJECT_NAME_TEST})

set_target_properties(${CMAKE_PROJECT_NAME_TEST} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/..")