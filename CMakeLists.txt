cmake_minimum_required(VERSION 3.5)
project(Chrono)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp PCD8544.cpp PCD8544.h)
add_executable(Chrono ${SOURCE_FILES})