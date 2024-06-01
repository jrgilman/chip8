#include <stdio.h>

// chip 8 has:
// 16 x 8 bit registers (V0-VF)
// 1x 16 bit index register
// 64 byte stack + 1 x stack pointer (8 bit)
// 4096 bytes of addressable memory
// all programs start at memory location 0x200

int main() {
    printf("Hello, World!\n");
    return 0;
}
