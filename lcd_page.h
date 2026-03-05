#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include "simulation.h"
#include "lcd_emulator.h"
#include "bitmap.h"
#define nLINE 5//¹²ÏÔÊ¾NÐÐ 5ÐÐ 6ÐÐ
#if (nLINE==5)
#define nDOT 16//ÐÅÏ¢ÐÐµãÊý
#define nNULL 12//¿Õ¸ñÐÐµãÊý
#define nSTART 0//Ê×ÐÐÆðÊ¼µã
#define nDOWN 0//µ¥Î»ÏÔÊ¾ÏÂÒÆÁ¿
#else
#define nDOT 16//ÐÅÏ¢ÐÐµãÊý
#define nNULL 6//¿Õ¸ñÐÐµãÊý
#define nSTART 2//Ê×ÐÐÆðÊ¼µã
#define nDOWN 0//µ¥Î»ÏÔÊ¾ÏÂÒÆÁ¿
#endif

#define Y_MAIN_L0 nSTART
#define Y_UNIT_L0 Y_MAIN_L0+nDOWN

#define Y_MAIN_L1 Y_MAIN_L0+nDOT+nNULL
#define Y_UNIT_L1 Y_MAIN_L1+nDOWN

#define Y_MAIN_L2 Y_MAIN_L1+nDOT+nNULL
#define Y_UNIT_L2 Y_MAIN_L2+nDOWN

#define Y_MAIN_L3 Y_MAIN_L2+nDOT+nNULL
#define Y_UNIT_L3 Y_MAIN_L3+nDOWN

#define Y_MAIN_L4 Y_MAIN_L3+nDOT+nNULL
#define Y_UNIT_L4 Y_MAIN_L4+nDOWN

#define Y_MAIN_L5 Y_MAIN_L4+nDOT+nNULL
#define Y_UNIT_L5 Y_MAIN_L5+nDOWN

// ✅ Declarations only (no definitions, no = nullptr)
extern sf::RenderWindow* g_window;
extern LCDEmulator* g_lcd;








void Display_Operating_Prompt(LCDEmulator& g_lcd);