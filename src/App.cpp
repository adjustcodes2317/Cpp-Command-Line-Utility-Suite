#include "App.h"

#include "Calculator.h"
#include "InputUtils.h"
#include "PrimeAnalyzer.h"
#include "StatisticsAnalyzer.h"
#include "TemperatureConverter.h"
#include "TextAnalyzer.h"

#include <iostream>
#include <iterator>

#ifndef APP_VERSION
#define APP_VERSION "dev"
#endif

namespace {

struct MenuItem {
    const char* name;
    void (*run)();
};

// To add a utility, add one line here (plus its files in CMakeLists.txt).
// The menu text and the valid input range are both derived from this table.
const MenuItem MENU[] = {
    {"Calculator",            Calculator::run},
    {"Temperature Converter", TemperatureConverter::run},
    {"Text Analyzer",         TextAnalyzer::run},
    {"Prime Analyzer",        PrimeAnalyzer::run},
    {"Statistics Analyzer",   StatisticsAnalyzer::run},
};

constexpr int MENU_SIZE = static_cast<int>(std::size(MENU));

}

void App::showWelcome() const {
    std::cout << "\n============================================\n";
    std::cout << "        C++ COMMAND-LINE UTILITY SUITE\n";
    std::cout << "                   v" << APP_VERSION << "\n";
    std::cout << "============================================\n";
}

void App::showMenu() const {
    std::cout << '\n';

    for (int i = 0; i < MENU_SIZE; ++i) {
        std::cout << (i + 1) << ". " << MENU[i].name << '\n';
    }

    std::cout << "0. Exit\n\n";
}

void App::run() const {
    showWelcome();

    try {
        while (true) {
            showMenu();

            const int choice =
                InputUtils::getInt("Choose an option: ", 0, MENU_SIZE);

            if (choice == 0) {
                break;
            }

            MENU[choice - 1].run();
            InputUtils::waitForEnter();
        }
    } catch (const InputUtils::InputClosed&) {
        std::cout << '\n';  // stdin ended (Ctrl+D or piped input): exit cleanly
    }

    std::cout << "\nThanks for using the utility suite.\n";
}
