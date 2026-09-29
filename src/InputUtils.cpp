#include "InputUtils.h"

#include <cmath>
#include <iostream>
#include <sstream>

namespace {

std::string readLine() {
    std::string line;

    if (!std::getline(std::cin, line)) {
        throw InputUtils::InputClosed();
    }

    return line;
}

}

namespace InputUtils {

double getDouble(const std::string& prompt) {
    while (true) {
        std::cout << prompt;

        std::stringstream input(readLine());

        double value{};
        char extra{};

        if ((input >> value) && !(input >> extra) && std::isfinite(value)) {
            return value;
        }

        std::cout << "[ERROR] Please enter a valid number.\n";
    }
}

int getInt(const std::string& prompt, int minValue, int maxValue) {
    while (true) {
        std::cout << prompt;

        std::stringstream input(readLine());

        int value{};
        char extra{};

        if ((input >> value) && !(input >> extra) &&
            value >= minValue && value <= maxValue) {
            return value;
        }

        std::cout << "[ERROR] Enter a value from "
                  << minValue << " to " << maxValue << ".\n";
    }
}

char getOperator(const std::string& prompt) {
    while (true) {
        std::cout << prompt;

        const std::string line = readLine();

        if (line.size() == 1 &&
            (line[0] == '+' || line[0] == '-' ||
             line[0] == '*' || line[0] == '/' ||
             line[0] == '%')) {
            return line[0];
        }

        std::cout << "[ERROR] Use +, -, *, / or %.\n";
    }
}

std::string getLine(const std::string& prompt) {
    std::cout << prompt;
    return readLine();
}

void waitForEnter() {
    std::cout << "\nPress Enter to return to the menu...";
    readLine();
}

}
