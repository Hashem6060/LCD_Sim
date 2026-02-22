// bitmap.h
#pragma once

// Declare the array (no data, no size needed for extern)
extern const unsigned char nBitmapDC5XD[];

// Constants for convenience
constexpr unsigned int BITMAP_WIDTH = 240;
constexpr unsigned int BITMAP_HEIGHT = 128;
constexpr unsigned int BITMAP_SIZE = BITMAP_WIDTH * (BITMAP_HEIGHT / 8);