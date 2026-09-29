#include "StatisticsAnalyzer.h"
#include "InputUtils.h"

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <stdexcept>
#include <string>

namespace StatisticsAnalyzer {

Statistics calculate(std::vector<double> values) {
    if (values.empty()) {
        throw std::invalid_argument("No values were provided.");
    }

    Statistics stats{};
    const double count = static_cast<double>(values.size());

    stats.sum = std::accumulate(values.begin(), values.end(), 0.0);
    stats.mean = stats.sum / count;

    std::sort(values.begin(), values.end());

    stats.minimum = values.front();
    stats.maximum = values.back();
    stats.range = stats.maximum - stats.minimum;

    const std::size_t middle = values.size() / 2;

    if (values.size() % 2 == 0) {
        stats.median = (values[middle - 1] + values[middle]) / 2.0;
    } else {
        stats.median = values[middle];
    }

    double squaredDifferences = 0.0;

    for (double value : values) {
        const double difference = value - stats.mean;
        squaredDifferences += difference * difference;
    }

    stats.standardDeviation = std::sqrt(squaredDifferences / count);

    if (values.size() > 1) {
        stats.sampleStandardDeviation =
            std::sqrt(squaredDifferences / (count - 1.0));
    }

    return stats;
}

void run() {
    std::cout << "\n========= STATISTICS ANALYZER =========\n";

    const int count = InputUtils::getInt("How many numbers? ", 1, 1000);

    std::vector<double> values;
    values.reserve(static_cast<std::size_t>(count));

    for (int i = 0; i < count; ++i) {
        values.push_back(
            InputUtils::getDouble("Value " + std::to_string(i + 1) + ": "));
    }

    const Statistics stats = calculate(values);

    std::cout << std::fixed << std::setprecision(3) << std::left;

    auto row = [](const char* label, double value) {
        std::cout << std::setw(32) << label << value << '\n';
    };

    std::cout << '\n';
    row("Sum:", stats.sum);
    row("Mean:", stats.mean);
    row("Median:", stats.median);
    row("Minimum:", stats.minimum);
    row("Maximum:", stats.maximum);
    row("Range:", stats.range);
    row("Std deviation (population):", stats.standardDeviation);

    if (values.size() > 1) {
        row("Std deviation (sample):", stats.sampleStandardDeviation);
    } else {
        std::cout << std::setw(32) << "Std deviation (sample):"
                  << "n/a (needs 2+ values)\n";
    }
}

}
