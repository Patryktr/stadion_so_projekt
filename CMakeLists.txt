cmake_minimum_required(VERSION 3.30)
project(stadion)

set(CMAKE_CXX_STANDARD 20)

add_executable(stadion main.cpp
        Kibic.cpp
        Kibic.h
        Stadion.cpp
        Stadion.h
        Kierownik.cpp
        Kierownik.h)
