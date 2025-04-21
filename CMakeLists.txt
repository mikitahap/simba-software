cmake_minimum_required(VERSION 3.10)
project(tests)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# Downloading google test
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(tests
        main.cpp
        IPv4PrefixSet.cpp
)

# Linking google test
target_link_libraries(tests
        gtest
        gtest_main
        pthread
)
