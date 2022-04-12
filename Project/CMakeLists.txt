cmake_minimum_required(VERSION 3.16)
project(untitled)

# Compilation settings for C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DROOT_PROJ_DIR='\"${PROJECT_SOURCE_DIR}/data\"'")

set(CMAKE_CXX_STANDARD 14)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/carrinhas.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/encomendas.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
add_executable(untitled main.cpp)
add_executable(cenario2 cenario2.cpp)
