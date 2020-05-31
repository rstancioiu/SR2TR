cmake_minimum_required(VERSION 3.5)

add_executable(batch
    main.cpp)

include_directories(batch PUBLIC ${CMAKE_SOURCE_DIR}/include/core)

TARGET_LINK_LIBRARIES(batch core)