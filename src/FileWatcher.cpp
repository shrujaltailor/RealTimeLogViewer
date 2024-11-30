#include "FileWatcher.h"
#include <fstream>
#include <sstream>
#include <chrono>
#include <iostream>

FileWatcher::FileWatcher(const std::string &filePath) : filePath(filePath), watching(false) {}

FileWatcher::~FileWatcher() {
    watching = false;
    if (watcherThread.joinable()) {
        watcherThread.join();
    }
}

void FileWatcher::start(const std::function<void(const std::string &)> &onLineRead) {
    watching = true;
    watcherThread = std::thread([this, onLineRead]() {
        std::ifstream file(filePath);
        std::string line;

        while (watching) {
            while (std::getline(file, line)) {
                onLineRead(line);
            }

            if (file.eof()) {
                file.clear();
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    });
}
