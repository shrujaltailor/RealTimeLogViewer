#include "FilterDecorator.h"
#include <QString>
#include <QRegularExpression>
#include <QRegularExpressionMatchIterator> 

// Constructor
FilterDecorator::FilterDecorator(LogViewer* viewer) : viewer(viewer) {}

// Highlight Matching Lines
QString FilterDecorator::highlightMatches(const QString& log, const QString& regexPattern) {
    QRegularExpression regex(regexPattern);
    QString highlightedLog = log;
    QRegularExpressionMatchIterator i = regex.globalMatch(log);

    // Highlight matches
    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        QString matchedText = match.captured();
        highlightedLog.replace(matchedText, "<b><span style='color:red;'>" + matchedText + "</span></b>");
    }

    return highlightedLog;
}