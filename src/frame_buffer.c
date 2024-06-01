#include "../includes/frame_buffer.h"

static frame_buffer frameBuffer = {0};

frame_buffer * getFrameBuffer()
{
    return &frameBuffer;
}

void clearFrameBuffer(frame_buffer * frameBuffer)
{
    for (int i = 0; i < FRAME_BUFFER_WIDTH * FRAME_BUFFER_HEIGHT; i++)
    {
        (*frameBuffer)[i] = 0;
    }
}