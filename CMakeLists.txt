cmake_minimum_required(VERSION 3.5)
project(Chrono)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp PCD8544.cpp PCD8544.h measurement.cpp measurement.h menu.h menu.cpp timer2.h timer2.cpp)
add_executable(Chrono ${SOURCE_FILES})