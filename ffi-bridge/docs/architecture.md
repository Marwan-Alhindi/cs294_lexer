# Architecture

## What the System Is
A C++ shared library exposing math functions via `extern "C"`, called from Python using the `ctypes` standard library. Demonstrates FFI (Foreign Function Interface).

## Pipeline
```
C++ source (.cpp)
    |
    v
[g++ -shared -fPIC] → shared library (.so / .dylib)
    |
    v
[Python ctypes.CDLL] → loads the .so at runtime
    |
    v
[MathLib wrapper class] → clean Python API
    |
    v
Application code / demo.py
```

## Modules

### `src/mathlib/`
C++ shared library. Exports functions with `extern "C"` linkage.

**Exported functions:**
- `int add(int a, int b)` — addition
- `int subtract(int a, int b)` — subtraction
- `int multiply(int a, int b)` — multiplication
- `double divide(double a, double b)` — division (returns 0.0 on divide-by-zero)
- `int factorial(int n)` — factorial (returns -1 for negative input)
- `int fibonacci(int n)` — nth fibonacci number (returns -1 for negative input)

### `src/bindings/`
Python ctypes wrapper that loads the shared library and provides a clean `MathLib` class.

- `MathLib` class — loads `.so`, sets `argtypes`/`restype`, exposes Python methods
- `demo.py` — standalone script that demonstrates all functions

## Data Flow
```
Python: MathLib("./build/libmathlib.so")
    ↓
ctypes.CDLL loads shared object into process
    ↓
lib.add.argtypes = [c_int, c_int]
lib.add.restype = c_int
    ↓
result = lib.add(3, 5)  →  calls C function  →  returns 8
```

## Key Concept: extern "C"
C++ name-mangles functions (e.g., `add` becomes `_Z3addii`). `extern "C"` disables this, so ctypes can find functions by their plain name.
