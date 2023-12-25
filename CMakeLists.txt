cmake_minimum_required(VERSION 3.10)
project(snake)

add_executable(snake main.c)

target_link_libraries(snake glfw ${GLFW_LIBRARIES})