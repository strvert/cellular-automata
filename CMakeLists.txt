cmake_minimum_required(VERSION 3.12)

project(lifegame)

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

add_executable(${CMAKE_PROJECT_NAME}
    src/main.cpp
    src/cell.cpp
    src/world.cpp
    )

target_include_directories(${CMAKE_PROJECT_NAME}
    PRIVATE ./inc
    )

target_compile_options(${CMAKE_PROJECT_NAME}
    PRIVATE -Ofast -march=native -Wall
    )

target_link_libraries(${CMAKE_PROJECT_NAME})

set_property(TARGET ${CMAKE_PROJECT_NAME}
    PROPERTY CXX_STANDARD 20
    )
