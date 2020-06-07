cmake_minimum_required(VERSION 3.12)
project(the_little_snake_game)


add_subdirectory(nana)

include_directories(include nana/include)

add_executable(snake src/main.cpp)
target_link_libraries(snake nana)