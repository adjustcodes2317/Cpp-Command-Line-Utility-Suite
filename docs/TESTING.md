# Testing

`tests/test_main.cpp` is a small standalone runner. It counts checks, prints
the file and line of any that fail, and returns a non-zero exit code so
`ctest` (and CI) notice.

It uses its own `CHECK` macros instead of `assert`. `assert` is removed when
`NDEBUG` is defined, which is the default for Release builds, so a test built
that way would pass while checking nothing.

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

Also try `-DCMAKE_BUILD_TYPE=Release` to confirm the tests still bite.

## What is covered

- Calculator: all operators, negative modulus, divide/modulus by zero, unknown operator
- Temperature: every unit pair, exact absolute-zero boundaries, round trip
- Text: empty input, repeated spaces, multi-line, uppercase vowels, average word length
- Primes: 0, 1, negatives, squares of primes, values near 10^9, factorization, next prime
- Statistics: odd and even counts, unsorted and negative data, one value, empty input,
  both standard deviations

## Not covered

The `run()` functions (prompts and printing) are only checked by hand:

- letters instead of numbers, `nan`, `inf`
- an invalid menu option
- dividing by zero
- a temperature below absolute zero
- empty text
- Ctrl+D at the menu and in the middle of a tool
- small and large primes
