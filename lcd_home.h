//#pragma once
//// lcd_home.h - Home screen display for LCD emulator
//#include "lcd_emulator.h"
//#include <cstdint>
//
//// ===== Y Positions (using #define for compatibility) =====
//#define nSTART 0
//#define nNULL 12        // gap rows
//#define nDOT 16         // text row height
//
//#define Y_MAIN_L0 nSTART                          // 0
//#define Y_MAIN_L1 (Y_MAIN_L0 + nDOT + nNULL)     // 28
//#define Y_MAIN_L2 (Y_MAIN_L1 + nDOT + nNULL)     // 56
//#define Y_MAIN_L3 (Y_MAIN_L2 + nDOT + nNULL)     // 84
//
//#define Y_UNIT_L0 Y_MAIN_L0
//#define Y_UNIT_L1 Y_MAIN_L1
//#define Y_UNIT_L2 Y_MAIN_L2
//#define Y_UNIT_L3 Y_MAIN_L3
//
//// ===== Settings indices =====
//#define eSET_generator_phase 0
//#define eSET_unit 1
//
//// ===== Symbol indices for SIGN_KR_2416 =====
//#define SYM_OIL_PRESSURE 0
//#define SYM_TEMPERATURE 1
//#define SYM_BATTERY 3
//#define SYM_RPM 4
//
//// ===== Home screen state =====
//struct HomeScreenState {
//    uint8_t generator_phase;
//    uint8_t unit_setting;
//    float voltage_LN;
//    float voltage_LL;
//    float frequency;
//    float current;
//    float power;
//    float battery_volts;
//    float rpm;
//    float temperature;
//    float oil_pressure;
//};
//
//
//// Draw the complete home screen
//void displayHomeScreen(LCDEmulator& lcd, const HomeScreenState& state);
//
//// Draw a 24×16 symbol from the SIGN_KR_2416 set
//void drawSymbol24x16(LCDEmulator& lcd, const uint8_t symbolSet[][48],
//    uint8_t symbolIndex, uint8_t x, uint8_t y, bool isOn);