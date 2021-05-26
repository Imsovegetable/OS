cmake_minimum_required(VERSION 3.17)
project(OS)

set(CMAKE_CXX_STANDARD 14)

include_directories(os)

add_executable(OS
        os/GODNING.h
        os/main.cpp
        os/memory.h)
