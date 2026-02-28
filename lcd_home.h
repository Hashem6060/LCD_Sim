#pragma once
// lcd_home.h - Home screen display for LCD emulator
#include "lcd_emulator.h"
#include <cstdint>

// ===== Y Positions (calculated from your defines) =====
constexpr uint8_t nSTART = 0;
constexpr uint8_t nNULL = 12;  // gap rows
constexpr uint8_t nDOT = 16;  // text row height

constexpr uint8_t Y_MAIN_L0 = nSTART;                          // 0
constexpr uint8_t Y_MAIN_L1 = Y_MAIN_L0 + nDOT + nNULL;       // 28
constexpr uint8_t Y_MAIN_L2 = Y_MAIN_L1 + nDOT + nNULL;       // 56
constexpr uint8_t Y_MAIN_L3 = Y_MAIN_L2 + nDOT + nNULL;       // 84

constexpr uint8_t Y_UNIT_L0 = Y_MAIN_L0;
constexpr uint8_t Y_UNIT_L1 = Y_MAIN_L1;
constexpr uint8_t Y_UNIT_L2 = Y_MAIN_L2;
constexpr uint8_t Y_UNIT_L3 = Y_MAIN_L3;

// ===== Settings indices (for set_variable array) =====
constexpr uint8_t eSET_generator_phase = 0;  // 1=single phase, 0=three phase
constexpr uint8_t eSET_unit = 1;              // 0-4 for unit selection

// ===== Symbol indices for SIGN_KR_2416 =====
constexpr uint8_t SYM_OIL_PRESSURE = 0;  // 油压
constexpr uint8_t SYM_TEMPERATURE = 1;  // 温度
constexpr uint8_t SYM_BATTERY = 3;  // 电瓶
constexpr uint8_t SYM_RPM = 4;  // 转速盘

// ===== Home screen state =====
struct HomeScreenState {
    // Settings (toggle with keys)
    uint8_t generator_phase;  // 1 = single phase (L-L:N), 0 = three phase (L-L:L)
    uint8_t unit_setting;     // 0=°C/KPA, 1=°C/BAR, 2=°C/PSI, 3=°F/KPA, 4=°F/BAR

    // Simulated sensor readings (edit these values)
    float voltage_LN;    // L-N voltage (single phase)
    float voltage_LL;    // L-L voltage (three phase)
    float frequency;     // Hz
    float current;       // Amps
    float power;         // KW
    float battery_volts; // V
    float rpm;           // RPM (integer)
    float temperature;   // °C or °F
    float oil_pressure;  // KPA/BAR/PSI
};

// Draw the complete home screen
void displayHomeScreen(LCDEmulator& lcd, const HomeScreenState& state);

// Draw a 24×16 symbol from the SIGN_KR_2416 set
void drawSymbol24x16(LCDEmulator& lcd, const uint8_t symbolSet[][48],
    uint8_t symbolIndex, uint8_t x, uint8_t y, bool isOn);