#include "../includes/cpu.h"

#include "stdio.h"

void execute_instruction(
    uint16_t instruction,
    stack * stack,
    stack_pointer * stackPointer,
    program_counter * programCounter
) {
    switch (instruction) {
        case 0x00EE:
            (*programCounter) = (*stack)[(*stackPointer) - 1];
            (*stackPointer)--;
            break;
        default:
    }
}