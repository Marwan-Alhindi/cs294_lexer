# FFI Bridge (CS294 Assignment 2)

A C++ shared library called from Python via ctypes. Demonstrates Foreign Function Interface (FFI) — getting the performance of C++ with the ease of Python.

## Build & Test
```bash
# Build shared library
cmake -B build && cmake --build build

# Run C++ tests
cd build && ctest

# Run Python tests
pytest tests/

# Quick demo
python3 src/bindings/demo.py
```

## Tech Stack
- **C++ Library:** C++17, compiled to `.so` (macOS/Linux) / `.dll` (Windows)
- **Build System:** CMake
- **C++ Tests:** GoogleTest
- **Python Wrapper:** ctypes (standard library)
- **Python Tests:** pytest
- **FFI Convention:** `extern "C"` to avoid C++ name mangling

## Development Standard (SDD + DDD + TDD)
1. Update docs in `src/<module>/<module>.md` BEFORE writing code
2. Write stubs with correct signatures
3. Write test cases that compile but fail
4. Implement code to make tests pass
5. Run tests to verify

## Documentation Standard (DDD)
- Each module has `src/<module>/<module>.md`
- Document: purpose, public API, data structures, constraints
- System architecture lives in `docs/architecture.md`

## Modules
- `src/mathlib/` — C++ shared library with `extern "C"` functions
- `src/bindings/` — Python ctypes wrapper and demo script
