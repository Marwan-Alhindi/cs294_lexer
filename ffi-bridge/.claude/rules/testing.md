# Testing Rules

## C++ Tests
- Framework: GoogleTest (gtest)
- File naming: `src/mathlib/mathlib_test.cc`
- Test every exported function directly (linked statically for testing)
- Test edge cases: zero, negative numbers, large values

## Python Tests
- Framework: pytest
- File naming: `tests/test_bindings.py`
- Test the ctypes wrapper loads the `.so` correctly
- Test each function returns correct results through the FFI boundary
- Test type conversions (int, double, string)

## TDD Workflow (tests first)
1. Read the module's `.md` doc
2. Write test cases based on the documented API
3. Verify tests compile/run but FAIL (red)
4. Write implementation code
5. Verify tests PASS (green)

## What to Test
- Every exported C function
- Every Python wrapper method
- Correct type marshalling across the FFI boundary
- Edge cases: 0, negative, overflow
- Library loading (correct path resolution)
