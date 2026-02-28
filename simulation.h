// lcd_display.h
#pragma once
#include "lcd_emulator.h"
#include <cstdint>
#include <string>

// Display constants
constexpr uint8_t Y_MAIN_L4 = 112;      // Calculated: 84 + 16 + 12
constexpr uint8_t U8_HIGH = 1;
constexpr uint8_t U8_LOW = 0;

// Process status strings (26 entries, max 16 chars + null)
extern const char displayEnglishRowProcess[26][17];

// Lock symbol bitmap (16×16 pixels, 32 bytes)
extern const uint8_t LOCK_SYMBOL_16x16[32];

// System state for display logic
struct DisplayState {
    uint8_t switch_co_status;    // Ignored for now (assume false branch)
    uint8_t key_disable;
    uint8_t meter_mode;
    uint8_t remote_mode;
    uint8_t num_process;         // Index 0-25 into process strings
    uint8_t en_disp_second;      // Show timer flag
    uint32_t timer_delay;        // In 100ms units (divide by 10 for seconds)
};

// Main display function (simulates Display_english_row_Page_static)
void displayEnglishRowPageStatic(LCDEmulator& lcd, const DisplayState& state);

// Helper: Draw 16×16 symbol (like lock icon)
void drawSymbol16x16(LCDEmulator& lcd, const uint8_t* bitmap,
    uint8_t x, uint8_t y, bool isOn);