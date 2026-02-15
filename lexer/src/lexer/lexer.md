# Lexer Module

## Purpose
Scans a Rust source string character by character and produces a stream of `Token` values.

## Public API

### `class Lexer`
```cpp
class Lexer {
public:
    explicit Lexer(const std::string& source);
    Token nextToken();
    std::vector<Token> tokenize();
};
```

### `Lexer(const std::string& source)`
Constructor. Stores the source string. Initializes position to 0, line to 1.

### `Token nextToken()`
Returns the next token from the source. Advances internal position.
- Skips whitespace and comments before reading a token
- Returns `Token{EOF_TOKEN, "", line}` when source is exhausted
- Returns `Token{ILLEGAL, "<char>", line}` for unrecognized characters

### `std::vector<Token> tokenize()`
Convenience method. Calls `nextToken()` repeatedly until `EOF_TOKEN`. Returns all tokens (including the EOF token).

## Internal Helpers (private)
- `peekChar()` — returns current char without advancing
- `advance()` — consumes current char and returns it
- `skipWhitespace()` — skips spaces, tabs, newlines (increments line on `\n`)
- `skipComments()` — skips `//` line comments and `/* */` block comments
- `readIdentifier()` — reads `[a-zA-Z_][a-zA-Z0-9_]*`
- `readNumber()` — reads `[0-9]+`
- `readString()` — reads `"..."`, handles unterminated string as ILLEGAL

## Constraints / Edge Cases
- `==` must be tokenized as one `EQ` token, not two `ASSIGN` tokens
- `!=` must be tokenized as one `NEQ` token
- `<=` and `>=` must be tokenized as `LTE` and `GTE` respectively
- Multi-char operators: peek ahead after `=`, `!`, `<`, `>` to check for `=`
- Whitespace and comments are skipped, never emitted as tokens
- Line tracking: increment line counter on every `\n`
- Unterminated strings (EOF before closing `"`) produce an `ILLEGAL` token
