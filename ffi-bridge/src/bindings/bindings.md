# Bindings Module

## Purpose
Python wrapper around the C++ shared library using `ctypes`. Provides a clean, Pythonic API.

## Public API

### `class MathLib`
```python
class MathLib:
    def __init__(self, lib_path: str)
    def add(self, a: int, b: int) -> int
    def subtract(self, a: int, b: int) -> int
    def multiply(self, a: int, b: int) -> int
    def divide(self, a: float, b: float) -> float
    def factorial(self, n: int) -> int
    def fibonacci(self, n: int) -> int
```

### `__init__(self, lib_path: str)`
Loads the shared library via `ctypes.CDLL(lib_path)`.
Sets `argtypes` and `restype` for every exported function.

### Methods
Each method calls the corresponding C function and returns the result.
Type conversion is handled by ctypes automatically.

## Constraints / Edge Cases
- `lib_path` must point to a valid `.so` / `.dylib` file
- Always set `argtypes` and `restype` — without these, ctypes assumes `int` for everything
- `divide` uses `c_double` for both args and return type
- If the library file doesn't exist, `__init__` will raise `OSError`
