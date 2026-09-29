#include "PrimeAnalyzer.h"
#include "InputUtils.h"

#include <iostream>
#include <sstream>

namespace PrimeAnalyzer {

bool isPrime(long long number) {
    if (number < 2) {
        return false;
    }

    if (number % 2 == 0) {
        return number == 2;
    }

    // "divisor <= number / divisor" avoids overflowing divisor * divisor.
    for (long long divisor = 3; divisor <= number / divisor; divisor += 2) {
        if (number % divisor == 0) {
            return false;
        }
    }

    return true;
}

std::string primeFactorization(long long number) {
    if (number < 2) {
        return "No prime factorization.";
    }

    std::ostringstream result;
    bool firstFactor = true;

    for (long long factor = 2; factor <= number / factor; ++factor) {
        int exponent = 0;

        while (number % factor == 0) {
            number /= factor;
            ++exponent;
        }

        if (exponent > 0) {
            if (!firstFactor) {
                result << " x ";
            }

            result << factor;

            if (exponent > 1) {
                result << '^' << exponent;
            }

            firstFactor = false;
        }
    }

    // Whatever is left over is a single prime bigger than sqrt(original).
    if (number > 1) {
        if (!firstFactor) {
            result << " x ";
        }

        result << number;
    }

    return result.str();
}

long long nextPrime(long long number) {
    long long candidate = (number < 2) ? 2 : number + 1;

    while (!isPrime(candidate)) {
        ++candidate;
    }

    return candidate;
}

void run() {
    std::cout << "\n============ PRIME ANALYZER ============\n";

    const int number =
        InputUtils::getInt("Enter an integer (1-1000000000): ",
                           1, 1000000000);

    const bool prime = isPrime(number);

    std::cout << "\nNumber: " << number << '\n';
    std::cout << "Prime: " << (prime ? "Yes" : "No") << '\n';

    if (!prime) {
        std::cout << "Factorization: " << primeFactorization(number) << '\n';
    }

    const long long next = nextPrime(number);

    std::cout << "Next prime: " << next << '\n';
    std::cout << "Prime gap: " << next - number << '\n';
}

}
