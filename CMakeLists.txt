cmake_minimum_required(VERSION 3.30)
project(stadion)

set(CMAKE_CXX_STANDARD 20)

add_executable(stadion main.cpp
        kibic.cpp
        kibic.h
        stadion.cpp
        stadion.h)
