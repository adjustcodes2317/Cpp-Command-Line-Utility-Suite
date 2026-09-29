# C++ Command-Line Utility Suite

A menu-driven terminal program with five small tools. It started as my
single-file C++ course capstone. I later split it into modules, added tests
and CMake, and tightened up how it handles bad input.

<!-- ADD ONE REAL SENTENCE HERE: something that actually tripped you up while
     building this (a bug, a design choice you changed your mind on). Delete
     this comment when done. -->

## The tools

| # | Tool | What it does |
|---|------|--------------|
| 1 | Calculator | `+ - * / %` on two numbers, with divide-by-zero handled |
| 2 | Temperature Converter | Celsius, Fahrenheit and Kelvin, rejects anything below absolute zero |
| 3 | Text Analyzer | words, characters, lines, vowels, digits, average word length |
| 4 | Prime Analyzer | prime check, prime factorization, next prime and the gap to it |
| 5 | Statistics Analyzer | sum, mean, median, min, max, range, population and sample standard deviation |

Example (Prime Analyzer, input `360`):

```text
Number: 360
Prime: No
Factorization: 2^3 x 3^2 x 5
Next prime: 367
Prime gap: 7
```

## Build and run

You need a C++17 compiler and CMake 3.20 or newer.

```bash
cmake -S . -B build
cmake --build build
./build/cpp_utility_suite
```

With Visual Studio or another multi-config generator the binary ends up in a
subfolder, e.g. `build/Debug/cpp_utility_suite.exe`, and you need
`--config Debug` (or `Release`) on the build and test commands.

## Tests

```bash
ctest --test-dir build --output-on-failure
```

There are 81 checks covering all five utilities, including the edge cases
(empty input, absolute zero, even-length data, primes near 10^9). They use a
small check macro instead of `assert`, so they still run in Release builds.
More in [docs/TESTING.md](docs/TESTING.md).

## Project layout

```text
Cpp-Command-Line-Utility-Suite/
├── include/        headers
├── src/            implementations, plus main.cpp and the menu (App.cpp)
├── tests/          test runner
├── docs/           architecture and testing notes
├── .github/        CI workflow
├── CMakeLists.txt
├── CHANGELOG.md
└── LICENSE
```

## Known limitations

- The Text Analyzer stops reading at the first blank line, so you can't paste
  text that contains blank lines. Vowels means `a e i o u` only.
- The Prime Analyzer accepts 1 to 1,000,000,000 and uses plain trial
  division.
- `%` uses `fmod`, so the result takes the sign of the first number
  (`-7 % 3` gives `-1`).
- The calculator prints four decimal places, so a very small result can show
  as `-0.0000`.
- The Statistics Analyzer takes up to 1000 values, typed one at a time.

## Ideas for later

- read the statistics input from a file
- a date/time utility
- a simple file analyzer
- tests that feed scripted input to the interactive parts
