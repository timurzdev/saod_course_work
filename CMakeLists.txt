cmake_minimum_required(VERSION 3.17)
project(saod_course_work)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(saod_course_work
        handler.h
        saod_course_work.cpp)
