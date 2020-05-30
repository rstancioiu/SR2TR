cmake_minimum_required(VERSION 3.5)

project(SR2TR)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_MAKE_PROGRAM ninja)

include_directories(SR2TR PUBLIC "include")

add_executable(SR2TR
    src/main.cpp
    src/Bitset.cpp
    src/CR.cpp
    src/Hungarian.cpp
    src/Mapping.cpp
    src/Reader.cpp
    src/ReadTextFile
    src/UIND.cpp)