// bitmap.h
#pragma once
#include <cstdint>
// Declare the array (no data, no size needed for extern)
extern const unsigned char nBitmapDC5XD[];

// Constants for convenience
constexpr unsigned int BITMAP_WIDTH = 240;
constexpr unsigned int BITMAP_HEIGHT = 128;
constexpr unsigned int BITMAP_SIZE = BITMAP_WIDTH * (BITMAP_HEIGHT / 8);

// ASCII 8x16 font (95 characters: 0x20-0x7E)
// Each character: 16 bytes (8 bits × 16 rows)
extern const uint8_t ASCII_FONT_8x16[];

// Chinese 16x16 font placeholder (GB2312 subset)
// Each character: 32 bytes (16 bits × 16 rows)
// In real use: load from external font file or large array
struct ChineseFontEntry {
    uint16_t gb_code;      // GB2312 code (e.g., 0xA8A1)
    const uint8_t* bitmap; // 32-byte bitmap
};
extern const ChineseFontEntry CHINESE_FONT_TABLE[];
extern const size_t CHINESE_FONT_COUNT;

// Font metrics
constexpr int ASCII_FONT_WIDTH = 8;
constexpr int ASCII_FONT_HEIGHT = 16;
constexpr int CHINESE_FONT_WIDTH = 16;
constexpr int CHINESE_FONT_HEIGHT = 16;
constexpr int ASCII_FONT_BYTES = 16;   // 8 bits × 16 rows / 8
constexpr int CHINESE_FONT_BYTES = 32; // 16 bits × 16 rows / 8

extern const uint8_t FONT[];