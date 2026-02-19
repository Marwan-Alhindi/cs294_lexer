# Architecture

## What the System Is
A compiler for basic Rust syntax. Reads a `.rs` source file and processes it through
a full compiler pipeline: lexing → parsing → (semantic analysis) → (code generation).

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
[parser] — recursive descent, consumes tokens, produces AST
    |
    v
[ast] — AstNode hierarchy (ProgramNode, FnDeclNode, LetStmtNode, ...)
    |
    v
[semantic] — type checking, name resolution (planned)
    |
    v
[codegen] — three-address code / LLVM IR emission (planned)
    |
    v
stdout — parsed AST summary or generated code
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

### `src/ast/`
- Defines `NodeKind` enum (15 node kinds)
- Defines `AstNode` base struct and 14 concrete node structs
- All nodes owned via `AstNodePtr = std::unique_ptr<AstNode>`
- No virtual methods — use `kind` field + `static_cast` to downcast

### `src/parser/`
- `Parser` class owns a `Lexer` by value
- `parseProgram()` returns `std::unique_ptr<ProgramNode>` (the AST root)
- Recursive descent, one-token lookahead (`current_` + `peek_`)
- Errors collected in `std::vector<ParseError>` — no exceptions
- Panic-mode recovery via `synchronize()` for multi-error reporting

### `src/semantic/` (planned)
- Walk AST, build scoped symbol table, infer and check types
- Produce `std::vector<SemanticError>`

### `src/codegen/` (planned)
- Walk annotated AST, emit three-address code or LLVM IR

### `src/main/`
- CLI entry point
- Reads a `.rs` file from argv
- Invokes `Parser`, checks for errors, prints AST summary

## Data Flow
```
main.cpp: reads file → string
         ↓
Lexer(source): stores source, position = 0
         ↓
Parser(source): owns Lexer, primes current + peek
         ↓
parseProgram(): recursive descent → ProgramNode
         ↓
AstNode tree: ProgramNode → [FnDeclNode, LetStmtNode, ...]
         ↓
(semantic analysis, code generation — future phases)
```

## Grammar (Rust subset)

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
