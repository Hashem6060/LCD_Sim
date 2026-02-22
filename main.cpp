// main.cpp
#include <SFML/Graphics.hpp>
#include "lcd_emulator.h"
#include "bitmap.h"

int main() {
    // Create window (scaled LCD: 240×128 → 960×512)
    sf::RenderWindow window(sf::VideoMode({ 960, 512 }), "LCD Emulator");
    window.setFramerateLimit(60);

    // Create LCD emulator (4× scale, green monochrome)
    LCDEmulator lcd(4);

    // Display your bitmap
    lcd.displayBitmap(nBitmapDC5XD);

    // Main render loop
    while (window.isOpen()) {
        // Handle events (SFML 3.x style)
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        // Render frame
        window.clear(sf::Color(30, 30, 30));  // Dark window background
        lcd.render(window);                    // Draw LCD
        window.display();                      // Present frame
    }

    return 0;
}