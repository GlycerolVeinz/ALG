cmake_minimum_required(VERSION 3.27)
project(AbstractDataTypes)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -v")

add_executable(AbstractDataTypes main.cpp
        BinTree.cpp
        BinTree.h
        Sorter.h
        SimpleSorters.cpp
        AdvancedSorters.cpp)
