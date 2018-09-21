set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(3rdparty/json/include)

file(GLOB LIB_SOURCES
        *.cpp
        *.hpp
        parsers/*.cpp
        parsers/*.hpp)
add_library(${LIB} ${LIB_SOURCES})

add_subdirectory(tests)
