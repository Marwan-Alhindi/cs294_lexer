# Parser Module

## Purpose
Consumes tokens from a `Lexer` and produces an AST (`ProgramNode`) via recursive descent.
Errors are collected into a `std::vector<ParseError>` — no exceptions are thrown.

## Grammar

```
program         ::= statement* EOF
statement       ::= fn_decl | let_stmt | return_stmt | while_stmt | if_stmt | expr_stmt | block
fn_decl         ::= FN IDENT LPAREN param_list RPAREN block
param_list      ::= (param (COMMA param)*)?
param           ::= IDENT COLON IDENT
let_stmt        ::= LET MUT? IDENT (COLON IDENT)? ASSIGN expression SEMICOLON
return_stmt     ::= RETURN expression? SEMICOLON
while_stmt      ::= WHILE expression block
if_stmt         ::= IF expression block (ELSE (block | if_stmt))?
expr_stmt       ::= expression SEMICOLON
block           ::= LBRACE statement* RBRACE
expression      ::= assignment
assignment      ::= IDENT ASSIGN assignment | comparison
comparison      ::= additive ((EQ|NEQ|LT|GT|LTE|GTE) additive)*
additive        ::= multiplicative ((PLUS|MINUS) multiplicative)*
multiplicative  ::= unary ((STAR|SLASH) unary)*
unary           ::= MINUS unary | primary
primary         ::= NUMBER | STRING | IDENT (call_args)? | LPAREN expression RPAREN
call_args       ::= LPAREN (expression (COMMA expression)*)? RPAREN
```

## Public API

### `struct ParseError`
```cpp
struct ParseError {
    std::string message;
    int line;
};
```

### `class Parser`
```cpp
class Parser {
public:
    explicit Parser(const std::string& source);
    std::unique_ptr<ProgramNode> parseProgram();
    bool hasErrors() const;
    const std::vector<ParseError>& errors() const;
};
```

### `Parser(const std::string& source)`
Constructs the parser. Owns a `Lexer` by value. Primes `current` and `peek` by calling `advance()` twice.

### `std::unique_ptr<ProgramNode> parseProgram()`
Entry point. Parses zero or more statements until `EOF_TOKEN`. Returns the root AST node.
If errors occurred, the returned tree may be partial — callers should check `hasErrors()`.

### `bool hasErrors() const`
Returns true if any parse errors were recorded.

### `const std::vector<ParseError>& errors() const`
Returns the collected errors in order of occurrence.

## Error Strategy
- **No exceptions.** Errors are recorded via `recordError(message, line)`.
- **Panic-mode recovery.** `synchronize()` skips tokens until it finds:
  - `SEMICOLON` (end of statement)
  - `RBRACE` (end of block)
  - Statement-boundary keywords: `FN`, `LET`, `RETURN`, `WHILE`, `IF`
- After synchronizing, parsing continues so multiple errors can be reported in one pass.

## Integration with Lexer
- `Parser` owns a `Lexer` by value: `Lexer lexer_`.
- Only `lexer_.nextToken()` is called — never `tokenize()`.
- `current_` holds the token being processed; `peek_` holds the next one.
- One-token lookahead is sufficient for this LL(1)-friendly grammar.

## Implementation Order (bottom-up)
```
parsePrimary → parseUnary → parseMultiplicative → parseAdditive
    → parseComparison → parseAssignment → parseExpression
    → parseExprStmt / parseLetStmt / parseReturnStmt
    → parseWhileStmt / parseIfStmt / parseFnDecl / parseBlock
    → parseStatement → parseProgram
```
