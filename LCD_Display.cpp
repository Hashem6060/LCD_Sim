//#include "LCD_Display.h"
//#include "Fonts.h"   // your array of fonts
//
//LCD_Display::LCD_Display() : window(nullptr), renderer(nullptr) {}
//
//LCD_Display::~LCD_Display() {
//    if (renderer) SDL_DestroyRenderer(renderer);
//    if (window) SDL_DestroyWindow(window);
//    SDL_Quit();
//}
//
//bool LCD_Display::init() {
//    SDL_Init(SDL_INIT_VIDEO);
//    window = SDL_CreateWindow("LCD Simulator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, LCD_WIDTH * PIXEL_SIZE, LCD_HEIGHT * PIXEL_SIZE, 0);
//    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
//    clear();
//    return window && renderer;
//}
//
//void LCD_Display::clear() {
//    SDL_SetRenderDrawColor(renderer, COLOR_BLACK.r, COLOR_BLACK.g, COLOR_BLACK.b, 255);
//    SDL_RenderClear(renderer);
//    SDL_RenderPresent(renderer);
//}
//
//void LCD_Display::drawPixel(int x, int y, const Color& color) {
//    SDL_Rect rect = { x * PIXEL_SIZE, y * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE };
//    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
//    SDL_RenderFillRect(renderer, &rect);
//}
//
//void LCD_Display::drawChar(char c, int row, int col, const Color& color) {
//    const unsigned char* bitmap = Fonts::getCharBitmap(c); // implement Fonts::getCharBitmap
//    for (int y = 0; y < CHAR_HEIGHT; ++y) {
//        for (int x = 0; x < CHAR_WIDTH; ++x) {
//            if (bitmap[y] & (1 << (7 - x))) {
//                drawPixel(col * CHAR_WIDTH + x, row * CHAR_HEIGHT + y, color);
//            }
//        }
//    }
//}
//
//void LCD_Display::drawString(const std::string& str, int row, int col, const Color& color) {
//    for (size_t i = 0; i < str.size(); ++i) {
//        drawChar(str[i], row, col + i, color);
//    }
//}
//
//void LCD_Display::drawBitmap(const std::vector<unsigned char>& bmp, int x0, int y0, int width, int height) {
//    for (int y = 0; y < height; ++y) {
//        for (int x = 0; x < width; ++x) {
//            int byteIndex = (y * width + x) / 8;
//            int bitIndex = 7 - ((y * width + x) % 8);
//            if (bmp[byteIndex] & (1 << bitIndex)) {
//                drawPixel(x0 + x, y0 + y, COLOR_WHITE);
//            }
//        }
//    }
//}
//
//void LCD_Display::update() {
//    SDL_RenderPresent(renderer);
//}
//
//void LCD_Display::delay(int ms) {
//    SDL_Delay(ms);
//}
