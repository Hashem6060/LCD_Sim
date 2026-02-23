// lcd_emulator.cpp
#include "lcd_emulator.h"
#include "bitmap.h"

constexpr int FONT_CHAR_WIDTH = 8;
constexpr int FONT_CHAR_HEIGHT = 16;
constexpr int FONT_BYTES_PER_CHAR = 16;  // 8 rows × 2 bytes/row = 16
constexpr int FONT_FIRST_CHAR = 0x20;    // First character is space
constexpr int FONT_LAST_CHAR = 0x7F;     // Last character is DEL

static const uint8_t SIMPLE_FONT_8x8[] = {
    // 0x20 (space)
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    // 0x21 (!)
    0x10, 0x10, 0x10, 0x10, 0x10, 0x00, 0x10, 0x00,
    // ... add more as needed, or use a generator tool
    // For now, we'll just draw a placeholder box for unknown chars
};








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

    texture.update(canvas);
    sprite.setScale(sf::Vector2f(static_cast<float>(scale),
        static_cast<float>(scale)));
}

void LCDEmulator::displayBitmap(const unsigned char* bitmapData) {
    // Clear canvas
    for (unsigned int y = 0; y < LCD_HEIGHT; ++y) {
        for (unsigned int x = 0; x < LCD_WIDTH; ++x) {
            canvas.setPixel(sf::Vector2u(x, y), colorOff);
        }
    }

    // Render page-based bitmap (240 columns × 16 pages)
    for (unsigned int page = 0; page < TOTAL_PAGES; ++page) {
        for (unsigned int x = 0; x < LCD_WIDTH; ++x) {
            const unsigned char data = bitmapData[page * LCD_WIDTH + x];

            for (unsigned int bit = 0; bit < 8; ++bit) {
                const unsigned int y = pageBitToY(page, bit);
                const bool pixelOn = (data >> bit) & 0x01;
                canvas.setPixel(sf::Vector2u(x, y), pixelOn ? colorOn : colorOff);
            }
        }
    }

    texture.update(canvas);
}

void LCDEmulator::render(sf::RenderWindow& window) {
    window.draw(sprite);
}

bool LCDEmulator::saveToPNG(const std::string& filepath) const {
    // Ensure .png extension (SFML only supports PNG)
    std::string path = filepath;
    if (path.size() < 4 || path.substr(path.size() - 4) != ".png") {
        path += ".png";
    }
    return canvas.saveToFile(path);
}




void LCDEmulator::displayText(const char* text, uint8_t x, uint8_t y, bool isOn) {
    if (!text || x >= LCD_WIDTH || y >= LCD_HEIGHT) return;

    int posX = x;
    size_t len = std::strlen(text);

    for (size_t i = 0; i < len; ++i) {
        unsigned char c = static_cast<unsigned char>(text[i]);

        if (c < 0x20 || c > 0x7F) {
            posX += 8;
            continue;
        }

        int fontOffset = (c - 0x20) * 16;  // 16 bytes per character

        // Draw all 8 columns
        for (int col = 0; col < 8; ++col) {
            // Each column has 2 bytes: top 8 pixels + bottom 8 pixels
            uint8_t bitmapTop = FONT[fontOffset + col];         // Top half (rows 0-7)
            uint8_t bitmapBottom = FONT[fontOffset + col + 8];  // Bottom half (rows 8-15)

            // Draw top 8 pixels of this column
            for (int row = 0; row < 8; ++row) {
                bool pixelOn = (bitmapTop >> row) & 0x01;

                uint8_t px = static_cast<uint8_t>(posX + col);
                uint8_t py = static_cast<uint8_t>(y + row);

                if (px < LCD_WIDTH && py < LCD_HEIGHT) {
                    sf::Color drawColor = pixelOn == isOn ? colorOn : colorOff;
                    canvas.setPixel(sf::Vector2u(px, py), drawColor);
                }
            }

            // Draw bottom 8 pixels of this column
            for (int row = 0; row < 8; ++row) {
                bool pixelOn = (bitmapBottom >> row) & 0x01;

                uint8_t px = static_cast<uint8_t>(posX + col);
                uint8_t py = static_cast<uint8_t>(y + row + 8);  // +8 for bottom half

                if (px < LCD_WIDTH && py < LCD_HEIGHT) {
                    sf::Color drawColor = pixelOn == isOn ? colorOn : colorOff;
                    canvas.setPixel(sf::Vector2u(px, py), drawColor);
                }
            }
        }

        posX += 8;  // Move to next character

        if (posX + 8 > LCD_WIDTH) {
            posX = x;
        }
    }

    texture.update(canvas);
}


void LCDEmulator::drawSimpleText(const char* text, int x, int y, bool pixelOn) {
    if (!text) return;

    const int FONT_W = 8;
    const int FONT_H = 8;

    for (int i = 0; text[i] != '\0'; ++i) {
        unsigned char c = static_cast<unsigned char>(text[i]);

        // Only handle printable ASCII
        if (c < 0x20 || c > 0x7F) continue;

        int fontIdx = c - 0x20;

        // Draw character (8x8)
        for (int row = 0; row < FONT_H; ++row) {
            // Get font byte for this row (or 0 if not defined)
            uint8_t bitmap = (fontIdx < 95) ? SIMPLE_FONT_8x8[fontIdx * FONT_H + row] : 0x00;

            for (int col = 0; col < FONT_W; ++col) {
                // Extract bit: MSB = leftmost pixel
                bool pixel = (bitmap >> (7 - col)) & 0x01;

                int px = x + i * FONT_W + col;
                int py = y + row;

                // Bounds check + set pixel
                if (px >= 0 && px < static_cast<int>(LCD_WIDTH) &&
                    py >= 0 && py < static_cast<int>(LCD_HEIGHT)) {

                    // ✅ SFML 3.x: setPixel takes Vector2u position + Color
                    sf::Color drawColor = pixel == pixelOn ? colorOn : colorOff;
                    canvas.setPixel(sf::Vector2u(static_cast<unsigned int>(px),
                        static_cast<unsigned int>(py)),
                        drawColor);
                }
            }
        }
    }

    // ✅ Update texture to show changes
    texture.update(canvas);
}


void LCDEmulator::clear() {
    // Fill entire canvas with background color
    for (unsigned int y = 0; y < LCD_HEIGHT; ++y) {
        for (unsigned int x = 0; x < LCD_WIDTH; ++x) {
            canvas.setPixel(sf::Vector2u(x, y), colorOff);
        }
    }

    // Update texture to reflect changes
    texture.update(canvas);
}