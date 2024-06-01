#include "../includes/main_memory.h"

#include <stdio.h>
#include "assert.h"

#define START_USABLE_MEMORY 0x200

static main_memory mainMemory = {0};

main_memory * getMainMemory()
{
    return &mainMemory;
}

void loadRomIntoMemory(const char * fileLocation, main_memory * mainMemory)
{
    FILE * filePointer = fopen(fileLocation, "rb");
    long fileLength;

    fseek(filePointer, 0, SEEK_END);
    fileLength = ftell(filePointer);
    rewind(filePointer);

    printf("%li\n", fileLength);

    for (int i = 0; i < fileLength; i++)
    {
        (*mainMemory)[START_USABLE_MEMORY + i] = (uint8_t) fgetc(filePointer);
    }

    fclose(filePointer);
}