//#pragma once
//#include <SFML/Graphics.hpp>
//#include <iostream>
//#include <vector>
//#include <ctime>
//#include <string>
//
//class LCDEmulator {
//private:
//    const int LCD_WIDTH = 240;
//    const int LCD_HEIGHT = 128;
//    const int PIXELS_PER_PAGE = 8;
//    const int TOTAL_PAGES = LCD_HEIGHT / PIXELS_PER_PAGE;
//
//    int scale;
//    sf::Image canvas;
//    sf::Texture texture;
//    sf::Sprite sprite;
//
//    int currentX = 0;
//    int currentPage = 0;
//
//    sf::Color colorOn;
//    sf::Color colorOff;
//    bool showPixelGrid;
//
//public:
//    LCDEmulator(int s = 4,
//        sf::Color on = sf::Color::Black,
//        sf::Color off = sf::Color(140, 150, 140),
//        bool grid = false)
//        : scale(s), colorOn(on), colorOff(off), showPixelGrid(grid) {
//
//        // SFML 3.x: create() takes Vector2u and returns bool
//        if (!canvas.create(sf::Vector2u(static_cast<unsigned int>(LCD_WIDTH),
//            static_cast<unsigned int>(LCD_HEIGHT)))) {
//            std::cerr << "Failed to create canvas image!" << std::endl;
//            return;
//        }
//
//        // Fill with background color - SFML 3.x: setPixel takes Vector2u position
//        for (unsigned int y = 0; y < static_cast<unsigned int>(LCD_HEIGHT); y++) {
//            for (unsigned int x = 0; x < static_cast<unsigned int>(LCD_WIDTH); x++) {
//                canvas.setPixel(sf::Vector2u(x, y), colorOff);
//            }
//        }
//    }
//
//    void Write_Data_To_LCD(uint8_t data) {
//        for (int bit = 0; bit < 8; bit++) {
//            int y = (currentPage * PIXELS_PER_PAGE) + bit;
//            int x = currentX;
//
//            if (x < LCD_WIDTH && y < LCD_HEIGHT) {
//                bool pixelOn = (data >> bit) & 0x01;
//                canvas.setPixel(sf::Vector2u(x, y), pixelOn ? colorOn : colorOff);
//            }
//        }
//
//        currentX++;
//        if (currentX >= LCD_WIDTH) {
//            currentX = 0;
//            currentPage++;
//            if (currentPage >= TOTAL_PAGES) {
//                currentPage = 0;
//            }
//        }
//    }
//
//    void setCursor(int x, int page) {
//        currentX = x % LCD_WIDTH;
//        currentPage = page % TOTAL_PAGES;
//    }
//
//    void clear() {
//        for (int y = 0; y < LCD_HEIGHT; y++) {
//            for (int x = 0; x < LCD_WIDTH; x++) {
//                canvas.setPixel(sf::Vector2u(x, y), colorOff);
//            }
//        }
//        currentX = 0;
//        currentPage = 0;
//    }
//
//    void fillPattern(uint8_t pattern) {
//        clear();
//        for (int page = 0; page < TOTAL_PAGES; page++) {
//            for (int x = 0; x < LCD_WIDTH; x++) {
//                currentX = x;
//                currentPage = page;
//                Write_Data_To_LCD(pattern);
//            }
//        }
//    }
//
//    void render(sf::RenderWindow& window) {
//        // SFML 3.x: update texture from image
//        texture.update(canvas);
//        sprite.setTexture(texture);
//        sprite.setScale(sf::Vector2f(static_cast<float>(scale), static_cast<float>(scale)));
//        window.draw(sprite);
//
//        if (showPixelGrid) {
//            drawPixelGrid(window);
//        }
//    }
//
//    void drawPixelGrid(sf::RenderWindow& window) {
//        sf::RectangleShape gridLine;
//        gridLine.setFillColor(sf::Color(0, 0, 0, 50));
//
//        // Horizontal lines
//        gridLine.setSize(sf::Vector2f(LCD_WIDTH * scale, 1));
//        for (int page = 0; page <= TOTAL_PAGES; page++) {
//            gridLine.setPosition(sf::Vector2f(0, page * PIXELS_PER_PAGE * scale));
//            window.draw(gridLine);
//        }
//
//        // Vertical lines
//        gridLine.setSize(sf::Vector2f(1, LCD_HEIGHT * scale));
//        for (int x = 0; x <= LCD_WIDTH; x += 8) {
//            gridLine.setPosition(sf::Vector2f(x * scale, 0));
//            window.draw(gridLine);
//        }
//    }
//
//    void saveScreenshot() {
//        std::string filename = "lcd_capture_" + std::to_string(std::time(0)) + ".png";
//        if (canvas.saveToFile(filename)) {
//            std::cout << "Screenshot saved: " << filename << std::endl;
//        }
//    }
//
//    bool getPixel(int x, int y) const {
//        if (x >= 0 && x < LCD_WIDTH && y >= 0 && y < LCD_HEIGHT) {
//            sf::Color pixel = canvas.getPixel(sf::Vector2u(x, y));
//            return (pixel.r + pixel.g + pixel.b) < 300;
//        }
//        return false;
//    }
//};