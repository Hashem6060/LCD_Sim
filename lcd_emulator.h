// lcd_emulator.h
#pragma once
#include <SFML/Graphics.hpp>

class LCDEmulator {
private:
    static constexpr unsigned int LCD_WIDTH = 240;
    static constexpr unsigned int LCD_HEIGHT = 128;
    static constexpr unsigned int PIXELS_PER_PAGE = 8;
    static constexpr unsigned int TOTAL_PAGES = LCD_HEIGHT / PIXELS_PER_PAGE;

    sf::Image canvas;
    sf::Texture texture;
    sf::Sprite sprite;

    int scale;
    sf::Color colorOn;
    sf::Color colorOff;

    [[nodiscard]] static constexpr unsigned int pageBitToY(unsigned int page, unsigned int bit) {
        return page * PIXELS_PER_PAGE + bit;
    }

public:
    LCDEmulator(int scale = 4,
        sf::Color on = sf::Color(30, 50, 30),
        sf::Color off = sf::Color(140, 160, 140));

    void displayBitmap(const unsigned char* bitmapData);
    void render(sf::RenderWindow& window);
    // Draw ASCII or Chinese text (GB2312 encoding)
    void displayText(const char* text, uint8_t x, uint8_t y, bool colorOn);

    void clear();

    void drawSimpleText(const char* text, int x, int y, bool pixelOn);
    // Save LCD canvas to PNG file
    [[nodiscard]] bool saveToPNG(const std::string& filepath) const;
};