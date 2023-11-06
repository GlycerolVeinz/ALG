cmake_minimum_required(VERSION 3.26)
project(Hw02)

set(CMAKE_CXX_STANDARD 14)

add_executable(Hw02
        ExplosiveStorage.cpp
        Storage.h
        Storage.cpp
        storageUtils.h
        storageUtils.cpp)
