# Implement Command

Step-by-step workflow the AI follows when implementing a module:

1. Read `docs/architecture.md` — understand overall system design
2. Read `src/<module>/<module>.md` — understand this module's API, data structures, and constraints
3. Write failing tests in `src/<module>/<module>_test.cc` based on the documented API
4. Write stub code in `src/<module>/<module>.h` and `src/<module>/<module>.cpp`
5. Run `cmake --build build` — verify tests compile
6. Run `cd build && ctest` — verify tests FAIL (red phase)
7. Implement the actual logic to make tests pass
8. Run `cd build && ctest` — verify tests PASS (green phase)
9. Update the module's `.md` if the API changed during implementation
