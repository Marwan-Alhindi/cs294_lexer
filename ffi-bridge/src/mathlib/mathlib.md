# MathLib Module

## Purpose
C++ shared library that exports math functions with C linkage for FFI consumption.

## Public API (exported via `extern "C"`)

### `int add(int a, int b)`
Returns `a + b`.

### `int subtract(int a, int b)`
Returns `a - b`.

### `int multiply(int a, int b)`
Returns `a * b`.

### `double divide(double a, double b)`
Returns `a / b`. Returns `0.0` if `b == 0.0` (no crash, no exception).

### `int factorial(int n)`
Returns `n!` for `n >= 0`. Returns `-1` for negative input.
- `factorial(0)` = 1
- `factorial(5)` = 120

### `int fibonacci(int n)`
Returns the nth Fibonacci number (0-indexed: fib(0)=0, fib(1)=1, fib(2)=1, ...).
Returns `-1` for negative input.

## Build
```bash
# Via CMake (preferred)
cmake -B build && cmake --build build

# Manual (for understanding)
g++ -shared -fPIC -o math_lib.so math_lib.cpp
```

## Constraints / Edge Cases
- All exported functions MUST be inside `extern "C" { ... }`
- Only use C-compatible types in signatures: `int`, `double`, `const char*`
- No exceptions may cross the FFI boundary — handle errors via return values
- Division by zero returns `0.0`, not an exception or crash
- Negative input to factorial/fibonacci returns `-1`
- Compiled with `-fPIC` (Position Independent Code) for shared library
