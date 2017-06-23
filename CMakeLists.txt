cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_STANDARD 11)

project(libsolve)

add_subdirectory(src)
include_directories(src)

# Testing
enable_testing()
add_subdirectory(tests)

