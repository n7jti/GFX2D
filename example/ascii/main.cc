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

void north(int32_t x, int32_t y)
{
    for (int i = 0; i <= 7; i++)
    {
        canvas.fillScreen(0);
        canvas.writeLine(x, y, i, 0, 1);
        render(canvas);
        printf("\n\n");
    }
}

void east(int32_t x, int32_t y)
{
    for (int i = 0; i <= 7; i++)
    {
        canvas.fillScreen(0);
        canvas.writeLine(x, y, 7, i, 1);
        render(canvas);
        printf("\n\n");
    }
}

void south(int32_t x, int32_t y)
{
    for (int i = 7; i >= 0; i--)
    {
        canvas.fillScreen(0);
        canvas.writeLine(x, y, i, 7, 1);
        render(canvas);
        printf("\n\n");
    }
}

void west(int x, int y)
{
    for (int i = 7; i >= 0; i--)
    {
        canvas.fillScreen(0);
        canvas.writeLine(x, y, 0, i, 1);
        render(canvas);
        printf("\n\n");
    }
}

void NW(void)
{
    printf("NW\n\n");
    int32_t x = 0;
    int32_t y = 0;

    east(x, y);
    south(x, y);
}

void NE(void)
{
    printf("NE\n\n");
    int32_t x = 7;
    int32_t y = 0;

    south(x, y);
    west(x, y);
}

void SE(void)
{
    printf("SE\n\n");
    int32_t x = 7;
    int32_t y = 7;

    west(x, y);
    north(x, y);
}

void SW(void)
{
    printf("SW\n\n");
    int32_t x = 0;
    int32_t y = 7;

    north(x, y);
    east(x, y);
}

int main(void)
{
    NW();
    SW();
    SE();
    NE();

    printf("\n\n");
    canvas.fillScreen(0);
    canvas.writeFillRect(1, 1, 6, 6, 1);
    render(canvas);

    return 0;
}