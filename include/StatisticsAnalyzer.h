#pragma once

#include <vector>

namespace StatisticsAnalyzer {

struct Statistics {
    double sum{};
    double mean{};
    double median{};
    double minimum{};
    double maximum{};
    double range{};
    double standardDeviation{};        // population (divides by n)
    double sampleStandardDeviation{};  // sample (divides by n - 1), 0 when n == 1
};

// Throws std::invalid_argument if values is empty.
Statistics calculate(std::vector<double> values);
void run();

}
