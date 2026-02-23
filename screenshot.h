#pragma once
// screenshot.h
#pragma once
#include <SFML/Graphics.hpp>
#include <string>

// Save SFML render window to file (PNG or JPG)
bool saveScreenshot(const sf::RenderWindow& window, const std::string& filepath);

// Save sf::Image to file (PNG only - SFML limitation)
inline bool saveImage(const sf::Image& image, const std::string& filepath) {
    return image.saveToFile(filepath);  // SFML only supports PNG
}