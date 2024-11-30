#include "CaptureCommand.h"
#include <fstream>  // For file output

CaptureCommand::CaptureCommand(const std::string& text) : text(text) {}

void CaptureCommand::execute() {
    std::ofstream file("log.txt", std::ios::app);  // Open file in append mode
    if (file.is_open()) {
        file << text << "\n";  // Write the text to the file
        file.close();  // Close the file
    }
}
