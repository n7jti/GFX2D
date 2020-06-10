// (C) Copyright Alan Ludwig, All rights reserved.

#include <cstdio>
#include <gfx2d.h>

Gfx2dCanvas<bool, 8, 8> canvas;

template <typename T, int WIDTH, int HEIGHT>
void render(const Gfx2dCanvas<T, WIDTH, HEIGHT> &canvas)
{
    const T *buffer = canvas.getBuffer();
    for (int32_t y = 0; y < HEIGHT; ++y)
    {
        for (int32_t x = 0; x < WIDTH; ++x)
        {
            printf("\t%d", static_cast<int>(buffer[y * WIDTH + x]));
        }
        printf("\n");
    }
    return;
}

int main(void)
{
    printf("Hello World!\n");
    canvas.writeFastHLine(0, 0, 5, 1);
    canvas.writeFastVLine(0, 0, 5, 1);
    canvas.writeLine(2, 2, 6, 8, 1);
    render(canvas);
    return 0;
}