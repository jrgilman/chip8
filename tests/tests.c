#include <assert.h>
#include <stdio.h>
#include "../includes/frame_buffer.h"
#include "../includes/main_memory.h"

void can_clear_framebuffer()
{
    // Arrange
    // we need a frame buffer that isn't empty that we intend to clear
    frame_buffer * frameBuffer = getFrameBuffer();
    for (int i = 0; i < FRAME_BUFFER_WIDTH * FRAME_BUFFER_HEIGHT; i++)
    {
        (*frameBuffer)[i] = 1;
    }

    // Act
    clearFrameBuffer(frameBuffer);

    // Assert
    // it should contain all zeroes after clearing
    for (int i = 0; i < FRAME_BUFFER_WIDTH * FRAME_BUFFER_HEIGHT; i++)
    {
//        printf("%p : %i\n", frameBuffer + i, (*frameBuffer)[i]);
        assert((*frameBuffer)[i] == 0);
    }
}

void loads_rom_file_into_memory()
{
    // Act
    // load the test_opcode.ch8 file into memory
    main_memory * mainMemory = getMainMemory();
    loadRomIntoMemory("./tests/test_opcode.ch8", mainMemory);

//    for (int i = 0; i < 4096; i++)
//    {
//        printf("%p: %i\n", &mainMemory + i, (*mainMemory)[i]);
//    }

    // Assert
    // assert first byte of rom appears at memory location 0x200
    assert((*mainMemory)[0x200] == 0x12);
    // assert last byte of rom appears at expected end
    assert((*mainMemory)[0x200 + 0x1dd] == 0xdc);
    // assert byte after last byte of rom is zero
    assert((*mainMemory)[0x200 + 0x1dd + 1] == 0);
}

int main ()
{
    can_clear_framebuffer();
    loads_rom_file_into_memory();
    return 0;
}