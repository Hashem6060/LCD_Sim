// main.cpp - LCD Emulator with Screenshot Support
// Press S to save screenshot, Esc to exit

#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include "simulation.h"
#include "lcd_emulator.h"
#include "bitmap.h"
#include "lcd_page.h"  // Main page display
#include "lcd_home.h"  // Home screen display



int main() {
    sf::RenderWindow window(sf::VideoMode({ 960, 512 }), "Generator LCD simulation");
    window.setFramerateLimit(60);

    LCDEmulator lcd(4);  // 4x scale
    // ===== Row 1: 20×20 Switch Symbols =====
 
    // Initial display
    lcd.clear();
   // lcd.displayText("System Ready", 80, 10, true);



    
    while (window.isOpen()) {
        // Handle events
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            // Add more event handling here later (keys, mouse, etc.)
        }
        //lcd.displayText("TIPS", 104, Y_MAIN_L0, true);
        //lcd.displayText("Press START to start engine", 0, Y_MAIN_L1, true);  // ← Shorter!
        //lcd.displayText("the engine!", 0, Y_MAIN_L1 + 16, true);

        Display_Operating_Prompt(lcd);
        lcd.drawFilledRect(0, 112, 239, 127, true);  // Black bar, bottom 16px
        lcd.updateTexture();


        // Render window (THE CRITICAL PART!)
        window.clear(sf::Color(30, 30, 30));
        lcd.render(window);
        window.display();  // ← Required to see anything!                     // Present to screen
    }

    return 0;
}