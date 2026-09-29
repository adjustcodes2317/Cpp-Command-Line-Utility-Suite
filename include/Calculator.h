#pragma once

namespace Calculator {

// Throws std::domain_error for division/modulus by zero and
// std::invalid_argument for an unknown operator.
double calculate(double first, double second, char operation);
void run();

}
