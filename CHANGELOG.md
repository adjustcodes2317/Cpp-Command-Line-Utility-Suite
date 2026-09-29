# Changelog

## v2.1 - 2026-09

### Fixed
- The program looped forever, printing errors, when input ended (Ctrl+D or
  piped input). It now exits cleanly.
- `nextPrime` returned a wrong value for negative input (`-5` gave `-4`).
- The tests used `assert`, which does nothing in Release builds, so they
  passed without checking anything. They now use their own check macro.
- Removed an unused variable that triggered a compiler warning.

### Changed
- Every utility is now a namespace with a `run()` function, and the menu is
  built from one table in `App.cpp`.
- The app and the tests share one static library in CMake.
- The version shown in the banner comes from `CMakeLists.txt`.
- Standard deviation is now labelled as population, and the sample version was
  added next to it.
- `getDouble` rejects `nan` and `inf`.
- CMake minimum raised to 3.20, which `ctest --test-dir` needs.

### Added
- Tests for the calculator, plus many more edge cases (81 checks in total).
- GitHub Actions workflow that builds and tests on Linux, Windows and macOS.

## v2.0 - 2026

- Split the original single-file project into headers and source files.
- Added a statistics utility.
- Added reusable input validation.
- Added a small test suite.
- Added CMake support.
- Cleaned up the menu and output.

## v1.0

- Original course capstone implementation.
- Calculator
- Temperature converter
- Word and character counter
- Prime number checker
