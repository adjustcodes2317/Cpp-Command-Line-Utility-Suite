cmake_minimum_required(VERSION 3.20)

project(CppUtilitySuite VERSION 2.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    set(PROJECT_WARNINGS /W4 /permissive-)
else()
    set(PROJECT_WARNINGS -Wall -Wextra -Wpedantic)
endif()

# Everything except main() and the menu lives in one library,
# so the program and the tests build the same code once.
add_library(utility_core STATIC
    src/InputUtils.cpp
    src/Calculator.cpp
    src/TemperatureConverter.cpp
    src/TextAnalyzer.cpp
    src/PrimeAnalyzer.cpp
    src/StatisticsAnalyzer.cpp
)
target_include_directories(utility_core PUBLIC include)
target_compile_options(utility_core PRIVATE ${PROJECT_WARNINGS})

add_executable(cpp_utility_suite src/main.cpp src/App.cpp)
target_link_libraries(cpp_utility_suite PRIVATE utility_core)
target_compile_options(cpp_utility_suite PRIVATE ${PROJECT_WARNINGS})
target_compile_definitions(cpp_utility_suite PRIVATE
    APP_VERSION=\"${PROJECT_VERSION}\")

enable_testing()

add_executable(cpp_utility_tests tests/test_main.cpp)
target_link_libraries(cpp_utility_tests PRIVATE utility_core)
target_compile_options(cpp_utility_tests PRIVATE ${PROJECT_WARNINGS})

add_test(NAME UtilitySuiteTests COMMAND cpp_utility_tests)
