#pragma once
#include <string>
#include <functional>
#include <thread>
#include <atomic>

class FileWatcher {
public:
    explicit FileWatcher(const std::string &filePath);
    ~FileWatcher();

    void start(const std::function<void(const std::string &)> &onLineRead);

private:
    std::string filePath;
    std::atomic<bool> watching;
    std::thread watcherThread;
};
