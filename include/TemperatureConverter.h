#pragma once

namespace TemperatureConverter {

enum class Unit {
    Celsius = 1,
    Fahrenheit,
    Kelvin
};

bool isValidTemperature(double value, Unit unit);
double convert(double value, Unit from, Unit to);
void run();

}
