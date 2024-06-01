#ifndef CHIP8_MAIN_MEMORY_H
#define CHIP8_MAIN_MEMORY_H

#include <stdint.h>

typedef uint8_t main_memory[4096];
typedef uint8_t stack[64];
typedef uint8_t stack_pointer;
typedef uint16_t program_counter;
typedef uint8_t v_registers[16];

void loadRomIntoMainMemory(const char * fileLocation, main_memory * mainMemory);

#endif //CHIP8_MAIN_MEMORY_H
