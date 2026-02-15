# Rust Lexer (CS294 Assignment 1)

A lexer for basic Rust syntax, written in C++. Takes a Rust source file as input and produces a stream of tokens.

## Build & Test
```bash
# Build
cmake -B build && cmake --build build

# Run tests
cd build && ctest

# Run on a file
./build/rustc input.rs
```

## Tech Stack
- **Language:** C++17
- **Build System:** CMake
- **Test Framework:** GoogleTest
- **Binary Name:** rustc

## Development Standard (SDD + DDD + TDD)
1. Update docs in `src/<module>/<module>.md` BEFORE writing code
2. Write stubs with correct signatures
3. Write test cases that compile but fail
4. Implement code to make tests pass
5. Run tests to verify

## Documentation Standard (DDD)
- Each module has `src/<module>/<module>.md`
- Document: purpose, public API, data structures, constraints, edge cases
- System architecture lives in `docs/architecture.md`

## Modules
- `src/token/` — Token type enum and Token struct
- `src/lexer/` — Lexer class that converts source text to tokens
- `src/main/` — CLI driver that reads a file and prints tokens
