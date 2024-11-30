#ifndef LOGVIEWER_H
#define LOGVIEWER_H

#include <QMainWindow>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QFileSystemWatcher>
#include <QTimer>
#include <QSyntaxHighlighter>
#include <QRegularExpression>
#include <QHBoxLayout>  // Use QHBoxLayout for side-by-side positioning
#include <QList>         // Include the header for QList
#include <QFile>         // Include the header for QFile

class KeywordHighlighter : public QSyntaxHighlighter {
    Q_OBJECT

public:
    explicit KeywordHighlighter(QTextDocument *parent = nullptr);

    void setRegexPattern(const QString &pattern);

protected:
    void highlightBlock(const QString &text) override;

private:
    QRegularExpression regexPattern;
    QTextCharFormat keywordFormat;
};

// Define the LogFile structure to store log file data
struct LogFile {
    QString path;           // Log file path
    QTextEdit *display;     // QTextEdit to display the log
    KeywordHighlighter *highlighter;  // Highlighter for keyword matching
};

class LogViewer : public QMainWindow {
    Q_OBJECT

public:
    explicit LogViewer(QWidget *parent = nullptr);
    ~LogViewer();

private slots:
    void selectLogFiles();
    void captureLogs();
    void onFileUpdated();
    void pollLogFiles();
    void applyRegex();

private:
    QVBoxLayout *mainLayout;  // Main layout for the window
    QHBoxLayout *logLayout;   // Horizontal layout for displaying log files side by side
    QList<LogFile> logFiles; // Keep track of the log files

    QLineEdit *regexInput;
    QPushButton *applyRegexButton;
    QPushButton *fileSelectButton;
    QPushButton *captureButton;
    QFileSystemWatcher *fileWatcher;
    QTimer *timer;
};

#endif // LOGVIEWER_H
