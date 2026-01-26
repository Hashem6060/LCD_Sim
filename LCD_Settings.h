#pragma once

const int LCD_WIDTH = 240;
const int LCD_HEIGHT = 120;
const int PIXEL_SIZE = 3;    // size of each pixel on screen
const int CHAR_WIDTH = 8;    // width of one char in pixels
const int CHAR_HEIGHT = 16;  // height of one char in pixels
const int CHAR_SPACING = 1;  // spacing between characters

const int LCD_COLS = LCD_WIDTH / CHAR_WIDTH;
const int LCD_ROWS = LCD_HEIGHT / CHAR_HEIGHT;

// Colors
struct Color {
    Uint8 r, g, b;
};

const Color COLOR_BLACK = { 0,0,0 };
const Color COLOR_WHITE = { 255,255,255 };