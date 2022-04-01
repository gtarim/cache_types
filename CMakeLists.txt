cmake_minimum_required(VERSION 3.5.0)

project(cache_types)

if(NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 20)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()

if(TEST)
    message("-- Google Test enabled")
    set(CMAKE_PROJECT_NAME_TEST ${CMAKE_PROJECT_NAME}_test)
    enable_testing()
    add_subdirectory(third_party/googletest)
    add_subdirectory(test)
endif(TEST)

set(CMAKE_CXX_FLAGS "-O3")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -s")

set( SOURCES main.cpp )

add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})

set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/..")

