# Token Module

## Purpose
Defines the vocabulary of the lexer — what kinds of tokens exist and how they are represented.

## Public API

### `enum class TokenType`
All possible token types:
- **Keywords:** `FN`, `LET`, `MUT`, `IF`, `ELSE`, `WHILE`, `RETURN`
- **Literals:** `IDENT`, `NUMBER`, `STRING`
- **Operators:** `PLUS`, `MINUS`, `STAR`, `SLASH`, `ASSIGN`, `EQ`, `NEQ`, `LT`, `GT`, `LTE`, `GTE`
- **Punctuation:** `LPAREN`, `RPAREN`, `LBRACE`, `RBRACE`, `SEMICOLON`, `COLON`, `COMMA`
- **Special:** `EOF_TOKEN`, `ILLEGAL`

### `struct Token`
```cpp
struct Token {
    TokenType type;
    std::string lexeme;
    int line;
};
```

### `std::string tokenTypeToString(TokenType type)`
Returns a human-readable string for a token type (e.g., `TokenType::FN` → `"FN"`).

### `TokenType lookupKeyword(const std::string& ident)`
Given an identifier string, returns the keyword `TokenType` if it matches a keyword, otherwise returns `TokenType::IDENT`.

## Data Structures
- `TokenType` — enum class, one entry per token kind
- `Token` — struct with type, lexeme, and line number

## Constraints / Edge Cases
- `fn_name` should be looked up and return `IDENT`, not `FN`
- Only the exact keyword strings map to keyword types
- `lookupKeyword` must be case-sensitive (Rust is case-sensitive)
