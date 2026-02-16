# Architecture

## What the System Is
A lexer (tokenizer) for basic Rust syntax. It reads a `.rs` source file and produces a stream of typed tokens.

## Pipeline
```
Rust source file (.rs)
    |
    v
[main] — reads file into string
    |
    v
[lexer] — scans characters, produces tokens
    |
    v
[token] — Token struct + TokenType enum
    |
    v
stdout — prints each token (type + value)
```

## Modules

### `src/token/`
- Defines `TokenType` enum class (all keyword, operator, punctuation, literal types)
- Defines `Token` struct (type, lexeme, line number)
- Provides `tokenTypeToString()` for display

### `src/lexer/`
- `Lexer` class takes a `std::string` of source code
- Exposes `nextToken()` which returns the next `Token`
- Exposes `tokenize()` which returns all tokens as a `std::vector<Token>`
- Handles: keywords, identifiers, numbers, strings, operators, punctuation
- Skips: whitespace, single-line comments (`//`), block comments (`/* */`)

### `src/main/`
- CLI entry point
- Reads a `.rs` file from argv
- Calls `Lexer::tokenize()`
- Prints each token to stdout

## Data Flow
```
main.cpp: reads file → string
         ↓
Lexer(source): stores source string, position = 0
         ↓
nextToken(): peekChar → classify → consume → return Token
         ↓
Token { type: TokenType, lexeme: string, line: int }
```

## Supported Token Types

| Category    | Tokens                                                  |
|-------------|--------------------------------------------------------|
| Keywords    | fn, let, mut, if, else, while, return                  |
| Identifiers | starts with letter or `_`, then alphanumeric or `_`    |
| Numbers     | integer literals (sequence of digits)                   |
| Strings     | `"..."` (double-quoted)                                |
| Operators   | +, -, *, /, =, ==, !=, <, >, <=, >=                   |
| Punctuation | (, ), {, }, ;, :, ,                                    |
| Special     | EOF, ILLEGAL (for unrecognized characters)             |
