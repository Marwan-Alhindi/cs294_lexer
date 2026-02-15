# Main Module

## Purpose
CLI entry point. Reads a Rust source file and prints each token produced by the lexer.

## Public API

### `int main(int argc, char* argv[])`
- Expects exactly one argument: the path to a `.rs` file
- Reads the file contents into a string
- Creates a `Lexer` instance with the source
- Calls `tokenize()` and prints each token in the format: `<TYPE> <lexeme>`
- Returns 0 on success, 1 on error (no file argument, file not found)

## Output Format
```
FN fn
IDENT main
LPAREN (
RPAREN )
LBRACE {
...
```

## Constraints
- Print one token per line
- Print the token type name followed by a space and the lexeme
- Do not print the EOF token
