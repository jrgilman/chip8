#include "stdio.h"
#include "stdlib.h"
#include "../includes/cpu.h"

void execute_instruction(
    uint16_t instruction,
    stack * stack,
    stack_pointer * stackPointer,
    program_counter * programCounter,
    frame_buffer * frameBuffer,
    v_registers * vRegisters
) {
    uint16_t instructionTopNibble = instruction & 0xF000;
    uint16_t instructionBottomNibble = instruction & 0x000F;

    if (instruction == 0x00E0)
    {
        clearFrameBuffer(frameBuffer);
    }
    else if (instruction == 0x00EE)
    {
        (*programCounter) = (*stack)[(*stackPointer) - 1];
        (*stackPointer)--;
    }
    else if (instructionTopNibble == 0x1000)
    {
        (*programCounter) = instruction & 0x0FFF;
    }
    else if (instructionTopNibble == 0x2000)
    {
        (*stackPointer)++;
        (*stack)[(*stackPointer) - 1] = *programCounter;
        (*programCounter) = instruction & 0x0FFF;
    }
    else if (instructionTopNibble == 0x3000)
    {
        // SE VX, NN (3XNN)
        uint8_t valueToCompare = instruction & 0xFF;
        uint8_t vRegister = (instruction >> 8) & 0xF;

        if ((*vRegisters)[vRegister] == valueToCompare)
        {
            (*programCounter) += 2;
        }
    }
    else if (instructionTopNibble == 0x4000)
    {
        // SNE VX, NN (4XNN)
        uint8_t valueToCompare = instruction & 0xFF;
        uint8_t vRegister = (instruction >> 8) & 0xF;

        if ((*vRegisters)[vRegister] != valueToCompare)
        {
            (*programCounter) += 2;
        }
    }
    else if (instructionTopNibble == 0x5000)
    {
        uint8_t vRegisterOne = (instruction >> 4) & 0xF;
        uint8_t vRegisterTwo = (instruction >> 8) & 0xF;

        if ((*vRegisters)[vRegisterOne] != (*vRegisters)[vRegisterTwo])
        {
            (*programCounter) += 2;
        }
    }
    else if (instructionTopNibble == 0x6000)
    {
        // 6XNN
        // Load NN into VX
        uint8_t vRegister = (instruction >> 8) & 0xF;
        uint8_t valueToLoad = instruction & 0xFF;
        (*vRegisters)[vRegister] = valueToLoad;
    }
    else if (instructionTopNibble == 0x7000)
    {
        // 7XNN
        // Add NN into VX
        uint8_t vRegister = (instruction >> 8) & 0xF;
        uint8_t valueToAdd = instruction & 0xFF;
        (*vRegisters)[vRegister] += valueToAdd;
    }
    else if (instructionTopNibble == 0x8000)
    {
        // Load VY into VX (8xy0)
        uint8_t vRegisterY = (instruction >> 4) & 0xF;
        uint8_t vRegisterX = (instruction >> 8) & 0xF;

        switch (instructionBottomNibble)
        {
            case 0x0000:
                (*vRegisters)[vRegisterX] = (*vRegisters)[vRegisterY];
                break;
            case 0x0001:
                (*vRegisters)[vRegisterX] |= (*vRegisters)[vRegisterY];
                break;
            case 0x0002:
                (*vRegisters)[vRegisterX] &= (*vRegisters)[vRegisterY];
                break;
            case 0x0003:
                (*vRegisters)[vRegisterX] ^= (*vRegisters)[vRegisterY];
                break;
            default:
                printf("Got an unexpected opcode 0x%04X\n", instruction);
                exit(EXIT_FAILURE);
        }
    }
}