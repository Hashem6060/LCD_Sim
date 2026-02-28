// lcd_display.cpp
#include "simulation.h"
#include <string>


// Process status strings (from your C array)
const char displayEnglishRowProcess[26][17] = {
    "Stop Idle Speed",   // 00
    "under stop",        // 01
    "Waiting",           // 02
    "Crank Cancel",      // 03
    "Crank Interval",    // 04
    "Alarm,Reset",       // 05
    "Standby...",        // 06
    "Pre-heat",          // 07
    "Pre-oil Supply",    // 08
    "Crank Delay",       // 09
    "Crank Ready",       // 10
    "Cranking",          // 11
    "Safety Delay",      // 12
    "Idle speed",        // 13
    "Speed-up",          // 14
    "Temperature-up",    // 15
    "Volt-built/up",     // 16
    "Hi-speed warming",  // 17
    "Rated running",     // 18
    "Mains return",      // 19
    "Cooling running",   // 20
    "Gens return",       // 21
    "Waiting cooling",   // 22
    "Switching",         // 23
    "    ",              // 24 (4 spaces)
    "Wating switch"      // 25 (typo preserved from original)
};

// Lock symbol: 16×16 pixels, 32 bytes (column-major, LSB=top)
const uint8_t LOCK_SYMBOL_16x16[32] = {
    // Columns 0-15, top 8 rows (page 0)
    0x00, 0x00, 0xC0, 0xF0, 0xFC, 0xFC, 0xCE, 0xC6,
    0xC6, 0xCE, 0xFC, 0xFC, 0xF0, 0xC0, 0x00, 0x00,
    // Columns 0-15, bottom 8 rows (page 1)
    0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE1,
    0xE1, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00
};

// Draw 16×16 symbol (column-major bitmap, LSB=top pixel)
void drawSymbol16x16(LCDEmulator& lcd, const uint8_t* bitmap,
    uint8_t x, uint8_t y, bool isOn) {
    // Draw all 16 columns
    for (int col = 0; col < 16; ++col) {
        uint8_t top = bitmap[col];          // Top 8 pixels
        uint8_t bottom = bitmap[col + 16];  // Bottom 8 pixels

        // Draw top half (rows 0-7)
        for (int row = 0; row < 8; ++row) {
            bool pixelOn = (top >> row) & 0x01;  // LSB = top
            uint8_t px = x + col;
            uint8_t py = y + row;
            if (px < 240 && py < 128) {
                sf::Color c = pixelOn == isOn ? lcd.getColorOn() : lcd.getColorOff();
                lcd.getCanvas().setPixel(sf::Vector2u(px, py), c);
            }
        }

        // Draw bottom half (rows 8-15)
        for (int row = 0; row < 8; ++row) {
            bool pixelOn = (bottom >> row) & 0x01;
            uint8_t px = x + col;
            uint8_t py = y + row + 8;
            if (px < 240 && py < 128) {
                sf::Color c = pixelOn == isOn ? lcd.getColorOn() : lcd.getColorOff();
                lcd.getCanvas().setPixel(sf::Vector2u(px, py), c);
            }
        }
    }
    lcd.updateTexture();
}

// Main display logic (simulates Display_english_row_Page_static)
void displayEnglishRowPageStatic(LCDEmulator& lcd, const DisplayState& state) {
    constexpr uint8_t START_X = 0;

    // Condition 1: Switch change (ignored per your request - assume false)
    // if (state.switch_co_status == PROCESS_ATS_DO) { ... }

    // Condition 2: Meter mode
    if (state.key_disable == U8_HIGH &&
        state.meter_mode == U8_HIGH &&
        state.remote_mode == U8_LOW) {
        lcd.clear();
        lcd.displayText("Meter Mode", START_X, Y_MAIN_L4, true);
    }
    // Condition 3: Key disable + lock symbol
    else if (state.key_disable == U8_HIGH &&
        state.meter_mode == U8_LOW &&
        state.remote_mode == U8_LOW) {
        lcd.clear();

        // Display process string
        if (state.num_process < 26) {
            lcd.displayText(displayEnglishRowProcess[state.num_process],
                START_X, Y_MAIN_L4, true);
        }

        // Draw lock symbol at (192, Y_MAIN_L4)
        drawSymbol16x16(lcd, LOCK_SYMBOL_16x16, 192, Y_MAIN_L4, true);
    }
    // Condition 4: Default + optional timer
    else {
        lcd.clear();

        // Display process string
        if (state.num_process < 26) {
            lcd.displayText(displayEnglishRowProcess[state.num_process],
                START_X, Y_MAIN_L4, true);
        }

        // Optional countdown timer display
        if (state.en_disp_second == U8_HIGH) {
            // Convert timer_delay (100ms units) to seconds
            uint8_t seconds = static_cast<uint8_t>(state.timer_delay / 10);

            // Display seconds at x=192
            std::string secStr = std::to_string(seconds);
            lcd.displayText(secStr.c_str(), 192, Y_MAIN_L4, true);

            // Display "S" at x=224
            lcd.displayText("S", 224, Y_MAIN_L4, true);
        }
    }
}