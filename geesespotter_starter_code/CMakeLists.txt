cmake_minimum_required(VERSION 3.23)
project(geesespotter_starter_code)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(geesespotter_starter_code
        geesespotter.cpp
        geesespotter.h
        geesespotter_lib.cpp
        geesespotter_lib.h)
