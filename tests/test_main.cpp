// Tiny test runner. It deliberately does not use assert(): assert() is
// compiled out when NDEBUG is defined (Release builds), which would make
// every test "pass" without checking anything.

#include "Calculator.h"
#include "PrimeAnalyzer.h"
#include "StatisticsAnalyzer.h"
#include "TemperatureConverter.h"
#include "TextAnalyzer.h"

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>

namespace {

int checks = 0;
int failures = 0;

}

#define CHECK(condition)                                                  \
    do {                                                                  \
        ++checks;                                                         \
        if (!(condition)) {                                               \
            ++failures;                                                   \
            std::cerr << __FILE__ << ':' << __LINE__                      \
                      << "  FAILED: " #condition "\n";                    \
        }                                                                 \
    } while (false)

#define CHECK_NEAR(actual, expected) \
    CHECK(std::abs((actual) - (expected)) < 1e-9)

#define CHECK_THROWS(expression, ExceptionType)                           \
    do {                                                                  \
        bool caught = false;                                              \
        try {                                                             \
            (void)(expression);                                           \
        } catch (const ExceptionType&) {                                  \
            caught = true;                                                \
        } catch (...) {                                                   \
        }                                                                 \
        CHECK(caught);                                                    \
    } while (false)

void testCalculator() {
    CHECK_NEAR(Calculator::calculate(2, 3, '+'), 5.0);
    CHECK_NEAR(Calculator::calculate(7, 10, '-'), -3.0);
    CHECK_NEAR(Calculator::calculate(4, 2.5, '*'), 10.0);
    CHECK_NEAR(Calculator::calculate(9, 3, '/'), 3.0);
    CHECK_NEAR(Calculator::calculate(7, 3, '%'), 1.0);
    CHECK_NEAR(Calculator::calculate(-7, 3, '%'), -1.0);  // sign follows the first number

    CHECK_THROWS(Calculator::calculate(5, 0, '/'), std::domain_error);
    CHECK_THROWS(Calculator::calculate(5, 0, '%'), std::domain_error);
    CHECK_THROWS(Calculator::calculate(5, 1, '^'), std::invalid_argument);
}

void testTemperature() {
    using TemperatureConverter::convert;
    using TemperatureConverter::isValidTemperature;
    using TemperatureConverter::Unit;

    CHECK_NEAR(convert(0.0, Unit::Celsius, Unit::Fahrenheit), 32.0);
    CHECK_NEAR(convert(100.0, Unit::Celsius, Unit::Kelvin), 373.15);
    CHECK_NEAR(convert(32.0, Unit::Fahrenheit, Unit::Celsius), 0.0);
    CHECK_NEAR(convert(212.0, Unit::Fahrenheit, Unit::Celsius), 100.0);
    CHECK_NEAR(convert(0.0, Unit::Kelvin, Unit::Celsius), -273.15);
    CHECK_NEAR(convert(300.0, Unit::Kelvin, Unit::Celsius), 26.85);
    CHECK_NEAR(convert(50.0, Unit::Celsius, Unit::Celsius), 50.0);
    CHECK_NEAR(convert(convert(37.0, Unit::Celsius, Unit::Fahrenheit),
                       Unit::Fahrenheit, Unit::Celsius), 37.0);

    CHECK(isValidTemperature(-273.15, Unit::Celsius));
    CHECK(!isValidTemperature(-273.16, Unit::Celsius));
    CHECK(isValidTemperature(-459.67, Unit::Fahrenheit));
    CHECK(!isValidTemperature(-459.68, Unit::Fahrenheit));
    CHECK(isValidTemperature(0.0, Unit::Kelvin));
    CHECK(!isValidTemperature(-1.0, Unit::Kelvin));

    CHECK_THROWS(convert(-300.0, Unit::Celsius, Unit::Fahrenheit),
                 std::domain_error);
}

