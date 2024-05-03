cmake_minimum_required(VERSION 3.10)
project(Artex)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

file(GLOB SOURCES "src/*.c")

add_executable(Artex ${SOURCES})

target_link_libraries(Artex SDL2 SDL2_image SDL2_ttf)

