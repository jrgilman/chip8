#include "../includes/memory.h"

#include <stdio.h>

#define START_USABLE_MEMORY 0x200

void preloadMainMemory(main_memory * mainMemory)
{
    (*mainMemory)[0] = 0xF0;
    (*mainMemory)[1] = 0x90;
    (*mainMemory)[2] = 0x90;
    (*mainMemory)[3] = 0x90;
    (*mainMemory)[4] = 0xF0;
    (*mainMemory)[5] = 0x20;
    (*mainMemory)[6] = 0x60;
    (*mainMemory)[7] = 0x20;
    (*mainMemory)[8] = 0x20;
    (*mainMemory)[9] = 0x70;
    (*mainMemory)[10] = 0xF0;
    (*mainMemory)[11] = 0x10;
    (*mainMemory)[12] = 0xF0;
    (*mainMemory)[13] = 0x80;
    (*mainMemory)[14] = 0xF0;
    (*mainMemory)[15] = 0xF0;
    (*mainMemory)[16] = 0x10;
    (*mainMemory)[17] = 0xF0;
    (*mainMemory)[18] = 0x10;
    (*mainMemory)[19] = 0xF0;
    (*mainMemory)[20] = 0x90;
    (*mainMemory)[21] = 0x90;
    (*mainMemory)[22] = 0xF0;
    (*mainMemory)[23] = 0x10;
    (*mainMemory)[24] = 0x10;
    (*mainMemory)[25] = 0xF0;
    (*mainMemory)[26] = 0x80;
    (*mainMemory)[27] = 0xF0;
    (*mainMemory)[28] = 0x10;
    (*mainMemory)[29] = 0xF0;
    (*mainMemory)[30] = 0xF0;
    (*mainMemory)[31] = 0x80;
    (*mainMemory)[32] = 0xF0;
    (*mainMemory)[33] = 0x90;
    (*mainMemory)[34] = 0xF0;
    (*mainMemory)[35] = 0xF0;
    (*mainMemory)[36] = 0x10;
    (*mainMemory)[37] = 0x20;
    (*mainMemory)[38] = 0x40;
    (*mainMemory)[39] = 0x40;
    (*mainMemory)[40] = 0xF0;
    (*mainMemory)[41] = 0x90;
    (*mainMemory)[42] = 0xF0;
    (*mainMemory)[43] = 0x90;
    (*mainMemory)[44] = 0xF0;
    (*mainMemory)[45] = 0xF0;
    (*mainMemory)[46] = 0x90;
    (*mainMemory)[47] = 0xF0;
    (*mainMemory)[48] = 0x10;
    (*mainMemory)[49] = 0xF0;
    (*mainMemory)[50] = 0xF0;
    (*mainMemory)[51] = 0x90;
    (*mainMemory)[52] = 0xF0;
    (*mainMemory)[53] = 0x90;
    (*mainMemory)[54] = 0x90;
    (*mainMemory)[55] = 0xE0;
    (*mainMemory)[56] = 0x90;
    (*mainMemory)[57] = 0xE0;
    (*mainMemory)[58] = 0x90;
    (*mainMemory)[59] = 0xE0;
    (*mainMemory)[60] = 0xF0;
    (*mainMemory)[61] = 0x80;
    (*mainMemory)[62] = 0x80;
    (*mainMemory)[63] = 0x80;
    (*mainMemory)[64] = 0xF0;
    (*mainMemory)[65] = 0xE0;
    (*mainMemory)[66] = 0x90;
    (*mainMemory)[67] = 0x90;
    (*mainMemory)[68] = 0x90;
    (*mainMemory)[69] = 0xE0;
    (*mainMemory)[70] = 0xF0;
    (*mainMemory)[71] = 0x80;
    (*mainMemory)[72] = 0xF0;
    (*mainMemory)[73] = 0x80;
    (*mainMemory)[74] = 0xF0;
    (*mainMemory)[75] = 0xF0;
    (*mainMemory)[76] = 0x80;
    (*mainMemory)[77] = 0xF0;
    (*mainMemory)[78] = 0x80;
    (*mainMemory)[79] = 0x80;
}

void loadRomIntoMainMemory(const char * fileLocation, main_memory * mainMemory)
{
    FILE * filePointer = fopen(fileLocation, "rb");
    long fileLength;

    fseek(filePointer, 0, SEEK_END);
    fileLength = ftell(filePointer);
    rewind(filePointer);

//    printf("%li\n", fileLength);

    for (int i = 0; i < fileLength; i++)
    {
        (*mainMemory)[START_USABLE_MEMORY + i] = (uint8_t) fgetc(filePointer);
    }

    fclose(filePointer);
}