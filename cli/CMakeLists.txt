cmake_minimum_required(VERSION 3.10)

include_directories(../lib)

file(GLOB CLI_SOURCES
        *.cpp
        *.hpp)

add_executable(${CLI} ${CLI_SOURCES})
target_link_libraries(${CLI} ${LIB})
add_dependencies(${CLI} ${LIB_TESTS_RUN})
