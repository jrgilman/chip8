#include "../includes/cpu.h"

#include "stdio.h"

void execute_instruction(
    uint16_t instruction,
    stack * stack,
    stack_pointer * stackPointer,
    program_counter * programCounter,
    frame_buffer * frameBuffer
) {
    switch (instruction) {
        case 0x00E0:
            clearFrameBuffer(frameBuffer);
            break;
        case 0x00EE:
            (*programCounter) = (*stack)[(*stackPointer) - 1];
            (*stackPointer)--;
            break;
        default:
    }
}