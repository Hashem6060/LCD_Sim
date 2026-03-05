// lcd_emulator.cpp
#include "lcd_emulator.h"
#include "bitmap.h"
#include <algorithm>


// ==== = Default Font ==== =
static const FontDescriptor DEFAULT_FONT(
    reinterpret_cast<const uint8_t*>(FONT_ASCII_8x16),
    8, 16, 16, 0x20, 0x7E, true  // LSB = left
);

// ===== Constructor (Simple - no DEFAULT_FONT variable needed) =====
LCDEmulator::LCDEmulator(int s, sf::Color on, sf::Color off)
    : canvas(sf::Vector2u(LCD_WIDTH, LCD_HEIGHT))
    , texture(sf::Vector2u(LCD_WIDTH, LCD_HEIGHT))
    , sprite(texture)
    , scale(s), colorOn(on), colorOff(off)
    , currentFont(
        reinterpret_cast<const uint8_t*>(FONT_ASCII_8x16),  // data
        8,   // charWidth
        16,  // charHeight
        16,  // bytesPerChar
        0x20, 0x7E,  // first/last char
        true  // lsbIsLeft
    )
{
    clear();
    sprite.setScale(sf::Vector2f(static_cast<float>(scale),
        static_cast<float>(scale)));
}

// ===== Font Management =====
void LCDEmulator::setFont(const FontDescriptor& font) { currentFont = font; }
const FontDescriptor& LCDEmulator::getFont() const { return currentFont; }
const FontDescriptor& LCDEmulator::getDefaultFont() { return DEFAULT_FONT; }

// ===== Draw Single Character (Keep - working) =====
void LCDEmulator::drawChar(unsigned char c, uint8_t x, uint8_t y, bool isOn) {
    const auto& font = currentFont;
    if (c < font.firstChar || c > font.lastChar) return;

    int fontOffset = (c - font.firstChar) * font.bytesPerChar;

    for (int row = 0; row < font.charHeight; ++row) {
        uint8_t bitmap = font.data[fontOffset + row];
        for (int col = 0; col < font.charWidth; ++col) {
            bool pixelOn = font.lsbIsLeft
                ? (bitmap >> col) & 0x01
                : (bitmap >> (font.charWidth - 1 - col)) & 0x01;

            if (x + col < LCD_WIDTH && y + row < LCD_HEIGHT) {
                canvas.setPixel(sf::Vector2u(x + col, y + row),
                    pixelOn == isOn ? colorOn : colorOff);
            }
        }
    }
}

// ===== Display Text (Keep - working) =====
void LCDEmulator::displayText(const char* text, uint8_t x, uint8_t y, bool isOn,
    const FontDescriptor* fontOverride) {
    if (!text || x >= LCD_WIDTH || y >= LCD_HEIGHT) return;
    const FontDescriptor* font = fontOverride ? fontOverride : &currentFont;

    int posX = x;
    for (int i = 0; text[i]; ++i) {
        unsigned char c = static_cast<unsigned char>(text[i]);
        if (c < font->firstChar || c > font->lastChar) {
            posX += font->charWidth;
            continue;
        }

        int fontOffset = (c - font->firstChar) * font->bytesPerChar;

        // Column-major, interleaved pages (like your font)
        for (int col = 0; col < font->charWidth; ++col) {
            uint8_t top = font->data[fontOffset + col];
            uint8_t bottom = font->data[fontOffset + col + 8];

            for (int row = 0; row < 8; ++row) {
                bool pixelOn = (top >> row) & 0x01;
                if (x + col < LCD_WIDTH && y + row < LCD_HEIGHT) {
                    canvas.setPixel(sf::Vector2u(posX + col, y + row),
                        pixelOn == isOn ? colorOn : colorOff);
                }
                pixelOn = (bottom >> row) & 0x01;
                if (x + col < LCD_WIDTH && y + row + 8 < LCD_HEIGHT) {
                    canvas.setPixel(sf::Vector2u(posX + col, y + row + 8),
                        pixelOn == isOn ? colorOn : colorOff);
                }
            }
        }
        posX += font->charWidth;
    }
}

