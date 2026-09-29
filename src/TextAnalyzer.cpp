#include "TextAnalyzer.h"
#include "InputUtils.h"

#include <algorithm>
#include <cctype>
#include <iomanip>
#include <iostream>

namespace TextAnalyzer {

TextStats analyze(const std::string& text) {
    TextStats stats{};
    bool insideWord = false;

    for (unsigned char value : text) {
        ++stats.charactersWithSpaces;

        if (std::isspace(value)) {
            insideWord = false;
            continue;
        }

        ++stats.charactersWithoutSpaces;

        if (std::isdigit(value)) {
            ++stats.digits;
        }

        const int lower = std::tolower(value);

        if (lower == 'a' || lower == 'e' || lower == 'i' ||
            lower == 'o' || lower == 'u') {
            ++stats.vowels;
        }

        if (!insideWord) {
            ++stats.words;
            insideWord = true;
        }
    }

    if (!text.empty()) {
        stats.lines = 1 + static_cast<std::size_t>(
            std::count(text.begin(), text.end(), '\n'));
    }

    if (stats.words > 0) {
        stats.averageCharactersPerWord =
            static_cast<double>(stats.charactersWithoutSpaces) /
            static_cast<double>(stats.words);
    }

    return stats;
}

void run() {
    std::cout << "\n============ TEXT ANALYZER ============\n";
    std::cout << "Enter text. A blank line ends the input.\n\n";

    std::string text;
    bool firstLine = true;

    while (true) {
        const std::string line = InputUtils::getLine("> ");

        if (line.empty()) {
            break;
        }

        if (!firstLine) {
            text += '\n';
        }

        text += line;
        firstLine = false;
    }

    const TextStats stats = analyze(text);

    std::cout << "\nWords: " << stats.words << '\n';
    std::cout << "Characters: " << stats.charactersWithSpaces << '\n';
    std::cout << "Characters (no spaces): "
              << stats.charactersWithoutSpaces << '\n';
    std::cout << "Lines: " << stats.lines << '\n';
    std::cout << "Vowels: " << stats.vowels << '\n';
    std::cout << "Digits: " << stats.digits << '\n';

    std::cout << std::fixed << std::setprecision(2)
              << "Average characters/word: "
              << stats.averageCharactersPerWord << '\n';
}

}
