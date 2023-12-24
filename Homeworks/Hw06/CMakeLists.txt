cmake_minimum_required(VERSION 3.27)
project(Hw06)

set(CMAKE_CXX_STANDARD 11)

add_executable(Hw06 avlTreeSolver.cpp
        avlTreeSolver.h
        lazyAvlTreeUtil.cpp
        lazyAvlTreeUtil.h)
