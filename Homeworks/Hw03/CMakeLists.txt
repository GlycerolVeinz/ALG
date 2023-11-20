cmake_minimum_required(VERSION 3.26)
project(Hw03)


set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Hw03
        TrainSystem.cpp
        TrainSystem.h
        CityBinaryTree.cpp
        CityBinaryTree.h)

target_compile_options( Hw03 PRIVATE -Wall -Wextra -Wunreachable-code -Wpedantic)
