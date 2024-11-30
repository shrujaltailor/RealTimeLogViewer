#include "LogViewer.h"
#include <QFileDialog>
#include <QTextStream>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QMessageBox>
#include <QScrollBar>

KeywordHighlighter::KeywordHighlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent) {
    keywordFormat.setForeground(Qt::red);  // Set the keyword highlight color
    keywordFormat.setFontWeight(QFont::Bold);
}

void KeywordHighlighter::setRegexPattern(const QString &pattern) {
    regexPattern = QRegularExpression(pattern);
    rehighlight();
}

void KeywordHighlighter::highlightBlock(const QString &text) {
    if (!regexPattern.isValid()) return;

    QRegularExpressionMatchIterator matchIterator = regexPattern.globalMatch(text);
    while (matchIterator.hasNext()) {
        QRegularExpressionMatch match = matchIterator.next();
        setFormat(match.capturedStart(), match.capturedLength(), keywordFormat);
    }
}

LogViewer::LogViewer(QWidget *parent)
    : QMainWindow(parent), fileWatcher(new QFileSystemWatcher(this)), timer(new QTimer(this)) {
    setWindowTitle("Real-Time Log Viewer");
    setGeometry(100, 100, 1200, 600);  // Increased width to fit side-by-side logs

    QWidget *centralWidget = new QWidget(this);

    // Create a main vertical layout for the window
    mainLayout = new QVBoxLayout(centralWidget);

    // Create a horizontal layout for the log files (side by side)
    logLayout = new QHBoxLayout();

    // Create widgets for controls at the bottom
    regexInput = new QLineEdit(centralWidget);
    applyRegexButton = new QPushButton("Search", centralWidget);
    fileSelectButton = new QPushButton("Select Log Files", centralWidget);
    captureButton = new QPushButton("Capture Logs", centralWidget);

    // Layout for buttons at the bottom
    QVBoxLayout *buttonLayout = new QVBoxLayout();
    buttonLayout->addWidget(fileSelectButton);
    buttonLayout->addWidget(captureButton);
    buttonLayout->addWidget(regexInput);
    buttonLayout->addWidget(applyRegexButton);

    // Create a QScrollArea to handle overflow when there are too many logs
    QScrollArea *scrollArea = new QScrollArea(centralWidget);
    QWidget *scrollWidget = new QWidget();
    scrollWidget->setLayout(logLayout);  // Set the log layout to the scrollable widget
    scrollArea->setWidget(scrollWidget);
    scrollArea->setWidgetResizable(true);

    // Add both the log display and the controls to the main layout
    mainLayout->addWidget(scrollArea);  // Add log display area at the top
    mainLayout->addLayout(buttonLayout);  // Add controls at the bottom

    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    connect(fileSelectButton, &QPushButton::clicked, this, &LogViewer::selectLogFiles);
    connect(captureButton, &QPushButton::clicked, this, &LogViewer::captureLogs);
    connect(applyRegexButton, &QPushButton::clicked, this, &LogViewer::applyRegex);
    connect(fileWatcher, &QFileSystemWatcher::fileChanged, this, &LogViewer::onFileUpdated);
    connect(timer, &QTimer::timeout, this, &LogViewer::pollLogFiles);
}

LogViewer::~LogViewer() {
    delete fileWatcher;
    delete timer;

    // Clean up the dynamic memory for the log files
    for (auto &logFile : logFiles) {
        delete logFile.highlighter;
        delete logFile.display;
    }
}

void LogViewer::selectLogFiles() {
    QStringList filePaths = QFileDialog::getOpenFileNames(this, "Select Log Files");
    if (!filePaths.isEmpty()) {
        for (const QString &filePath : filePaths) {
            // Create a new log file entry
            LogFile logFile;
            logFile.path = filePath;
            logFile.display = new QTextEdit(this);
            logFile.display->setReadOnly(true);
            logFile.highlighter = new KeywordHighlighter(logFile.display->document());

            logFiles.append(logFile);
            fileWatcher->addPath(filePath);

            // Add the QTextEdit for the log file to the layout
            logLayout->addWidget(logFile.display);  // Add to QHBoxLayout (side by side)
        }

        onFileUpdated();
    }
}

void LogViewer::captureLogs() {
    if (logFiles.isEmpty()) {
        QMessageBox::warning(this, "No Files Selected", "Please select at least one log file.");
        return;
    }

    for (auto &logFile : logFiles) {
        QFile file(logFile.path);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            logFile.display->setPlainText(in.readAll());
        } else {
            QMessageBox::critical(this, "Error", "Could not open the log file: " + logFile.path);
        }
    }
}

void LogViewer::onFileUpdated() {
    for (auto &logFile : logFiles) {
        QFile file(logFile.path);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);

            // Preserve the scroll position for each log file
            QScrollBar *scrollBar = logFile.display->verticalScrollBar();
            int scrollValue = scrollBar->value();
            bool atBottom = (scrollValue == scrollBar->maximum());

            logFile.display->setPlainText(in.readAll());

            if (atBottom) {
                scrollBar->setValue(scrollBar->maximum());
            } else {
                scrollBar->setValue(scrollValue);
            }
        }
    }
}

void LogViewer::pollLogFiles() {
    onFileUpdated();
}

void LogViewer::applyRegex() {
    QString regexPattern = regexInput->text();
    for (auto &logFile : logFiles) {
        logFile.highlighter->setRegexPattern(regexPattern);
    }
}
