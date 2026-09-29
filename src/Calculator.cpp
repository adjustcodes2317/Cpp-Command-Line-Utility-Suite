#include "Calculator.h"
#include "InputUtils.h"

#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>

namespace Calculator {

double calculate(double first, double second, char operation) {
    switch (operation) {
        case '+':
            return first + second;
        case '-':
            return first - second;
        case '*':
            return first * second;
        case '/':
            if (second == 0.0) {
                throw std::domain_error("Cannot divide by zero.");
            }
            return first / second;
        case '%':
            if (second == 0.0) {
                throw std::domain_error("Cannot use zero as the modulus.");
            }
            return std::fmod(first, second);
        default:
            throw std::invalid_argument("Unknown operator.");
    }
}

void run() {
    std::cout << "\n========== CALCULATOR ==========\n";

    const double first = InputUtils::getDouble("First number: ");
    const char operation =
        InputUtils::getOperator("Operation (+ - * / %): ");
    const double second = InputUtils::getDouble("Second number: ");

    try {
        const double result = calculate(first, second, operation);

        std::cout << std::fixed << std::setprecision(4)
                  << "Result: " << result << '\n';
    } catch (const std::exception& error) {
        std::cout << "[ERROR] " << error.what() << '\n';
    }
}

}
