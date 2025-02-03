cmake_minimum_required(VERSION 3.30)
project(stadion)

set(CMAKE_CXX_STANDARD 20)

add_executable(stadion main.cpp
        Stadion.cpp
        Stadion.h
        Fan.cpp
        Fan.h
        Pracownik_tech.cpp
        Pracownik_tech.h
        Gate.cpp
        Gate.h
        Kierownik.cpp
        Kierownik.h
)
