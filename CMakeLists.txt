cmake_minimum_required(VERSION 3.28.3)
project(player C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)

add_executable(player
    src/main.c
)

target_include_directories(player PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(player PRIVATE ${SDL2_LIBRARIES})

