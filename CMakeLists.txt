cmake_minimum_required(VERSION 3.12)
cmake_policy(SET CMP0074 NEW)

project(example)

set(CMAKE_CXX_STANDARD 17)

find_package(opentelemetry-cpp)
include_directories(${OPENTELEMETRY_CPP_INCLUDE_DIRS})

add_subdirectory(src)
option(PACKAGE_TESTS "Build the tests" ON)
if(PACKAGE_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()