// ===== Flexible Symbol Drawing (Any Size) =====
void LCDEmulator::drawSymbol(const uint8_t* data, uint8_t width, uint8_t height,
    uint8_t x, uint8_t y, bool isOn) {
    if (!data || width == 0 || height == 0) return;

    // Calculate number of pages (1 page = 8 vertical pixels)
    uint8_t pages = (height + 7) / 8;  // e.g., 16→2, 20→3, 24→3

    // Column-major, interleaved pages (SAME pattern as your font!)
    for (uint8_t col = 0; col < width; ++col) {
        for (uint8_t page = 0; page < pages; ++page) {
            // ✅ KEY FORMULA: Same as your working font
            // Byte for this column+page = col + page * width
            uint8_t byteIdx = col + page * width;
            uint8_t bitmap = data[byteIdx];
            uint8_t baseRow = page * 8;  // Starting row for this page

            // Extract up to 8 pixels from this byte (LSB = top pixel)
            for (uint8_t bit = 0; bit < 8; ++bit) {
                uint8_t row = baseRow + bit;

                // Skip if beyond symbol height
                if (row >= height) break;

                // Extract pixel: LSB = top pixel within byte
                bool pixelOn = (bitmap >> bit) & 0x01;

                uint8_t px = static_cast<uint8_t>(x + col);
                uint8_t py = static_cast<uint8_t>(y + row);

                if (px < LCD_WIDTH && py < LCD_HEIGHT) {
                    sf::Color drawColor = pixelOn == isOn ? colorOn : colorOff;
                    canvas.setPixel(sf::Vector2u(px, py), drawColor);
                }
            }
        }
    }
    // Note: Caller should call updateTexture() after drawing
}

// ===== Clear Canvas =====
void LCDEmulator::clear() {
    for (unsigned int y = 0; y < LCD_HEIGHT; ++y)
        for (unsigned int x = 0; x < LCD_WIDTH; ++x)
            canvas.setPixel(sf::Vector2u(x, y), colorOff);
    texture.update(canvas);
}

// ===== Display Bitmap =====
void LCDEmulator::displayBitmap(const unsigned char* bitmapData) {
    clear();
    for (unsigned int page = 0; page < LCD_HEIGHT / 8; ++page) {
        for (unsigned int x = 0; x < LCD_WIDTH; ++x) {
            uint8_t data = bitmapData[page * LCD_WIDTH + x];
            for (unsigned int bit = 0; bit < 8; ++bit) {
                unsigned int y = pageBitToY(page, bit);
                bool pixelOn = (data >> bit) & 0x01;
                canvas.setPixel(sf::Vector2u(x, y), pixelOn ? colorOn : colorOff);
            }
        }
    }
    texture.update(canvas);
}

// ===== Render & Save =====
void LCDEmulator::render(sf::RenderWindow& window) { window.draw(sprite); }
bool LCDEmulator::saveToPNG(const std::string& filepath) const {
    std::string path = filepath;
    if (path.size() < 4 || path.substr(path.size() - 4) != ".png") path += ".png";
    return canvas.saveToFile(path);
}


// ===== Draw Filled Rectangle (Like GUI_RectangleFill) =====
void LCDEmulator::drawFilledRect(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, bool isOn) {
    // Ensure coordinates are in valid order
    if (x0 > x1) std::swap(x0, x1);
    if (y0 > y1) std::swap(y0, y1);

    // Clamp to LCD bounds
    x0 = std::max(x0, uint8_t(0));
    y0 = std::max(y0, uint8_t(0));
    x1 = std::min(x1, uint8_t(LCD_WIDTH - 1));
    y1 = std::min(y1, uint8_t(LCD_HEIGHT - 1));

    // Fill rectangle with color
    sf::Color fillColor = isOn ? colorOn : colorOff;
    for (uint8_t y = y0; y <= y1; ++y) {
        for (uint8_t x = x0; x <= x1; ++x) {
            canvas.setPixel(sf::Vector2u(x, y), fillColor);
        }
    }
    // Note: Caller should call updateTexture() after drawing
}