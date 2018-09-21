find_package(Qt5 COMPONENTS Core Widgets Charts REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

include_directories(../lib)

file(GLOB GUI_SOURCES
        *.cpp
        *.hpp)

add_executable(${GUI} ${GUI_SOURCES})
target_link_libraries(${GUI} ${LIB})
qt5_use_modules(${GUI} Widgets Charts)
add_dependencies(${GUI} ${LIB_TESTS_RUN})
