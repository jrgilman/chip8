#include "assert.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "libgen.h"

#include "../includes/frame_buffer.h"
#include "../includes/memory.h"
#include "../includes/cpu.h"

static frame_buffer frameBuffer;
static stack_pointer stackPointer;
static stack programStack;
static program_counter programCounter;
static main_memory mainMemory;
static v_registers vRegisters;

static char * testOpcodeFile;

void setup()
{
    programCounter = 0;

    for (int i = 0; i < FRAME_BUFFER_WIDTH * FRAME_BUFFER_HEIGHT; i++)
    {
        frameBuffer[i] = 1;
    }

    stackPointer = 0;
    for (int i = 0; i < 64; i++)
    {
        programStack[i] = 0;
    }

    for (int i = 0; i < 4096; i++)
    {
        mainMemory[i] = 0;
    }

    for (int i = 0; i < 16; i++)
    {
        vRegisters[i] = 0;
    }
}

void can_clear_framebuffer()
{
    setup();

    // Arrange
    // we need a frame buffer that isn't empty that we intend to clear
    for (int i = 0; i < FRAME_BUFFER_WIDTH * FRAME_BUFFER_HEIGHT; i++)
    {
        frameBuffer[i] = 1;
    }

    // Act
    execute_instruction(
        0x00E0,
        &programStack,
        &stackPointer,
        &programCounter,
        &frameBuffer,
        &vRegisters
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
    setup();

    // Act
    // load the test_opcode.ch8 file into memory
    loadRomIntoMainMemory(testOpcodeFile, &mainMemory);

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
    setup();

    // Arrange
    // 64 byte stack
    // 8 bit stack pointer
    // 16 bit program counter
    stack_pointer stackPointer = 64;
    programStack[stackPointer - 1] = 0xFF;
    program_counter programCounter = 0xABCD;

    // Act
    execute_instruction(
        0x00EE,
        &programStack,
        &stackPointer,
        &programCounter,
        &frameBuffer,
        &vRegisters
    );

    // Assert
    // program counter should be the value at the top of the stack
    // stack pointer should be one less
    assert(programCounter == 0xFF);
    assert(stackPointer == 63);
}

void can_jump()
{
    setup();

    execute_instruction(
        0x1DEF,
        &programStack,
        &stackPointer,
        &programCounter,
        &frameBuffer,
        &vRegisters
    );

    assert(programCounter == 0xDEF);
}

void call_subroutine_at_address()
{
    setup();

    programCounter = 0x12;

    execute_instruction(
        0x2ABC,
        &programStack,
        &stackPointer,
        &programCounter,
        &frameBuffer,
        &vRegisters
    );

    assert(stackPointer == 1);
    assert(programStack[stackPointer - 1] == 0x12);
    assert(programCounter == 0xABC);
}

void skip_next_instruction_if_vx_equals_nn()
{
    // 3XNN
    setup();

    vRegisters[0xA] = 0xBC;

    // should skip
    execute_instruction(
        0x3ABC,
        &programStack,
        &stackPointer,
        &programCounter,
        &frameBuffer,
        &vRegisters
    );

    assert(programCounter == 2);

    // now it shouldn't skip.
    execute_instruction(
        0x3ABB,
        &programStack,
        &stackPointer,
        &programCounter,
        &frameBuffer,
        &vRegisters
    );

    assert(programCounter == 2);
}

void skip_next_instruction_if_vx_not_equal_to_nn()
{
    // 4XNN
    // SNE VX, NN
    setup();

    // it should skip because they're not equal here
    vRegisters[0xA] = 0xBC;
    execute_instruction(
        0x4ABB,
        &programStack,
        &stackPointer,
        &programCounter,
        &frameBuffer,
        &vRegisters
    );

    assert(programCounter == 2);

    // it should not skip here because they're equal
    execute_instruction(
        0x4ABC,
        &programStack,
        &stackPointer,
        &programCounter,
        &frameBuffer,
        &vRegisters
    );

    assert(programCounter == 2);
}

void skip_next_instruction_if_vx_not_equal_to_vy() {
    // 5XY0
    setup();
    programCounter = 0;

    vRegisters[0x0] = 0;
    vRegisters[0xA] = 1;
    vRegisters[0xB] = 0;

    execute_instruction(
        0x50A0,
        &programStack,
        &stackPointer,
        &programCounter,
        &frameBuffer,
        &vRegisters
    );

    // V0 is not equal to VA thus PC should be 2
    assert(programCounter == 2);

    // V0 and VB are the same thus PC should remain at 2
    execute_instruction(
        0x5B00,
        &programStack,
        &stackPointer,
        &programCounter,
        &frameBuffer,
        &vRegisters
    );

    // V0 and VB are the same thus PC should remain at 2
    assert(programCounter == 2);
}

void load_nn_into_vx() {
    setup();
    vRegisters[0x0] = 0;

    execute_instruction(
        0x60FF,
        &programStack,
        &stackPointer,
        &programCounter,
        &frameBuffer,
        &vRegisters
    );

    assert(vRegisters[0x0] == 0xFF);
}

void add_vx_and_nn()
{
    // 7xnn
    setup();
    vRegisters[0x0] = 0x01;

    // V0
    execute_instruction(
        0x70FE,
        &programStack,
        &stackPointer,
        &programCounter,
        &frameBuffer,
        &vRegisters
    );

    // 0x01 plus 0xFE should be 0xFF
    assert(vRegisters[0x0] == 0xFF);
}

int main ()
{
    printf("Running unit tests\n");

    // Get the directory path of the executable
    char* executable_path = strdup(__FILE__);
    char* executable_dir = dirname(executable_path);

    // Construct the path to the test_opcode.ch8 file relative to the executable
    testOpcodeFile = malloc(strlen(executable_dir) + strlen("/test_opcode.ch8") + 1);
    strcpy(testOpcodeFile, executable_dir);
    strcat(testOpcodeFile, "/test_opcode.ch8");

    can_clear_framebuffer();
    loads_rom_file_into_memory();
    return_from_subroutine();
    can_jump();
    call_subroutine_at_address();
    skip_next_instruction_if_vx_equals_nn();
    skip_next_instruction_if_vx_not_equal_to_nn();
    skip_next_instruction_if_vx_not_equal_to_vy();
    load_nn_into_vx();
    add_vx_and_nn();

    printf("Tests complete\n");
    return 0;
}