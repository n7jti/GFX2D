// Copyright Alan Ludwig, all rights reserved

#pragma once

#include <stdint.h>

class Gfx2d
{
public:
    constexpr Gfx2d(int32_t w, int32_t h) : _w(w), _h(h)
    {
        // static_assert(w > 0);
        // static_assert(h > 0);
    }

    virtual void setPixel(int32_t x, int32_t y, uint32_t color) = 0;

    virtual void begin(void);
    virtual void end(void);
    virtual void writePixel(int32_t x, int32_t y, uint32_t color);
    virtual void writeFillRect(int32_t x, int32_t y, int32_t w, int32_t h, uint32_t color);
    virtual void writePixel(int32_t x, int32_t y, uint32_t color);
    virtual void writeFastVLine(int32_t x, int32_t y, int32_t h, uint32_t color);
    virtual void writeFastHline(int32_t x, int32_t y, int32_t w, uint32_t color);
    virtual void writLine(int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint32_t color);

private:
    const int32_t _w;
    const int32_t _h;
};

// 1 bit canvas for GFX2D
class Gfx2dCanvas1;

// 8 bit canvas for GFX2D
class Gfx2dCanvas8;

// 16 bit canvas for GFX2D
class Gfs3dCanvas16;

// 32 bit canvas for GFX2D
class Gfx2dCanvas32;
