// lcd_emulator.h
#pragma once
#include <SFML/Graphics.hpp>

class LCDEmulator {
private:
    // LCD constants
    static constexpr unsigned int LCD_WIDTH = 240;
    static constexpr unsigned int LCD_HEIGHT = 128;
    static constexpr unsigned int PIXELS_PER_PAGE = 8;
    static constexpr unsigned int TOTAL_PAGES = LCD_HEIGHT / PIXELS_PER_PAGE;

    // SFML objects
    sf::Image canvas;
    sf::Texture texture;
    sf::Sprite sprite;

    // Configuration
    int scale;
    sf::Color colorOn;
    sf::Color colorOff;

    // Helper: convert page/bit to Y coordinate
    [[nodiscard]] static constexpr unsigned int pageBitToY(unsigned int page, unsigned int bit) {
        return page * PIXELS_PER_PAGE + bit;
    }

public:
    // Constructor with defaults (green monochrome LCD)
    LCDEmulator(int scale = 4,
        sf::Color on = sf::Color(30, 50, 30),
        sf::Color off = sf::Color(140, 160, 140));

    // Display a page-based bitmap (240×16 bytes)
    void displayBitmap(const unsigned char* bitmapData);

    // Render to window
    void render(sf::RenderWindow& window);

    // Getters (optional, for debugging)
    [[nodiscard]] constexpr unsigned int width() const { return LCD_WIDTH; }
    [[nodiscard]] constexpr unsigned int height() const { return LCD_HEIGHT; }
};