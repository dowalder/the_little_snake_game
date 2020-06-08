cmake_minimum_required(VERSION 3.12)
project(the_little_snake_game)

find_package(GTest REQUIRED)

add_subdirectory(nana)

include_directories(include nana/include ${GTEST_INCLUDE_DIR})

add_library(snakelib 
    src/BoardElements.cpp
    src/GraphicsBoard.cpp
    src/MainWindow.cpp
    src/utils.cpp
    src/sampling.cpp
    )
target_link_libraries(snakelib nana)

add_executable(snake src/main.cpp)
target_link_libraries(snake nana snakelib)

enable_testing()
add_executable(snake_unit_test test/snake_unit_test.cpp)

target_link_libraries(snake_unit_test gtest pthread nana snakelib)
