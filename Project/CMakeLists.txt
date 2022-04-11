cmake_minimum_required(VERSION 3.16)
project(untitled)

# Compilation settings for C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DROOT_PROJ_DIR='\"${PROJECT_SOURCE_DIR}/data\"'")

set(CMAKE_CXX_STANDARD 14)

add_executable(untitled main.cpp)
