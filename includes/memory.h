#ifndef CHIP8_MAIN_MEMORY_H
#define CHIP8_MAIN_MEMORY_H

#include <stdint.h>

typedef uint8_t main_memory[4096];

main_memory * getMainMemory();
void loadRomIntoMainMemory(const char * fileLocation, main_memory * mainMemory);

#endif //CHIP8_MAIN_MEMORY_H
