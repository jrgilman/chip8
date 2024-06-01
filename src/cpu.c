#include "../includes/cpu.h"

#include "stdio.h"

void execute_instruction(
    uint16_t instruction,
    stack * stack,
    stack_pointer * stackPointer,
    program_counter * programCounter,
    frame_buffer * frameBuffer
) {
    if (instruction == 0x00E0)
    {
        clearFrameBuffer(frameBuffer);
    }
    else if (instruction == 0x00EE)
    {
        (*programCounter) = (*stack)[(*stackPointer) - 1];
        (*stackPointer)--;
    }
    else if ((instruction & 0xF000) == 0x1000)
    {
        (*programCounter) = instruction & 0x0FFF;
    }
    else if ((instruction & 0xF000) == 0x2000)
    {
        (*stackPointer)++;
        (*stack)[(*stackPointer) - 1] = *programCounter;
        (*programCounter) = instruction & 0x0FFF;
    }
}