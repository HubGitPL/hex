cmake_minimum_required(VERSION 3.27)
project(hex)

set(CMAKE_CXX_STANDARD 17)

add_executable(hex main.cpp
        Counter.cpp
        Counter.h
        Defines.h)
