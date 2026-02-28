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
    sf::RenderWindow window(sf::VideoMode({ 960, 512 }), "Generator LCD Home");
    window.setFramerateLimit(60);

    LCDEmulator lcd(4);  // 4x scale

    // ===== Initial home screen state (edit these values!) =====
    HomeScreenState state = {};

    // Settings (toggle with keys 1-5)
    state.generator_phase = 0;  // 0 = three phase, 1 = single phase
    state.unit_setting = 0;     // 0=°C/KPA

    // Simulated sensor readings - EDIT THESE TO MATCH YOUR SYSTEM!
    state.voltage_LN = 230.5f;   // L-N voltage
    state.voltage_LL = 400.2f;   // L-L voltage  
    state.frequency = 50.0f;     // Hz
    state.current = 12.5f;       // Amps
    state.power = 5.2f;          // KW
    state.battery_volts = 12.8f; // V
    state.rpm = 1500;            // RPM (integer)
    state.temperature = 85.3f;   // °C
    state.oil_pressure = 4.2f;   // KPA/BAR/PSI

    std::cout << "Generator LCD Home Screen\n"
        << "  [1] Toggle Phase: Three/L-N\n"
        << "  [2-6] Cycle Unit: C/KPA, C/BAR, C/PSI, F/KPA, F/BAR\n"
        << "  [S] Save screenshot\n"
        << "  [Esc] Exit\n" << std::endl;

    while (window.isOpen()) {
        // ===== Event Handling =====
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
                switch (key->scancode) {
                case sf::Keyboard::Scancode::Escape:
                    window.close();
                    break;

                case sf::Keyboard::Scancode::Num1:  // Toggle phase
                    state.generator_phase = state.generator_phase ? 0 : 1;
                    break;

                case sf::Keyboard::Scancode::Num2: state.unit_setting = 0; break;  // °C/KPA
                case sf::Keyboard::Scancode::Num3: state.unit_setting = 1; break;  // °C/BAR
                case sf::Keyboard::Scancode::Num4: state.unit_setting = 2; break;  // °C/PSI
                case sf::Keyboard::Scancode::Num5: state.unit_setting = 3; break;  // °F/KPA
                case sf::Keyboard::Scancode::Num6: state.unit_setting = 4; break;  // °F/BAR

                case sf::Keyboard::Scancode::S:  // Save screenshot
                {
                    char filename[64];
                    std::time_t now = std::time(nullptr);
                    std::tm timeinfo{};
#ifdef _WIN32
                    if (localtime_s(&timeinfo, &now) == 0) {
                        std::strftime(filename, sizeof(filename),
                            "lcd_%Y%m%d_%H%M%S.png", &timeinfo);
                    }
#else
                    std::tm* tmp = std::localtime(&now);
                    if (tmp) {
                        timeinfo = *tmp;
                        std::strftime(filename, sizeof(filename),
                            "lcd_%Y%m%d_%H%M%S.png", &timeinfo);
                    }
#endif
                    if (lcd.saveToPNG(filename)) {
                        std::cout << "✓ Saved: " << filename << "\n";
                    }
                    break;
                }
                }
            }
        }

        // ===== Update and Render Home Screen =====
        displayHomeScreen(lcd, state);

        window.clear(sf::Color(30, 30, 30));
        lcd.render(window);
        window.display();
    }

    return 0;
}