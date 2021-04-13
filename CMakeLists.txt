cmake_minimum_required(VERSION 3.12)

project(lifegame)

find_package(SFML 2 REQUIRED graphics window system)

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(${CMAKE_PROJECT_NAME}
    src/main.cpp
    src/game_logics/cell_base.cpp
    src/game_logics/lifegame_cell.cpp
    src/game_logics/field.cpp
    src/renderers/field_renderer.cpp
    src/system/component_manager.cpp
    )

target_include_directories(${CMAKE_PROJECT_NAME}
    PRIVATE ./inc
    )

target_compile_options(${CMAKE_PROJECT_NAME}
    PRIVATE -Ofast -Wall
    )

target_link_libraries(${CMAKE_PROJECT_NAME} sfml-graphics sfml-system sfml-window fmt)

set_property(TARGET ${CMAKE_PROJECT_NAME}
    PROPERTY CXX_STANDARD 20
    )
