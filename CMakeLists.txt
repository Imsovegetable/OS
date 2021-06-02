cmake_minimum_required(VERSION 3.17.5)
project(os)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(os
        GODNING.h
        main.cpp
        memory.h memory.cpp gcm.h gcm.cpp directory.h directory.cpp help.cpp help.h ram.cpp ram.h inode.cpp inode.h fileSys.cpp fileSys.h user.cpp user.h os.cpp os.h)
