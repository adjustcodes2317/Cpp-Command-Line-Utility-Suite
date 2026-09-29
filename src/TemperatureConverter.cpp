#include "TemperatureConverter.h"
#include "InputUtils.h"

#include <iomanip>
#include <iostream>
#include <stdexcept>

namespace {

constexpr double ABSOLUTE_ZERO_C = -273.15;
constexpr double ABSOLUTE_ZERO_F = -459.67;

double toCelsius(double value, TemperatureConverter::Unit unit) {
    switch (unit) {
        case TemperatureConverter::Unit::Celsius:
            return value;
        case TemperatureConverter::Unit::Fahrenheit:
            return (value - 32.0) * 5.0 / 9.0;
        case TemperatureConverter::Unit::Kelvin:
            return value - 273.15;
    }

    throw std::invalid_argument("Unknown temperature unit.");
}

double fromCelsius(double value, TemperatureConverter::Unit unit) {
    switch (unit) {
        case TemperatureConverter::Unit::Celsius:
            return value;
        case TemperatureConverter::Unit::Fahrenheit:
            return value * 9.0 / 5.0 + 32.0;
        case TemperatureConverter::Unit::Kelvin:
            return value + 273.15;
    }

    throw std::invalid_argument("Unknown temperature unit.");
}

}

namespace TemperatureConverter {

bool isValidTemperature(double value, Unit unit) {
    switch (unit) {
        case Unit::Celsius:
            return value >= ABSOLUTE_ZERO_C;
        case Unit::Fahrenheit:
            return value >= ABSOLUTE_ZERO_F;
        case Unit::Kelvin:
            return value >= 0.0;
    }

    return false;
}

double convert(double value, Unit from, Unit to) {
    if (!isValidTemperature(value, from)) {
        throw std::domain_error("Temperature is below absolute zero.");
    }

    return fromCelsius(toCelsius(value, from), to);
}

void run() {
    std::cout << "\n======= TEMPERATURE CONVERTER =======\n";
    std::cout << "1. Celsius\n";
    std::cout << "2. Fahrenheit\n";
    std::cout << "3. Kelvin\n";

    const int fromChoice = InputUtils::getInt("From: ", 1, 3);
    const double value = InputUtils::getDouble("Temperature: ");
    const int toChoice = InputUtils::getInt("To: ", 1, 3);

    const Unit from = static_cast<Unit>(fromChoice);
    const Unit to = static_cast<Unit>(toChoice);

    try {
        const double result = convert(value, from, to);

        std::cout << std::fixed << std::setprecision(2)
                  << "Converted value: " << result << '\n';
    } catch (const std::exception& error) {
        std::cout << "[ERROR] " << error.what() << '\n';
    }
}

}
