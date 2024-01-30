cmake_minimum_required(VERSION 3.27)
project(AbstractDataTypes)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O2 -Wall -Wextra -v")

add_executable(AbstractDataTypes main.cpp
        tree/BinTree.cpp
        tree/BinTree.h
        sort/Sorter.h
        sort/SimpleSorters.cpp
        sort/AdvancedSorters.cpp
        Andrews.cpp
        tree/BST.cpp
        tree/BST.h
        tree/AVLGPT.cpp
)
