#ifndef CAPTURECOMMAND_H
#define CAPTURECOMMAND_H

#include <string>
#include <fstream>  // For file output

class CaptureCommand {
public:
    CaptureCommand(const std::string& text);  // Constructor with text parameter
    void execute();  // Execute command (e.g., write text to file)

private:
    std::string text;  // Member variable to store the text
};

#endif // CAPTURECOMMAND_H
