#ifndef CHIP8_CPU_H
#define CHIP8_CPU_H

#include "memory.h"

void execute_instruction(
    uint16_t instruction,
    stack * stack,
    stack_pointer * stackPointer,
    program_counter * programCounter
);

#endif //CHIP8_CPU_H
