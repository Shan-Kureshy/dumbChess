cmake_minimum_required(VERSION 3.9)
project(chess2 C)

set(CMAKE_C_STANDARD 99)
include_directories("/usr/include/eigen")

add_executable(chess2 main.c pieces.h gameFunctions.h gameFunctions.c pieces.c comp.h comp.c)