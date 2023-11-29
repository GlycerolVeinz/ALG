cmake_minimum_required(VERSION 3.26)
project(Hw04)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Hw04
        joe.cpp
        joe.h
        GameField.cpp
        GameField.h)
