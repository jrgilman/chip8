cmake_minimum_required(VERSION 3.0)
project(chip8 C)

set(CMAKE_C_STANDARD 23)

message(UNIT_TEST: ${UNIT_TEST})

if (UNIT_TEST EQUAL 1)
    add_subdirectory(tests)
else ()
    add_subdirectory(src)
endif ()