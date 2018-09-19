cmake_minimum_required(VERSION 3.10)
project(ParkingLot)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Werror")

include_directories(lib)

add_subdirectory(lib)
