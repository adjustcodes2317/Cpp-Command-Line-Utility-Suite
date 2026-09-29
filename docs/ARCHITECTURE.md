# Project Structure

```text
main.cpp
   |
   v
  App  (menu table)
   |
   +-- Calculator
   +-- TemperatureConverter
   +-- TextAnalyzer
   +-- PrimeAnalyzer
   +-- StatisticsAnalyzer
   |
   +-- InputUtils  (used by every utility)
```

## Pieces

- **`main.cpp`** only creates an `App` and runs it.
- **`App`** owns the menu. The menu is a table of `{name, run function}`, and
  both the printed list and the valid input range come from that table.
- **`InputUtils`** is the only place that reads from `std::cin`. Every prompt
  loops until the input is valid. If input ends (Ctrl+D or piped input), it
  throws `InputClosed`, and `App` catches it and exits cleanly.
- **Utilities** each get a namespace with the same shape: pure functions that
  do the work (`convert`, `calculate`, `analyze`, `isPrime`, ...) and a
  `run()` that handles the prompts and printing.

## Why logic and `run()` are separate

Anything that touches the keyboard is hard to test. Keeping the maths in
plain functions means the tests can call them directly, and only `run()` is
left untested.

## Adding another utility

1. Add a header in `include/` with a namespace containing `run()`.
2. Add the implementation in `src/`.
3. Add the `.cpp` to `utility_core` in `CMakeLists.txt`.
4. Add one line to the `MENU` table in `App.cpp`.
5. Add tests for the logic part in `tests/test_main.cpp`.

## Trade-offs

- Utilities are namespaces of free functions rather than classes, because none
  of them keeps any state between calls.
- There is no plugin system or common base class. With five small tools it
  would be more code than it saves.
