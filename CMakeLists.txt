cmake_minimum_required(VERSION 3.5)

project(SR2TR)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_MAKE_PROGRAM ninja)

add_subdirectory(src/core)
add_subdirectory(src/batch)