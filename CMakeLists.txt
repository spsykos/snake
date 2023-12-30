cmake_minimum_required(VERSION 3.10)

project(snake)

set(PROJECT_DIR ${CMAKE_SOURCE_DIR})

set(PROJECT_INCLUDE_DIR ${PROJECT_DIR}/include)

set(PROJECT_SOURCE_DIR ${PROJECT_DIR}/src)

set(PROJECT_SOURCES
            ${PROJECT_SOURCE_DIR}/main.c
            ${PROJECT_SOURCE_DIR}/glad.c
            ${PROJECT_SOURCE_DIR}/snakeObject.c 
            ${PROJECT_SOURCE_DIR}/VBuffer.c 
            ${PROJECT_SOURCE_DIR}/shader.c)

find_package(glfw3 3.2 REQUIRED)
find_package(cglm REQUIRED)
 
include_directories(${PROJECT_INCLUDE_DIR})

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_link_libraries(${PROJECT_NAME} glfw cglm)