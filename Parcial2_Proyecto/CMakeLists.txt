cmake_minimum_required(VERSION 3.26)
project(Parcial2_Proyecto)

set(CMAKE_CXX_STANDARD 17)

add_executable(Parcial2_Proyecto main.cpp)
find_package(box2d CONFIG REQUIRED)
target_link_libraries(Parcial2_Proyecto PRIVATE box2d::box2d)
find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
target_link_libraries(Parcial2_Proyecto PRIVATE sfml-system sfml-network sfml-graphics sfml-window)