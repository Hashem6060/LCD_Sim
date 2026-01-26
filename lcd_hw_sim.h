#pragma once
#ifndef LCD_HW_SIM_H
#define LCD_HW_SIM_H

#include <stdint.h>

/* LCD resolution */
#define LCD_WIDTH   240
#define LCD_HEIGHT  128
#define LCD_PAGES   (LCD_HEIGHT / 8)

#define GUI_LCM_XMAX 240
#define GUI_LCM_YMAX 128

// Declare the buffer as external so multiple files can use it
extern uint8_t gui_disp_buf[GUI_LCM_YMAX][GUI_LCM_XMAX];


/* LCD RAM: [page][column] */
extern uint8_t lcd_ram[LCD_PAGES][LCD_WIDTH];

/* Hardware-compatible API */
void Write_Command_To_LCD(uint8_t cmd);
void Write_Data_To_LCD(uint8_t data);

/* Debug output */
void lcd_dump_bmp(const char* filename, const uint8_t* buffer);

void bitmap_to_gui_disp(const uint8_t* bmp, uint8_t width, uint8_t height, uint8_t gui_buf[GUI_LCM_YMAX][GUI_LCM_XMAX]);

#endif
