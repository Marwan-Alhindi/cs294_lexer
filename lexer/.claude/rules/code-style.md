# Code Style

## Naming Conventions
- Classes: `PascalCase` (e.g., `Lexer`, `Token`)
- Functions/methods: `camelCase` (e.g., `nextToken`, `peekChar`)
- Constants/enum values: `UPPER_SNAKE_CASE` (e.g., `FN`, `LET`, `PLUS`)
- Variables: `camelCase` (e.g., `currentChar`, `tokenStart`)
- Files: `snake_case` (e.g., `token.h`, `lexer.cpp`)

## Patterns to Use
- Use `std::string_view` for read-only string references
- Use `enum class` for token types (not plain enums)
- Use smart pointers where ownership is needed
- Return by value where possible (rely on copy elision)
- Use `const` and `constexpr` where applicable

## Patterns to Avoid
- No raw `new`/`delete`
- No `using namespace std;` in headers
- No exceptions for control flow — use return values or `std::optional`
- No global mutable state

## Formatting
- 4-space indentation
- Opening brace on same line
- Max line length: 100 characters
