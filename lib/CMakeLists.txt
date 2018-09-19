cmake_minimum_required(VERSION 3.10)

set(LIB lib)
set(LIB_TESTS ${LIB}_tests)

file(GLOB LIB_SOURCES
        *.cpp
        *.hpp
        parsers/*.cpp
        parsers/*.hpp)
add_library(${LIB} ${LIB_SOURCES})

add_subdirectory(tests)
