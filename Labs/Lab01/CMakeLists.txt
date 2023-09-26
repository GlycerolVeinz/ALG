cmake_minimum_required(VERSION 3.5)
project(cmake-example LANGUAGES CXX)
 
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
 
add_executable(lab01
    Lab_exercises01.cpp
)
 
# Zapneme rozumnou sadu varování
if ( CMAKE_CXX_COMPILER_ID MATCHES "Clang|AppleClang|GNU" )
    target_compile_options( lab01 PRIVATE -Wall -Wextra -Wunreachable-code -Wpedantic)
endif()
if ( CMAKE_CXX_COMPILER_ID MATCHES "MSVC" )
    target_compile_options( lab01 PRIVATE /W4 )
endif()