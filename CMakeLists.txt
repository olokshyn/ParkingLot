cmake_minimum_required(VERSION 3.10)
project(ParkingLot)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Werror")

set(LIB lib)
set(LIB_TESTS ${LIB}_tests)
set(LIB_TESTS_RUN ${LIB_TESTS}_run)
set(CLI cli_${PROJECT_NAME})
set(GUI gui_${PROJECT_NAME})

add_subdirectory(lib)
add_subdirectory(cli)

find_package(Qt5Widgets)
if(Qt5Widgets_FOUND)
    add_subdirectory(gui)
else()
    message(WARNING "Qt5 was not found in CMAKE_PREFIX_PATH, so GUI target won`t be available")
endif()

file(COPY test_data DESTINATION ${CMAKE_BINARY_DIR}/)
