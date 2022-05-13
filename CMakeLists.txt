cmake_minimum_required(VERSION 3.10)
project(zadanie)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH "F:\\Qt\\5.15.2\\mingw81_32")

find_package(Qt5Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_subdirectory(libraries)
add_subdirectory(tests)

add_executable(zadanie main.cpp)

target_link_libraries(zadanie point_group)

target_link_libraries(zadanie Qt5::Core)
target_link_libraries(zadanie Qt5::Gui)
target_link_libraries(zadanie Qt5::Widgets)