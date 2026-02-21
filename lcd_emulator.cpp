
//int main() {
//    // Create window (960x512 to fit our scaled LCD)
//sf::RenderWindow window(sf::VideoMode({ 960, 512 }), "LCD Simulator");
//window.setFramerateLimit(60);
//
//// LCD dimensions
//const unsigned int LCD_WIDTH = 240;
//const unsigned int LCD_HEIGHT = 128;
//const int SCALE = 4;  // Scale up for visibility
//
//// Create the LCD background (dark green)
//sf::RectangleShape lcdBackground(sf::Vector2f(LCD_WIDTH* SCALE, LCD_HEIGHT* SCALE));
//lcdBackground.setFillColor(sf::Color(50, 70, 50));  // Dark green
//lcdBackground.setPosition({ 0, 0 });  // ✅ SFML 3.x: use brace-init or Vector2f
//
//// Main loop
//while (window.isOpen()) {
//    // Event handling (SFML 3.x style)
//    while (const std::optional event = window.pollEvent()) {
//        if (event->is<sf::Event::Closed>()) {
//            window.close();
//        }
//    }
//
//    // Draw
//    window.clear(sf::Color(30, 30, 30));  // Dark gray window background
//    window.draw(lcdBackground);            // Draw LCD screen
//    window.display();
//}
//
//return 0;
//}








//#include <SFML/Graphics.hpp>
//#include <iostream>
//
//int main() {
//    // Create window
//    sf::RenderWindow window(sf::VideoMode({ 960, 512 }), "LCD Simulator");
//    window.setFramerateLimit(60);
//
//    // LCD dimensions
//    const unsigned int LCD_WIDTH = 240;
//    const unsigned int LCD_HEIGHT = 128;
//    const int SCALE = 4;
//
//    // LCD colors
//    const sf::Color COLOR_OFF = sf::Color(140, 160, 140);  // Light green (pixel off)
//    const sf::Color COLOR_ON = sf::Color(30, 50, 30);      // Dark green (pixel on)
//
//    // === STEP 1: Create pixel canvas ===
//    sf::Image canvas(sf::Vector2u(LCD_WIDTH, LCD_HEIGHT));
//
//    // Fill with background color (all pixels off)
//    for (unsigned int y = 0; y < LCD_HEIGHT; y++) {
//        for (unsigned int x = 0; x < LCD_WIDTH; x++) {
//            canvas.setPixel(sf::Vector2u(x, y), COLOR_OFF);
//        }
//    }
//
//    // === STEP 2: Create texture ===
//    sf::Texture texture(sf::Vector2u(LCD_WIDTH, LCD_HEIGHT));
//    texture.update(canvas);
//
//    // === STEP 3: Create sprite WITH texture (SFML 3.x) ===
//    sf::Sprite sprite(texture);  // ✅ Pass texture to constructor
//    sprite.setScale(sf::Vector2f(SCALE, SCALE));
//
//    // === STEP 4: Draw a test pattern (horizontal lines) ===
//    for (unsigned int y = 0; y < LCD_HEIGHT; y += 8) {
//        for (unsigned int x = 0; x < LCD_WIDTH; x++) {
//            canvas.setPixel(sf::Vector2u(x, y), COLOR_ON);
//        }
//    }
//    texture.update(canvas);  // Update texture with new pixels
//
//    // Main loop
//    while (window.isOpen()) {
//        while (const std::optional event = window.pollEvent()) {
//            if (event->is<sf::Event::Closed>()) {
//                window.close();
//            }
//        }
//
//        window.clear(sf::Color(30, 30, 30));
//        window.draw(sprite);
//        window.display();
//    }
//
//    return 0;
//}