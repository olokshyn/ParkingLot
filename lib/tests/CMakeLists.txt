cmake_minimum_required(VERSION 3.10)

add_subdirectory(3rdparty/googletest)

include_directories(${gtest_SOURCE_DIR}/include)
include_directories(../)

file(GLOB TEST_SOURCES
        *.cpp
        *.hpp)
add_executable(${LIB_TESTS} ${TEST_SOURCES})
add_dependencies(${LIB_TESTS} ${LIB} gtest_main)
target_link_libraries(${LIB_TESTS} ${LIB} gtest_main)

add_custom_target(${LIB_TESTS}_run
        ${LIB_TESTS}
        DEPENDS ${LIB}
        DEPENDS ${LIB_TESTS})
