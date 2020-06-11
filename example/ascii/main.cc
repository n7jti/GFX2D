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
    for (int i = 0; i < 8; i++)
    {
        canvas.fillScreen(0);
        canvas.writeLine(7, 0, 0, i, 1);
        render(canvas);
        printf("\n\n");
    }

    return 0;
}