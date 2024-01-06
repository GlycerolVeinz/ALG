cmake_minimum_required(VERSION 3.27)
project(Hw08_02)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Hw08_02
        garden.cpp
        garden.h
        gardenPlanner.cpp)
