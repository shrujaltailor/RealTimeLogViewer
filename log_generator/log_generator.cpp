// log_generator/log_generator.cpp
#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>
#include <random>
#include <vector>

// Function to get a random log type
std::string getRandomLogType() {
    static const std::vector<std::string> logTypes = {
        "INFO", "DEBUG", "WARNING", "ERROR", "CRITICAL"
    };
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dist(0, logTypes.size() - 1);

    return logTypes[dist(gen)];
}

// Function to get a random log message
std::string getRandomLogMessage(const std::string& logType) {
    static const std::vector<std::string> messages = {
        "Initialization complete",
        "Processing request",
        "Database connection established",
        "Disk usage is high",
        "User authentication failed",
        "Configuration file missing",
        "Data successfully processed",
        "Memory allocation error",
        "File not found",
        "Network connection lost"
    };

    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dist(0, messages.size() - 1);

    return "[" + logType + "] " + messages[dist(gen)];
}

// Log generation function
void generateLogFile(const std::string& filename) {
    std::ofstream logFile(filename, std::ios::app);

    if (!logFile.is_open()) {
        std::cerr << "Failed to open log file: " << filename << "\n";
        return;
    }

    int counter = 0;
    while (true) {
        std::string logType = getRandomLogType();
        std::string logMessage = getRandomLogMessage(logType);

        // Write log to the file
        logFile << "Log entry " << counter++ << ": " << logMessage << std::endl;
        logFile.flush();

        // Simulate delay between log entries
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    }
}

int main() {
    std::string logFilePath = "application.log";
    generateLogFile(logFilePath);
    return 0;
}
