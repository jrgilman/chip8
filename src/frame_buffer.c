#include "../includes/frame_buffer.h"

void clearFrameBuffer(frame_buffer * frameBuffer)
{
    for (int i = 0; i < FRAME_BUFFER_WIDTH * FRAME_BUFFER_HEIGHT; i++)
    {
        (*frameBuffer)[i] = 0;
    }
}