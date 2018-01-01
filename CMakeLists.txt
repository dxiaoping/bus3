cmake_minimum_required(VERSION 3.9)
project(bus3)

set(CMAKE_CXX_STANDARD 11)

add_executable(bus3 main.cpp bus.h bus_station.h bus.cpp bus_road.cpp)