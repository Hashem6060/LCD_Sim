// main.cpp - LCD Emulator with Screenshot Support
// Press S to save screenshot, Esc to exit

#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>

#include "lcd_emulator.h"
#include "bitmap.h"

int main() {
    // Create window (240×128 LCD scaled 4x = 960×512)
    sf::RenderWindow window(sf::VideoMode({ 960, 512 }), "LCD Emulator");
    window.setFramerateLimit(30);

    // Create LCD emulator (green monochrome, 4x scale)
    LCDEmulator lcd(4);

    // Display your bitmap
    //lcd.displayBitmap(nBitmapDC5XD);

    lcd.clear();
    lcd.displayText("5121", 10, 10, true);   // dark green pixels
    lcd.displayText("the screen is working ", 10, 30, true);

    // Ensure window is ready for rendering
    window.display();
    sf::sleep(sf::milliseconds(50));

    std::cout << "LCD Emulator Ready\n"
        << "  [S] Save screenshot (PNG)\n"
        << "  [Esc] Exit\n" << std::endl;

    // Main loop
    while (window.isOpen()) {
        // Handle events (SFML 3.x style)
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
                switch (key->scancode) {
                case sf::Keyboard::Scancode::Escape:
                    window.close();
                    break;

                case sf::Keyboard::Scancode::S:  // Save screenshot
                {
                    // Generate timestamped filename: lcd_20260222_143022.png
                    char filename[64];
                    // Replace the localtime section with this:
                    std::time_t now = std::time(nullptr);
                    std::tm timeinfo{};

#ifdef _WIN32
                    // Windows: use localtime_s
                    if (localtime_s(&timeinfo, &now) == 0) {
                        std::strftime(filename, sizeof(filename), "lcd_%Y%m%d_%H%M%S.png", &timeinfo);
                    }
#else
                    // Linux/Mac: use localtime
                    std::tm* tmp = std::localtime(&now);
                    if (tmp != nullptr) {
                        timeinfo = *tmp;
                        std::strftime(filename, sizeof(filename), "lcd_%Y%m%d_%H%M%S.png", &timeinfo);
                    }
#endif

                    // Save LCD canvas to PNG
                    if (lcd.saveToPNG(filename)) {
                        std::cout << "✓ Saved: " << filename << "\n";
                    }
                    else {
                        std::cerr << "✗ Failed to save screenshot\n";
                    }
                    break;
                }
                }
            }
        }

        // Render frame
        window.clear(sf::Color(30, 30, 30));  // Dark window background
        lcd.render(window);                    // Draw LCD content
        window.display();                      // Present to screen
    }

    return 0;
}