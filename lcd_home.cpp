// lcd_home.cpp
#include "lcd_home.h"
#include <string>
#include <sstream>
#include <iomanip>

// ===== Symbol Bitmap Data (from your nSign_Dot2416) =====
// Format: 6 symbols × 48 bytes each
// Each symbol: 24 columns × 16 rows, column-major, LSB = top pixel
static const uint8_t SIGN_KR_2416[6][48] = {
    // Index 0: Oil Pressure (油压) - 24×16 bitmap
    {
        0x7C,0xEC,0xDC,0xF8,0x60,0x66,0x66,0x7E,0x7E,0x66,0x66,0x60,0xE0,0xC0,0xC0,0xE0,
        0x60,0x70,0xB0,0xF8,0x3C,0x04,0x0C,0x00,  // Top 8 rows (columns 0-23)
        0x00,0x00,0x3F,0x3F,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x18,
        0x1E,0x03,0x01,0x00,0x00,0x06,0x0F,0x06   // Bottom 8 rows (columns 0-23)
    },
    // Index 1: Temperature (温度) - 24×16 bitmap
    {
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xCC,0xCC,0xCC,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0xCC,0xCC,0xE6,0x66,0x6C,0x6C,0x60,0xCC,0xDE,0xDF,0xDF,0xDE,0xCC,0x60,
        0x6C,0x6C,0x66,0xE6,0xCC,0xCC,0x00,0x00
    },
    // Index 2: Oil Level (油位) - commented in original, included for completeness
    {
        0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xC3,0xC3,0xC3,0xC3,0xC3,0xFF,0xFF,0x00,0x00,
        0x02,0x0C,0x1C,0x38,0xE0,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x80,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8E,0x0C,
        0x38,0x60,0x30,0x1E,0x07,0x00,0x00,0x00
    },
    // Index 3: Battery (电瓶) - 24×16 bitmap
    {
        0x00,0x00,0xF8,0xF8,0x18,0x1E,0x1E,0x1E,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x98,
        0x9E,0x1E,0x1E,0x18,0xF8,0xF8,0x00,0x00,
        0x00,0x00,0x7F,0x7F,0x60,0x60,0x63,0x63,0x63,0x63,0x60,0x60,0x60,0x60,0x63,0x67,
        0x67,0x63,0x60,0x60,0x7F,0x7F,0x00,0x00
    },
    // Index 4: RPM Dial (转速盘) - 24×16 bitmap
    {
        0x00,0x00,0x00,0x00,0x00,0xE0,0xF0,0x38,0x1F,0x1F,0x83,0xF3,0x73,0x03,0x1F,0x1F,
        0x38,0xF0,0xE0,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x0F,0x1F,0x30,0x60,0xCF,0xCD,0xCC,0xCC,0xCC,0xCC,0x60,
        0x30,0x1F,0x0F,0x00,0x00,0x00,0x00,0x00
    },
    // Index 5: Reserved/Unused
    {0}
};

// ===== Helper: Format float to string =====
std::string formatValue(float value, int decimals = 1) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(decimals) << value;
    return oss.str();
}

// ===== Draw 24×16 symbol (column-major, LSB = top pixel) =====
void drawSymbol24x16(LCDEmulator& lcd, const uint8_t symbolSet[][48],
    uint8_t symbolIndex, uint8_t x, uint8_t y, bool isOn) {
    const uint8_t* bitmap = symbolSet[symbolIndex];  // Get pointer to specific symbol

    for (int col = 0; col < 24; ++col) {
        uint8_t top = bitmap[col];           // Top 8 pixels
        uint8_t bottom = bitmap[col + 24];   // Bottom 8 pixels

        for (int row = 0; row < 8; ++row) {
            bool pixelOn = (top >> row) & 0x01;
            if (x + col < 240 && y + row < 128) {
                sf::Color c = (pixelOn == isOn) ? lcd.getColorOn() : lcd.getColorOff();
                lcd.getCanvas().setPixel(sf::Vector2u(x + col, y + row), c);
            }
            pixelOn = (bottom >> row) & 0x01;
            if (x + col < 240 && y + row + 8 < 128) {
                sf::Color c = (pixelOn == isOn) ? lcd.getColorOn() : lcd.getColorOff();
                lcd.getCanvas().setPixel(sf::Vector2u(x + col, y + row + 8), c);
            }
        }
    }
    lcd.updateTexture();
}

