#pragma once

#include <stdexcept>
#include <string>

namespace InputUtils {

// Thrown when stdin is closed (Ctrl+D / Ctrl+Z, or piped input runs out).
class InputClosed : public std::runtime_error {
public:
    InputClosed() : std::runtime_error("Input stream closed.") {}
};

double getDouble(const std::string& prompt);
int getInt(const std::string& prompt, int minValue, int maxValue);
char getOperator(const std::string& prompt);
std::string getLine(const std::string& prompt);
void waitForEnter();

}
