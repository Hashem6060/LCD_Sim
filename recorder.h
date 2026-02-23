// recorder.h - Simple frame recorder (PNG sequence)
#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <filesystem>

class FrameRecorder {
private:
    std::string outputPath;
    unsigned int frameCount = 0;
    bool recording = false;

public:
    // Start recording to folder
    bool start(const std::string& folder);

    // Capture current frame
    bool captureFrame(const sf::RenderWindow& window);

    // Stop recording
    void stop();

    // Check if recording
    [[nodiscard]] bool isRecording() const { return recording; }

    // Get frame count
    [[nodiscard]] unsigned int getFrameCount() const { return frameCount; }
};
