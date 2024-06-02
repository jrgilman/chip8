#include "../includes/cpu.h"

void execute_instruction(
    uint16_t instruction,
    stack * stack,
    stack_pointer * stackPointer,
    program_counter * programCounter,
    frame_buffer * frameBuffer,
    v_registers * vRegisters
) {
    uint16_t instructionTopNibbleOnly = (instruction & 0xF000);

    if (instruction == 0x00E0)
    {
        clearFrameBuffer(frameBuffer);
    }
    else if (instruction == 0x00EE)
    {
        (*programCounter) = (*stack)[(*stackPointer) - 1];
        (*stackPointer)--;
    }
    else if (instructionTopNibbleOnly == 0x1000)
    {
        (*programCounter) = instruction & 0x0FFF;
    }
    else if (instructionTopNibbleOnly == 0x2000)
    {
        (*stackPointer)++;
        (*stack)[(*stackPointer) - 1] = *programCounter;
        (*programCounter) = instruction & 0x0FFF;
    }
    else if (instructionTopNibbleOnly == 0x3000)
    {
        // SE VX, NN (3XNN)
        uint8_t valueToCompare = instruction & 0xFF;
        uint8_t vRegister = (instruction >> 8) & 0xF;

        if ((*vRegisters)[vRegister] == valueToCompare)
        {
            (*programCounter) += 2;
        }
    }
    else if (instructionTopNibbleOnly == 0x4000)
    {
        // SNE VX, NN (4XNN)
        uint8_t valueToCompare = instruction & 0xFF;
        uint8_t vRegister = (instruction >> 8) & 0xF;

        if ((*vRegisters)[vRegister] != valueToCompare)
        {
            (*programCounter) += 2;
        }
    }
    else if (instructionTopNibbleOnly == 0x5000)
    {
        uint8_t vRegisterOne = (instruction >> 4) & 0xF;
        uint8_t vRegisterTwo = (instruction >> 8) & 0xF;

        if ((*vRegisters)[vRegisterOne] != (*vRegisters)[vRegisterTwo])
        {
            (*programCounter) += 2;
        }
    }
}