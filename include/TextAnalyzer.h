#pragma once

#include <cstddef>
#include <string>

namespace TextAnalyzer {

struct TextStats {
    std::size_t charactersWithSpaces{};
    std::size_t charactersWithoutSpaces{};
    std::size_t words{};
    std::size_t lines{};
    std::size_t vowels{};
    std::size_t digits{};
    double averageCharactersPerWord{};
};

TextStats analyze(const std::string& text);
void run();

}
