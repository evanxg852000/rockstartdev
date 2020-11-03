# Basic CMake project
cmake_minimum_required(VERSION 3.5.1)

project(clox)

set(CMAKE_C_STANDARD 99)

add_executable(clox 
    main.c
    chunk.c
    memory.c
    debug.c
    value.c
    vm.c
    compiler.c
    scanner.c
    object.c
    table.c
)
