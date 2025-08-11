cmake_minimum_required(VERSION 3.31)
project(PJC C)

set(CMAKE_C_STANDARD 11)

add_executable(PJC main.c
        Include/function.h
        Include/student.h
        Include/teacher.h
        Include/classroom.h
        Src/function.c
        Src/student.c
        Src/teacher.c
        Src/classroom.c
        Include/datatype.h)
