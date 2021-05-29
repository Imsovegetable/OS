cmake_minimum_required(VERSION 3.17.5)
project(os)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(os
        GODNING.h
        main.cpp
        memory.h memory.cpp gcm.h gcm.cpp)
