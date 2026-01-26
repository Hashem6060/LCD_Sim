#define _CRT_SECURE_NO_WARNINGS
#include "lcd_hw_sim.h"
#include <stdio.h>
#include <string.h>

/* ================= LCD RAM ================= */
uint8_t lcd_ram[LCD_PAGES][LCD_WIDTH];

/* ============ Internal LCD State ============ */
static uint8_t cur_page = 0;
static uint8_t cur_col = 0;

static uint8_t win_x_start = 0;
static uint8_t win_x_end = LCD_WIDTH - 1;

static uint8_t win_page_start = 0;
static uint8_t win_page_end = LCD_PAGES - 1;


uint8_t gui_disp_buf[GUI_LCM_YMAX][GUI_LCM_XMAX] = { 0 };

/* ============================================ */

void Write_Command_To_LCD(uint8_t cmd)
{
    /* Column address */
    if ((cmd & 0xF0) == 0x04) {
        cur_col = cmd & 0x0F;
        return;
    }

    /* Page address */
    if ((cmd & 0xF0) == 0x60) {
        cur_page = cmd & 0x0F;
        return;
    }

    switch (cmd) {

    case 0xF4:  /* X start */
        /* next command sets start */
        return;

    case 0xF6:  /* X end */
        return;

    case 0xF5:  /* Page start */
        return;

    case 0xF7:  /* Page end */
        return;

    case 0xF9:  /* Window enable */
        cur_col = win_x_start;
        cur_page = win_page_start;
        return;

    case 0x01:  /* Write RAM */
        return;

    default:
        /* Ignore unused commands */
        return;
    }
}

/* ------------------------------------------------ */

void Write_Data_To_LCD(uint8_t data)
{
    if (cur_page > win_page_end || cur_col > win_x_end)
        return;

    lcd_ram[cur_page][cur_col] = data;

    cur_col++;

    if (cur_col > win_x_end) {
        cur_col = win_x_start;
        cur_page++;
        if (cur_page > win_page_end)
            cur_page = win_page_start;
    }
}

/* ------------------------------------------------ */
/* Dump LCD RAM to PBM (portable bitmap) file       */
/* ------------------------------------------------ */
void lcd_dump_bmp(const char* filename, const uint8_t* buffer)
{
    FILE* f = fopen(filename, "wb");
    if (!f) return;

    uint32_t filesize = 54 + 3 * LCD_WIDTH * LCD_HEIGHT;
    uint8_t bmpfileheader[14] = {
        'B','M',          // Signature
        0,0,0,0,          // File size
        0,0,              // Reserved
        0,0,              // Reserved
        54,0,0,0          // Offset to pixel data
    };
    uint8_t bmpinfoheader[40] = {
        40,0,0,0,         // Header size
        0,0,0,0,          // Width
        0,0,0,0,          // Height
        1,0,              // Planes
        24,0,             // Bits per pixel
        0,0,0,0,          // Compression
        0,0,0,0,          // Image size
        0x13,0x0B,0,0,    // X pixels/m
        0x13,0x0B,0,0,    // Y pixels/m
        0,0,0,0,          // Colors used
        0,0,0,0           // Important colors
    };

    bmpfileheader[2] = (uint8_t)(filesize);
    bmpfileheader[3] = (uint8_t)(filesize >> 8);
    bmpfileheader[4] = (uint8_t)(filesize >> 16);
    bmpfileheader[5] = (uint8_t)(filesize >> 24);

    bmpinfoheader[4] = (uint8_t)(LCD_WIDTH);
    bmpinfoheader[5] = (uint8_t)(LCD_WIDTH >> 8);
    bmpinfoheader[6] = (uint8_t)(LCD_WIDTH >> 16);
    bmpinfoheader[7] = (uint8_t)(LCD_WIDTH >> 24);

    bmpinfoheader[8] = (uint8_t)(LCD_HEIGHT);
    bmpinfoheader[9] = (uint8_t)(LCD_HEIGHT >> 8);
    bmpinfoheader[10] = (uint8_t)(LCD_HEIGHT >> 16);
    bmpinfoheader[11] = (uint8_t)(LCD_HEIGHT >> 24);

    fwrite(bmpfileheader, 1, 14, f);
    fwrite(bmpinfoheader, 1, 40, f);

    // Write pixel data (BGR) bottom-to-top
    for (int y = LCD_HEIGHT - 1; y >= 0; y--) {
        for (int x = 0; x < LCD_WIDTH; x++) {
            uint8_t byte = buffer[(y / 8) * LCD_WIDTH + x];
            uint8_t bit = 1 << (y % 8);
            uint8_t pixel = (byte & bit) ? 0 : 255; // 1=black, 0=white
            uint8_t color[3] = { pixel, pixel, pixel };
            fwrite(color, 1, 3, f);
        }
    }

    fclose(f);
}

void bitmap_to_gui_disp(const uint8_t* bmp, uint8_t width, uint8_t height, uint8_t gui_buf[GUI_LCM_YMAX][GUI_LCM_XMAX]) {
    uint16_t bytes_per_col = (height + 7) / 8;

    for (uint16_t x = 0; x < width; x++) {
        for (uint16_t y = 0; y < height; y++) {
            uint16_t byte_index = (x * bytes_per_col) + (y / 8);
            uint8_t bit_index = y % 8;

            // CHANGE: Try (0x80 >> bit_index) if (1 << bit_index) was wrong
            // This treats the Most Significant Bit as the first pixel (top-most)
            if (bmp[byte_index] & (0x80 >> bit_index)) {
                gui_buf[y][x] = 0x00; // Black
            }
            else {
                gui_buf[y][x] = 0xFF; // White
            }
        }
    }
}