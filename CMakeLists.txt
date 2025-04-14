cmake_minimum_required(VERSION 3.30)
project(simle)

set(CMAKE_CXX_STANDARD 20)

add_executable(simle main.cpp
        IPv4PrefixSet.cpp
        IPv4PrefixSet.h)
