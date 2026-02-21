#include <SFML/Graphics.hpp>
#include <iostream>

// ============================================
// YOUR BITMAP ARRAY (replace with your actual data)
// ============================================
extern unsigned char nBitmapDC5XD[240 * 16];  // Your actual array from header

// For testing, create a simple pattern
unsigned char testBitmap[240 * 16] = { 0 };

void initTestBitmap() {
    for (int i = 0; i < 240 * 16; i++) {
        testBitmap[i] = (i % 2 == 0) ? 0b10101010 : 0b01010101;
    }
}

// ============================================
// LCD Emulator Class (SFML 3.x Fixed)
// ============================================
class LCDEmulator {
private:
    const unsigned int LCD_WIDTH = 240;
    const unsigned int LCD_HEIGHT = 128;
    const unsigned int PIXELS_PER_PAGE = 8;
    const unsigned int TOTAL_PAGES = LCD_HEIGHT / PIXELS_PER_PAGE;  // 16 pages

    int scale;
    sf::Image canvas;
    sf::Texture texture;
    sf::Sprite sprite;  // ← Will be initialized in constructor with texture

    sf::Color colorOn;
    sf::Color colorOff;

public:
    LCDEmulator(int s = 4,
        sf::Color on = sf::Color(30, 50, 30),
        sf::Color off = sf::Color(140, 160, 140))
        : scale(s), colorOn(on), colorOff(off),
        // ✅ SFML 3.x: Initialize in order (canvas → texture → sprite)
        canvas(sf::Vector2u(LCD_WIDTH, LCD_HEIGHT)),
        texture(sf::Vector2u(LCD_WIDTH, LCD_HEIGHT)),
        sprite(texture)  // ← Pass texture to sprite constructor
    {
        // Fill canvas with background color
        for (unsigned int y = 0; y < LCD_HEIGHT; y++) {
            for (unsigned int x = 0; x < LCD_WIDTH; x++) {
                canvas.setPixel(sf::Vector2u(x, y), colorOff);
            }
        }

        // Upload initial canvas to texture
        texture.update(canvas);

        // Set sprite scale
        sprite.setScale(sf::Vector2f(static_cast<float>(scale), static_cast<float>(scale)));
    }

    // ============================================
    // Display bitmap array on LCD
    // ============================================
    void displayBitmap(const unsigned char* bitmapData) {
        // Clear canvas first
        for (unsigned int y = 0; y < LCD_HEIGHT; y++) {
            for (unsigned int x = 0; x < LCD_WIDTH; x++) {
                canvas.setPixel(sf::Vector2u(x, y), colorOff);
            }
        }

        // Draw bitmap data (page-based format: 240 columns × 16 pages)
        for (unsigned int page = 0; page < TOTAL_PAGES; page++) {
            for (unsigned int x = 0; x < LCD_WIDTH; x++) {
                unsigned char data = bitmapData[page * LCD_WIDTH + x];

                for (int bit = 0; bit < 8; bit++) {
                    unsigned int y = (page * PIXELS_PER_PAGE) + bit;
                    if (y < LCD_HEIGHT) {
                        bool pixelOn = (data >> bit) & 0x01;
                        canvas.setPixel(sf::Vector2u(x, y), pixelOn ? colorOn : colorOff);
                    }
                }
            }
        }

        // Update texture to show changes
        texture.update(canvas);
    }

    void render(sf::RenderWindow& window) {
        window.draw(sprite);
    }
};

// ============================================
// Main Function
// ============================================
int main() {
    // Initialize test bitmap
    initTestBitmap();

    // Create window
    sf::RenderWindow window(sf::VideoMode({ 960, 512 }), "LCD Bitmap Display");
    window.setFramerateLimit(60);

    // Create LCD emulator
    LCDEmulator lcd(4);

    // Display the bitmap
    lcd.displayBitmap(testBitmap);  // Replace with: nBitmapDC5XD

    // Main loop
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        window.clear(sf::Color(30, 30, 30));
        lcd.render(window);
        window.display();
    }

    return 0;
}