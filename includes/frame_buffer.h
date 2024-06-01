#ifndef CHIP8_FRAME_BUFFER_H
#define CHIP8_FRAME_BUFFER_H

#define FRAME_BUFFER_WIDTH 64
#define FRAME_BUFFER_HEIGHT 32

typedef int frame_buffer[FRAME_BUFFER_WIDTH * FRAME_BUFFER_HEIGHT];

frame_buffer * getFrameBuffer();

void clearFrameBuffer(frame_buffer * frameBuffer);

#endif //CHIP8_FRAME_BUFFER_H
