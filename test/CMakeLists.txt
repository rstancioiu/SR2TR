cmake_minimum_required(VERSION 3.14)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.8.0
)

FetchContent_MakeAvailable(googletest)

include_directories(test PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_executable(test
    Bitset_test.cpp
    main_test.cpp)

TARGET_LINK_LIBRARIES(test gtest gmock core)