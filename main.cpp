// main.cpp - LCD Emulator with Screenshot Support
// Press S to save screenshot, Esc to exit

#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include "simulation.h"
#include "lcd_emulator.h"
#include "bitmap.h"

#include "lcd_home.h"  // Home screen display






int main() {
    sf::RenderWindow window(sf::VideoMode({ 960, 512 }), "Generator LCD simulation");
    window.setFramerateLimit(60);

    LCDEmulator lcd(4);  // 4x scale
    // ===== Row 1: 20×20 Switch Symbols =====
   // 16×16 lock symbol (2 bytes/row)
    lcd.clear();

    // 8×16 symbol (16 bytes = 8 cols × 2 pages)
    lcd.drawSymbol(SendReceive_Dot816[0], 8, 16, 8, 10, true);
    lcd.drawSymbol(SendReceive_Dot816[1], 8, 16, 16, 10, true);

    // 16×16 symbol (32 bytes = 16 cols × 2 pages)
    lcd.drawSymbol(nSign_Dot1616[0], 16, 16, 32, 10, true);

    // 18×16 RSSI symbol (36 bytes = 18 cols × 2 pages)
    lcd.drawSymbol(RSSI_Dot1816[9], 18, 16, 48, 10, true);

    // 20×20 symbol (60 bytes = 20 cols × 3 pages)
    lcd.drawSymbol(nSign_Dot2020[0], 20, 20, 70, 10, true);
    lcd.drawSymbol(nSign_Dot2020[1], 20, 20, 92, 10, true);
    lcd.drawSymbol(nSign_Dot2020[2], 20, 20, 114, 10, true);
    lcd.drawSymbol(nSign_Dot2020[3], 20, 20, 136, 10, true);
    lcd.drawSymbol(nSign_Dot2020[4], 20, 20, 158, 10, true);
    lcd.drawSymbol(nSign_Dot2020[5], 20, 20, 180, 10, true);

    // 24×16 symbol (48 bytes = 24 cols × 2 pages)
    int x = 8;
    lcd.drawSymbol(nSign_Dot2416[0], 24, 16, x, 40, true);
    lcd.drawSymbol(nSign_Dot2416[1], 24, 16, x+26, 40, true);
    lcd.drawSymbol(nSign_Dot2416[2], 24, 16, x+2*26, 40, true);
    lcd.drawSymbol(nSign_Dot2416[3], 24, 16, x+3*26, 40, true);
    lcd.drawSymbol(nSign_Dot2416[4], 24, 16, x+4*26, 40, true);
    lcd.drawSymbol(nSign_Dot2416[5], 24, 16, x+5*26, 40, true);

    lcd.updateTexture();  // ← REQUIRED!
    
    while (window.isOpen()) {
        // Handle events
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            // Add more event handling here later (keys, mouse, etc.)
        }

        // Render frame
        window.clear(sf::Color(30, 30, 30));  // Dark window background
        lcd.render(window);                    // Draw blank LCD
        window.display();                      // Present to screen
    }

    return 0;
}