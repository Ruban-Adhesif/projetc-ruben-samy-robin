cmake_minimum_required(VERSION 3.25)
project(Project_C C)

set(CMAKE_C_STANDARD 11)

add_executable(Project_C main.c
        part1.c
        part1.h
        part2.c
        part2.h part3.c part3.h)
