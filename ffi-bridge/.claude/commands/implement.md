# Implement Command

Step-by-step workflow the AI follows when implementing a module:

1. Read `docs/architecture.md` — understand overall system design
2. Read `src/<module>/<module>.md` — understand this module's API and constraints
3. Write failing tests:
   - C++ tests in `src/mathlib/mathlib_test.cc`
   - Python tests in `tests/test_bindings.py`
4. Write stub code
5. Run `cmake --build build` — verify C++ tests compile
6. Run `cd build && ctest` — verify C++ tests FAIL (red)
7. Implement the actual logic
8. Run `cd build && ctest` — verify C++ tests PASS (green)
9. Run `pytest tests/` — verify Python tests PASS (green)
10. Update the module's `.md` if the API changed
