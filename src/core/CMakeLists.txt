cmake_minimum_required(VERSION 3.5)

add_library(core STATIC
    Bitset.cpp
    CR.cpp
    Hungarian.cpp
    Mapping.cpp
    Reader.cpp
    ReadTextFile.cpp
    UIND.cpp)

include_directories(core PUBLIC ${CMAKE_SOURCE_DIR}/include/core)