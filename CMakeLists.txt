cmake_minimum_required(VERSION 3.10)

project(example)

set(CMAKE_CXX_STANDARD 17)

find_package(Threads)
find_package(opentelemetry-cpp)

add_subdirectory(src)
option(PACKAGE_TESTS "Build the tests" ON)
if(PACKAGE_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()
