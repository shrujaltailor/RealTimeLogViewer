#ifndef FILTERDECORATOR_H
#define FILTERDECORATOR_H

#include <QString>  // Include necessary Qt header for QString

class LogViewer;  // Forward declaration of LogViewer class

class FilterDecorator {
public:
    FilterDecorator(LogViewer* viewer);  // Constructor declaration
    QString highlightMatches(const QString& log, const QString& regexPattern);  // Function declaration

private:
    LogViewer* viewer;  // Member variable to store the LogViewer reference
};

#endif // FILTERDECORATOR_H