void testText() {
    using TextAnalyzer::analyze;

    const auto basic = analyze("Hello 123");
    CHECK(basic.words == 2);
    CHECK(basic.charactersWithSpaces == 9);
    CHECK(basic.charactersWithoutSpaces == 8);
    CHECK(basic.vowels == 2);
    CHECK(basic.digits == 3);
    CHECK(basic.lines == 1);

    const auto empty = analyze("");
    CHECK(empty.words == 0);
    CHECK(empty.charactersWithSpaces == 0);
    CHECK(empty.lines == 0);
    CHECK_NEAR(empty.averageCharactersPerWord, 0.0);

    const auto spaces = analyze("  a   b  ");
    CHECK(spaces.words == 2);

    const auto multiline = analyze("one\ntwo\nthree");
    CHECK(multiline.lines == 3);
    CHECK(multiline.words == 3);

    CHECK(analyze("AEIOU aeiou xyz").vowels == 10);
    CHECK_NEAR(analyze("ab cd").averageCharactersPerWord, 2.0);
}

void testPrime() {
    using namespace PrimeAnalyzer;

    CHECK(!isPrime(-7));
    CHECK(!isPrime(0));
    CHECK(!isPrime(1));
    CHECK(isPrime(2));
    CHECK(isPrime(3));
    CHECK(!isPrime(25));
    CHECK(!isPrime(49));
    CHECK(isPrime(97));
    CHECK(!isPrime(100));
    CHECK(isPrime(999999937));
    CHECK(isPrime(1000000007));

    CHECK(primeFactorization(360) == "2^3 x 3^2 x 5");
    CHECK(primeFactorization(97) == "97");
    CHECK(primeFactorization(1000000000) == "2^9 x 5^9");
    CHECK(primeFactorization(1) == "No prime factorization.");

    CHECK(nextPrime(-5) == 2);
    CHECK(nextPrime(0) == 2);
    CHECK(nextPrime(2) == 3);
    CHECK(nextPrime(10) == 11);
    CHECK(nextPrime(13) == 17);
    CHECK(nextPrime(1000000000) == 1000000007);
}

void testStatistics() {
    using StatisticsAnalyzer::calculate;

    const auto odd = calculate({10.0, 20.0, 30.0, 40.0, 50.0});
    CHECK_NEAR(odd.sum, 150.0);
    CHECK_NEAR(odd.mean, 30.0);
    CHECK_NEAR(odd.median, 30.0);
    CHECK_NEAR(odd.minimum, 10.0);
    CHECK_NEAR(odd.maximum, 50.0);
    CHECK_NEAR(odd.range, 40.0);
    CHECK_NEAR(odd.standardDeviation, std::sqrt(200.0));
    CHECK_NEAR(odd.sampleStandardDeviation, std::sqrt(250.0));

    const auto even = calculate({2.0, 4.0, 4.0, 4.0, 5.0, 5.0, 7.0, 9.0});
    CHECK_NEAR(even.mean, 5.0);
    CHECK_NEAR(even.median, 4.5);
    CHECK_NEAR(even.standardDeviation, 2.0);
    CHECK_NEAR(even.sampleStandardDeviation, std::sqrt(32.0 / 7.0));

    const auto unsorted = calculate({9.0, 1.0, 5.0});
    CHECK_NEAR(unsorted.median, 5.0);
    CHECK_NEAR(unsorted.minimum, 1.0);
    CHECK_NEAR(unsorted.maximum, 9.0);

    const auto negatives = calculate({-5.0, -1.0});
    CHECK_NEAR(negatives.mean, -3.0);
    CHECK_NEAR(negatives.median, -3.0);
    CHECK_NEAR(negatives.range, 4.0);

    const auto single = calculate({7.0});
    CHECK_NEAR(single.standardDeviation, 0.0);
    CHECK_NEAR(single.sampleStandardDeviation, 0.0);

    CHECK_THROWS(calculate({}), std::invalid_argument);
}

int main() {
    testCalculator();
    testTemperature();
    testText();
    testPrime();
    testStatistics();

    if (failures > 0) {
        std::cerr << failures << " of " << checks << " checks failed.\n";
        return 1;
    }

    std::cout << "All " << checks << " checks passed.\n";
    return 0;
}
