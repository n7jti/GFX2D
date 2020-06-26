// Copyright (C) Alan Ludwig, all rights reserved.

#include <gfx2d.h>
#include <cmath>

void Gfx2d::begin(void)
{
    // default implementation does nothing;
    return;
}

void Gfx2d::end(void)
{
    // default implementation does nothing
    return;
}

void Gfx2d::writeFastHLine(int32_t x, int32_t y, int32_t w, uint32_t color)
{
    // Set 'w' horizontal pixels starting with x
    for (int32_t i = 0; i < w; ++i)
    {
        drawPixel(x + i, y, color);
    }
    return;
}

void Gfx2d::writeFastVLine(int32_t x, int32_t y, int32_t h, uint32_t color)
{
    // Set 'h' vertical pixels starting with y
    for (int32_t i = 0; i < h; ++i)
    {
        drawPixel(x, y + i, color);
    }
    return;
}

void Gfx2d::writeFillRect(int32_t x, int32_t y, int32_t w, int32_t h, uint32_t color)
{
    // Implement Fill Rect as a series of lines
    for (int i = 0; i < h; ++i)
    {
        writeFastHLine(x, y + i, w, color);
    }
    return;
}

void Gfx2d::writeLineLow(int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint32_t color)
{
    int32_t dx = x1 - x0;
    int32_t dy = y1 - y0;
    int32_t yi = 1;

    if (dy < 0)
    {
        yi = -1;
        dy = -dy;
    }

    int32_t d = 2 * dy - dx;

    int32_t incrE = 2 * dy;
    int32_t incrNE = 2 * (dy - dx);

    int32_t x = x0;
    int32_t y = y0;
    writePixel(x, y, color);

    while (x < x1)
    {
        if (d < 0) // Choose E (the EAST Pixel)
        {
            d += incrE;
        }
        else // Choose NE (the NE Pixel)
        {
            d += incrNE;
            y += yi;
        }
        x++;
        writePixel(x, y, color);
    }
}

void Gfx2d::writeLineHigh(int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint32_t color)
{
    // writeLine is based on the Midpoint Algorithm from chapter 3 of "Computer Graphics
    // Principles and pratice" Second Edition in C by Foley, Dam , et al. (c) 1996
    int32_t dx = x1 - x0;
    int32_t dy = y1 - y0;
    int32_t xi = 1;
    if (dx < 0)
    {
        xi = -1;
        dx = -dx;
    }
    int32_t d = 2 * dx - dy;
    int32_t incrE = 2 * dx;
    int32_t incrNE = 2 * (dx - dy);

    int32_t x = x0;
    int32_t y = y0;
    writePixel(x, y, color);

    while (y < y1)
    {
        if (d < 0) // Choose E (the EAST Pixel)
        {
            d += incrE;
        }
        else // Choose NE (the NE Pixel)
        {
            d += incrNE;
            x += xi;
        }
        y++;
        writePixel(x, y, color);
    }
}

void Gfx2d::writeLine(int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint32_t color)
{
    // writeLine is based on the Midpoint Algorithm from chapter 3 of "Computer Graphics
    // Principles and pratice" Second Edition in C by Foley, Dam , et al. (c) 1996, combined
    // with generalizations from wikipedia's article on Bresenham's line algorithm
    if (abs(y1 - y0) < abs(x1 - x0))
    {
        if (x0 > x1)
        {
            writeLineLow(x1, y1, x0, y0, color);
        }
        else
        {
            writeLineLow(x0, y0, x1, y1, color);
        }
    }
    else
    {
        if (y0 > y1)
        {
            writeLineHigh(x1, y1, x0, y0, color);
        }
        else
        {
            writeLineHigh(x0, y0, x1, y1, color);
        }
    }
}

void Gfx2d::writePixel(int32_t x, int32_t y, uint32_t color)
{
    // Default implementation falls through to drawPixel
    drawPixel(x, y, color);
    return;
}

void Gfx2d::fillScreen(uint32_t color)
{
    for (int i = 0; i < _w; ++i)
    {
        for (int j = 0; j < _h; ++j)
        {
            writePixel(i, j, color);
        }
    }
}

// bitmap
void Gfx2d::drawBitmap(int32_t x, int32_t y, const uint8_t *bitmap, int32_t w, int32_t h, uint32_t color)
{
    uint8_t width = (w + 7) / 8; // The bitmap stride is assumed to be in whole bytes, even if the bitmap itself isn't.
    uint8_t byte = 0;

    begin();

    // loop over the height in bits
    for (int32_t i = 0; i < h; i++)
    {
        // loop over the width in bits
        for (int32_t j = 0; j < w; j++)
        {
            // if any of the first three bits are set then we are not divisible by 8. So if we are not divisible by 8
            // then shift the bits to the right.
            if (j & 7)
            {
                // shift the bits to the right
                byte = byte << 1;
            }
            else // if we are divisible by 8.
            {
                // read in a new bit.
                byte = bitmap[(i * width) + (j / 8)];
            }

            // if the top bit of our byte is set
            if (byte & 0x80)
            {
                // write out the color
                writePixel(x + i, y, color);
            }
        }
        y++; // Increment y
    }

    end();
}

// bitmap
void Gfx2d::drawBitmap(int32_t x, int32_t y, const uint8_t *bitmap, int32_t w, int32_t h, uint32_t color, uint32_t bg)
{
    uint8_t width = (w + 7) / 8; // The bitmap stride is assumed to be in whole bytes, even if the bitmap itself isn't.
    uint8_t byte = 0;

    begin();

    // loop over the height in bits
    for (int32_t i = 0; i < h; i++)
    {
        // loop over the width in bits
        for (int32_t j = 0; j < w; j++)
        {
            // if any of the first three bits are set then we are not divisible by 8. So if we are not divisible by 8
            // then shift the bits to the right.
            if (j & 7)
            {
                // shift the bits to the right
                byte = byte << 1;
            }
            else // if we are divisible by 8.
            {
                // read in a new bit.
                byte = bitmap[(i * width) + (j / 8)];
            }

            // if the top bit of our byte is set
            if (byte & 0x80)
            {
                // write out the color
                writePixel(x + i, y + i, color);
            }
            else
            {
                writePixel(x + i, y + i, bg);
            }
        }
    }

    end();
}
