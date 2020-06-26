// (C) Alan Ludwig, all rights reserved

#pragma once

#include <stdint.h>

class Gfx2d
{
public:
    constexpr Gfx2d(int32_t w, int32_t h) : _w(w), _h(h)
    {
    }

    virtual void drawPixel(int32_t x, int32_t y, uint32_t color) = 0;

    virtual void begin(void);
    virtual void end(void);
    virtual void writeFastHLine(int32_t x, int32_t y, int32_t w, uint32_t color);
    virtual void writeFastVLine(int32_t x, int32_t y, int32_t h, uint32_t color);
    virtual void writeFillRect(int32_t x, int32_t y, int32_t w, int32_t h, uint32_t color);
    virtual void writeLine(int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint32_t color);
    virtual void writePixel(int32_t x, int32_t y, uint32_t color);

    // bitmap
    void drawBitmap(int32_t x, int32_t y, const uint8_t *bitmap, int32_t w, int32_t h, uint32_t color);
    void drawBitmap(int32_t x, int32_t y, const uint8_t *bitmap, int32_t w, int32_t h, uint32_t color, uint32_t bg);

    virtual void fillScreen(uint32_t color);

protected:
    const int32_t _w;
    const int32_t _h;

private:
    virtual void writeLineLow(int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint32_t color);
    virtual void writeLineHigh(int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint32_t color);
};

template <typename T, int WIDTH, int HEIGHT>
class Gfx2dCanvas : public Gfx2d
{
public:
    constexpr Gfx2dCanvas() : Gfx2d(WIDTH, HEIGHT)
    {
        static_assert(HEIGHT > 0);
        static_assert(WIDTH > 0);
    };

    void drawPixel(int32_t x, int32_t y, uint32_t color)
    {
        if ((x >= 0 && x < _w) && (y >= 0 && y < _h))
        {
            _buffer[y * _w + x] = static_cast<T>(color);
        }
    }

    void fillScreen(uint32_t color)
    {
        for (int i = 0; i < _w * _h; ++i)
        {
            _buffer[i] = static_cast<T>(color);
        }
    }

    const T *getBuffer(void) const { return _buffer; }

private:
    T _buffer[WIDTH * HEIGHT] = {};
};
