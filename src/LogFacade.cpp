#include "LogFacade.h"

LogFacade::LogFacade(const std::string &filePath, const std::regex &filter)
    : watcher(filePath), filter(filter) {}

void LogFacade::start(const std::function<void(const std::string &)> &onLineFiltered) {
    watcher.start([this, onLineFiltered](const std::string &line) {
        if (std::regex_search(line, filter)) {
            onLineFiltered(line);
        }
    });
}
