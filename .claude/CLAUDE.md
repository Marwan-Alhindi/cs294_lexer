# Rust Compiler (CS294)

A compiler for basic Rust syntax, written in C++. Implements the full pipeline:
Lexer → Parser → (Semantic Analyzer) → (Code Generator).

## Build & Test
```bash
# Build
cmake -B build && cmake --build build

# Run all tests
cd build && ctest --output-on-failure

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
- `src/ast/` — AST node types (output of parser, input to semantic analyzer)
- `src/parser/` — Recursive descent parser; produces AST from token stream
- `src/semantic/` — Type checking and name resolution (planned)
- `src/codegen/` — IR / code emission (planned)
- `src/main/` — CLI driver
