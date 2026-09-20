cmake_minimum_required(VERSION 4.3)
project(herewego C)

set(CMAKE_C_STANDARD 11)

add_executable(herewego main.c
        cpu.h
        cpu.c
        assembler.c
        assembler.h
        instructions.c
        instructions.h
        decoder.c
        decoder.h
        emit.c
        emit.h
)
