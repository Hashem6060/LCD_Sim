// screenshot.cpp
#include "screenshot.h"

// Optional: JPG support via stb_image_write
#ifdef USE_STB
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>
#endif

bool saveScreenshot(const sf::RenderWindow& window, const std::string& filepath) {
    // ✅ SFML 3.x: Capture via Texture

    // 1. Get window size
    auto size = window.getSize();

    // 2. Create texture with window dimensions
    sf::Texture texture(size);

    // 3. Update texture from window framebuffer
    // ⚠️ SFML 3.x: update() returns void, not bool!
    texture.update(window);  // ✅ No return value to check

    // 4. Copy texture to image for saving
    sf::Image screenshot = texture.copyToImage();

    // 5. Save based on extension
    if (filepath.size() >= 4) {
        std::string ext = filepath.substr(filepath.size() - 4);

        // PNG: Use SFML (always works)
        if (ext == ".png" || ext == ".PNG") {
            return screenshot.saveToFile(filepath);  // ✅ saveToFile returns bool
        }

        // JPG: Use stb_image_write if available
#ifdef USE_STB
        else if (ext == ".jpg" || ext == ".JPG" || ext == ".jpeg" || ext == ".JPEG") {
            auto pixels = screenshot.getPixelsPtr();
            auto imgSize = screenshot.getSize();
            return stbi_write_jpg(filepath.c_str(), imgSize.x, imgSize.y, 4, pixels, 90) != 0;
        }
#endif
    }

    // Default: save as PNG
    return screenshot.saveToFile(filepath + ".png");
}