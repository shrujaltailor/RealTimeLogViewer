#pragma once
#include <string>
#include <regex>
#include "FileWatcher.h"

class LogFacade {
public:
    LogFacade(const std::string &filePath, const std::regex &filter);
    void start(const std::function<void(const std::string &)> &onLineFiltered);

private:
    FileWatcher watcher;
    std::regex filter;
};
