// lcd_emulator.cpp
#include "lcd_emulator.h"

LCDEmulator::LCDEmulator(int s, sf::Color on, sf::Color off)
    : canvas(sf::Vector2u(LCD_WIDTH, LCD_HEIGHT))
    , texture(sf::Vector2u(LCD_WIDTH, LCD_HEIGHT))
    , sprite(texture)
    , scale(s)
    , colorOn(on)
    , colorOff(off)
{
    // Initialize canvas with background color
    for (unsigned int y = 0; y < LCD_HEIGHT; ++y) {
        for (unsigned int x = 0; x < LCD_WIDTH; ++x) {
            canvas.setPixel(sf::Vector2u(x, y), colorOff);
        }
    }

    // Upload to texture and configure sprite
    texture.update(canvas);
    sprite.setScale(sf::Vector2f(static_cast<float>(scale),
        static_cast<float>(scale)));
}

void LCDEmulator::displayBitmap(const unsigned char* bitmapData) {
    // Clear canvas to background
    for (unsigned int y = 0; y < LCD_HEIGHT; ++y) {
        for (unsigned int x = 0; x < LCD_WIDTH; ++x) {
            canvas.setPixel(sf::Vector2u(x, y), colorOff);
        }
    }

    // Render page-based bitmap: 240 columns × 16 pages (8 bits/page)
    for (unsigned int page = 0; page < TOTAL_PAGES; ++page) {
        for (unsigned int x = 0; x < LCD_WIDTH; ++x) {
            const unsigned char data = bitmapData[page * LCD_WIDTH + x];

            // Each bit = one vertical pixel in this column
            for (unsigned int bit = 0; bit < 8; ++bit) {
                const unsigned int y = pageBitToY(page, bit);
                const bool pixelOn = (data >> bit) & 0x01;
                canvas.setPixel(sf::Vector2u(x, y), pixelOn ? colorOn : colorOff);
            }
        }
    }

    // Push changes to GPU
    texture.update(canvas);
}

void LCDEmulator::render(sf::RenderWindow& window) {
    window.draw(sprite);
}