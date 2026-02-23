// recorder.cpp
#include "recorder.h"
#include "screenshot.h"
#include <iostream>

bool FrameRecorder::start(const std::string& folder) {
    // Create output directory
    if (!std::filesystem::exists(folder)) {
        if (!std::filesystem::create_directories(folder)) {
            std::cerr << "Failed to create folder: " << folder << std::endl;
            return false;
        }
    }

    outputPath = folder;
    frameCount = 0;
    recording = true;
    std::cout << "Recording started: " << outputPath << std::endl;
    return true;
}

bool FrameRecorder::captureFrame(const sf::RenderWindow& window) {
    if (!recording) return false;

    // Generate filename: frame_0001.png, frame_0002.png, etc.
    char filename[64];
    snprintf(filename, sizeof(filename), "/frame_%04d.png", ++frameCount);

    return saveScreenshot(window, outputPath + filename);
}

void FrameRecorder::stop() {
    if (recording) {
        std::cout << "Recording stopped. Captured " << frameCount << " frames." << std::endl;
        std::cout << "To create GIF/MP4: ffmpeg -r 30 -i frame_%04d.png output.gif" << std::endl;
    }
    recording = false;
}