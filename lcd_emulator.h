// lcd_emulator.h
#pragma once
#include <SFML/Graphics.hpp>
#include <cstdint>
#include <string>

// ===== Font Descriptor (Keep this - working) =====
struct FontDescriptor {
    const uint8_t* data;
    uint8_t charWidth;
    uint8_t charHeight;
    uint8_t bytesPerChar;
    uint8_t firstChar;
    uint8_t lastChar;
    bool lsbIsLeft;

    constexpr FontDescriptor(const uint8_t* d, uint8_t w, uint8_t h, uint8_t bpc,
        uint8_t first = 0x20, uint8_t last = 0x7E, bool lsbLeft = true)
        : data(d), charWidth(w), charHeight(h), bytesPerChar(bpc),
        firstChar(first), lastChar(last), lsbIsLeft(lsbLeft) {
    }
};

class LCDEmulator {
private:
    // ===== Constants =====
    static constexpr unsigned int LCD_WIDTH = 240;
    static constexpr unsigned int LCD_HEIGHT = 128;
    static constexpr unsigned int PIXELS_PER_PAGE = 8;

    // ===== SFML Objects =====
    sf::Image canvas;
    sf::Texture texture;
    sf::Sprite sprite;

    // ===== Config =====
    int scale;
    sf::Color colorOn;
    sf::Color colorOff;

    // ===== Font State =====
    FontDescriptor currentFont;

    // ===== Helpers =====
    [[nodiscard]] static constexpr unsigned int pageBitToY(unsigned int page, unsigned int bit) {
        return page * PIXELS_PER_PAGE + bit;
    }
    void drawChar(unsigned char c, uint8_t x, uint8_t y, bool isOn);

public:
    // ===== Constructor =====
    LCDEmulator(int scale = 4,
        sf::Color on = sf::Color(35, 35, 35),
        sf::Color off = sf::Color(207, 233, 255));

    // ===== Core Methods =====
    void displayBitmap(const unsigned char* bitmapData);
    void render(sf::RenderWindow& window);
    void displayText(const char* text, uint8_t x, uint8_t y, bool isOn,
        const FontDescriptor* font = nullptr);
    void clear();
    [[nodiscard]] bool saveToPNG(const std::string& filepath) const;

    // ===== Font Management =====
    void setFont(const FontDescriptor& font);
    [[nodiscard]] const FontDescriptor& getFont() const;
    [[nodiscard]] static const FontDescriptor& getDefaultFont();

    // ===== Flexible Symbol Drawing (Any Size) =====
    // Column-major format, interleaved pages (same as your font)
    // - data: pointer to symbol bitmap array
    // - width: symbol width in pixels (also = bytes per page)
    // - height: symbol height in pixels
    // - x, y: top-left position on LCD
    // - isOn: use colorOn (true) or colorOff (false) for pixels
    void drawSymbol(const uint8_t* data, uint8_t width, uint8_t height,
        uint8_t x, uint8_t y, bool isOn);


    // ===== Accessors =====
    [[nodiscard]] sf::Image& getCanvas() { return canvas; }
    [[nodiscard]] const sf::Image& getCanvas() const { return canvas; }
    [[nodiscard]] sf::Color getColorOn() const { return colorOn; }
    [[nodiscard]] sf::Color getColorOff() const { return colorOff; }
    void updateTexture() { texture.update(canvas); }
    [[nodiscard]] static constexpr unsigned int width() { return LCD_WIDTH; }
    [[nodiscard]] static constexpr unsigned int height() { return LCD_HEIGHT; }
};