// ===== Main Home Screen Display Function =====
void displayHomeScreen(LCDEmulator& lcd, const HomeScreenState& state) {
    lcd.clear();

    // ===== ROW 0 (Y=0): Phase info + Frequency =====
    if (state.generator_phase == 1) {
        // Single phase: "L-L:N:"
        lcd.displayText("L", 0, Y_MAIN_L0, true);
        lcd.displayText("-", 12, Y_MAIN_L0, true);
        lcd.displayText("N:", 24, Y_MAIN_L0, true);
    }
    else {
        // Three phase: "L-L:L:"
        lcd.displayText("L", 0, Y_MAIN_L0, true);
        lcd.displayText("-", 12, Y_MAIN_L0, true);
        lcd.displayText("L:", 24, Y_MAIN_L0, true);
    }
    lcd.displayText("FREQ:", 120, Y_MAIN_L0, true);

    // ===== ROW 1 (Y=28): Current + Power =====
    lcd.displayText("AMPS:", 0, Y_MAIN_L1, true);
    lcd.displayText("POWER:", 112, Y_MAIN_L1, true);

    // ===== ROW 2 (Y=56): Battery + RPM symbols + colons =====
    drawSymbol24x16(lcd, SIGN_KR_2416, SYM_BATTERY, 8, Y_MAIN_L2, true);
    drawSymbol24x16(lcd, SIGN_KR_2416, SYM_RPM, 128, Y_MAIN_L2, true);
    lcd.displayText(":", 32, Y_MAIN_L2, true);
    lcd.displayText(":", 152, Y_MAIN_L2, true);

    // ===== ROW 3 (Y=84): Temp + Oil symbols + colons =====
    drawSymbol24x16(lcd, SIGN_KR_2416, SYM_TEMPERATURE, 8, Y_MAIN_L3, true);
    drawSymbol24x16(lcd, SIGN_KR_2416, SYM_OIL_PRESSURE, 128, Y_MAIN_L3, true);
    lcd.displayText(":", 32, Y_MAIN_L3, true);
    lcd.displayText(":", 152, Y_MAIN_L3, true);

    // ===== UNIT LABELS (right side) =====
    // Voltage unit
    lcd.displayText("V", 92, Y_UNIT_L0, true);
    lcd.displayText("Hz", 224, Y_UNIT_L0, true);

    // Current/Power unit
    lcd.displayText("A", 92, Y_UNIT_L1, true);
    lcd.displayText("KW", 224, Y_UNIT_L1, true);

    // RPM unit
    lcd.displayText("V", 92, Y_UNIT_L2, true);
    lcd.displayText("RPM", 216, Y_UNIT_L2, true);

    // Temperature unit (°C or °F)
    if (state.unit_setting < 3) {
        lcd.displayText("C", 92, Y_UNIT_L3, true);  // Celsius
    }
    else {
        lcd.displayText("F", 92, Y_UNIT_L3, true);  // Fahrenheit
    }

    // Pressure unit (KPA/BAR/PSI)
    const char* pressureUnit = (state.unit_setting == 0 || state.unit_setting == 3) ? "KPA" :
        (state.unit_setting == 1 || state.unit_setting == 4) ? "BAR" : "PSI";
    lcd.displayText(pressureUnit, 216, Y_UNIT_L3, true);

    // ===== NUMERIC VALUES (simulated sensor readings) =====

    // Voltage (after "N:" or "L:")
    float voltage = (state.generator_phase == 1) ? state.voltage_LN : state.voltage_LL;
    lcd.displayText(formatValue(voltage).c_str(), 48, Y_MAIN_L0, true);

    // Frequency (after "FREQ:")
    lcd.displayText(formatValue(state.frequency).c_str(), 168, Y_MAIN_L0, true);

    // Current (after "AMPS:")
    lcd.displayText(formatValue(state.current).c_str(), 48, Y_MAIN_L1, true);

    // Power (after "POWER:")
    lcd.displayText(formatValue(state.power).c_str(), 168, Y_MAIN_L1, true);

    // Battery (after battery icon + ":")
    lcd.displayText(formatValue(state.battery_volts).c_str(), 48, Y_MAIN_L2, true);

    // RPM (after RPM icon + ":") - no decimals for RPM
    lcd.displayText(formatValue(state.rpm, 0).c_str(), 168, Y_MAIN_L2, true);

    // Temperature (after temp icon + ":")
    lcd.displayText(formatValue(state.temperature).c_str(), 48, Y_MAIN_L3, true);

    // Oil pressure (after oil icon + ":")
    lcd.displayText(formatValue(state.oil_pressure).c_str(), 168, Y_MAIN_L3, true);
}