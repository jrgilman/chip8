#include <assert.h>
#include <stdio.h>
#include "../includes/frame_buffer.h"
#include "../includes/memory.h"
#include "../includes/cpu.h"

void can_clear_framebuffer()
{
    // Arrange
    // we need a frame buffer that isn't empty that we intend to clear
    frame_buffer frameBuffer;
    for (int i = 0; i < FRAME_BUFFER_WIDTH * FRAME_BUFFER_HEIGHT; i++)
    {
        frameBuffer[i] = 1;
    }

    stack_pointer stackPointer;
    stack stack;
    program_counter programCounter;

    // Act
    execute_instruction(
        0x00E0,
        &stack,
        &stackPointer,
        &programCounter,
        &frameBuffer
    );

    // Assert
    // it should contain all zeroes after clearing
    for (int i = 0; i < FRAME_BUFFER_WIDTH * FRAME_BUFFER_HEIGHT; i++)
    {
//        printf("%p : %i\n", frameBuffer + i, (*frameBuffer)[i]);
        assert(frameBuffer[i] == 0);
    }
}

void loads_rom_file_into_memory()
{
    // Act
    // load the test_opcode.ch8 file into memory
    main_memory mainMemory;
    loadRomIntoMainMemory("./tests/test_opcode.ch8", &mainMemory);

//    for (int i = 0; i < 4096; i++)
//    {
//        printf("%p: %i\n", &mainMemory + i, (*mainMemory)[i]);
//    }

    // Assert
    // assert first byte of rom appears at memory location 0x200
    assert(mainMemory[0x200] == 0x12);
    // assert last byte of rom appears at expected end
    assert(mainMemory[0x200 + 0x1dd] == 0xdc);
    // assert byte after last byte of rom is zero
    assert(mainMemory[0x200 + 0x1dd + 1] == 0);
}

void return_from_subroutine()
{
    // Arrange
    frame_buffer frameBuffer;

    // 64 byte stack
    // 8 bit stack pointer
    // 16 bit program counter
    stack_pointer stackPointer = 64;
    stack stack;
    stack[stackPointer - 1] = 0xFF;

    program_counter programCounter = 0xABCD;

    // Act
    execute_instruction(
        0x00EE,
        &stack,
        &stackPointer,
        &programCounter,
        &frameBuffer
    );

    // Assert
    // program counter should be the value at the top of the stack
    // stack pointer should be one less
    assert(programCounter == 0xFF);
    assert(stackPointer == 63);
}

int main ()
{
    can_clear_framebuffer();
    loads_rom_file_into_memory();
    return_from_subroutine();
    return 0;
}