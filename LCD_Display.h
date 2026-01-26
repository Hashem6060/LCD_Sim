//#pragma once
//#include <SDL2/SDL.h>
//#include <vector>
//#include <string>
//#include "LCD_Settings.h"
//
//class LCD_Display {
//public:
//    LCD_Display();
//    ~LCD_Display();
//
//    bool init();
//    void clear();
//    void drawPixel(int x, int y, const Color& color);
//    void drawChar(char c, int row, int col, const Color& color);
//    void drawString(const std::string& str, int row, int col, const Color& color);
//    void drawBitmap(const std::vector<unsigned char>& bmp, int x, int y, int width, int height);
//    void update();
//    void delay(int ms);
//
//private:
//    SDL_Window* window;
//    SDL_Renderer* renderer;
//};