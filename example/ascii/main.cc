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

void NW(void)
{
    printf("NW\n\n");

    // east
    for (int i = 0; i < 8; i++)
    {
        canvas.fillScreen(0);
        canvas.writeLine(0, 0, 7, i, 1);
        render(canvas);
        printf("\n\n");
    }

    //south
    for (int i = 7; i >= 0; i--)
    {
        canvas.fillScreen(0);
        canvas.writeLine(0, 0, i, 7, 1);
        render(canvas);
        printf("\n\n");
    }
}

void NE(void)
{
    printf("NE\n\n");

    //south
    for (int i = 7; i >= 0; i--)
    {
        canvas.fillScreen(0);
        canvas.writeLine(7, 0, i, 7, 1);
        render(canvas);
        printf("\n\n");
    }

    //west
    for (int i = 7; i >= 0; i--)
    {
        canvas.fillScreen(0);
        canvas.writeLine(7, 0, 0, i, 1);
        render(canvas);
        printf("\n\n");
    }
}

void SE(void)
{
    printf("SE\n\n");

    //north
    for (int i = 7; i >= 0; i--)
    {
        canvas.fillScreen(0);
        canvas.writeLine(7, 7, i, 0, 1);
        render(canvas);
        printf("\n\n");
    }

    //west
    for (int i = 0; i <= 7; i++)
    {
        canvas.fillScreen(0);
        canvas.writeLine(7, 7, 0, i, 1);
        render(canvas);
        printf("\n\n");
    }
}

void SW(void)
{
    printf("SW\n\n");
    // east
    for (int i = 7; i >= 0; i--)
    {
        canvas.fillScreen(0);
        canvas.writeLine(0, 7, 7, i, 1);
        render(canvas);
        printf("\n\n");
    }

    //north
    for (int i = 7; i >= 0; i--)
    {
        canvas.fillScreen(0);
        canvas.writeLine(0, 7, i, 0, 1);
        render(canvas);
        printf("\n\n");
    }
}

int main(void)
{
    NE();
    NW();
    SW();
    SE();
    return 0;
}