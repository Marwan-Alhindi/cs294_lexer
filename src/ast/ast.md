# AST Module

## Purpose
Defines the Abstract Syntax Tree (AST) node types that represent parsed Rust source code.
The AST is the output of the parser and the input to the semantic analyzer.

## Node Hierarchy

```
AstNode (base)
├── Statements
│   ├── ProgramNode       — top-level list of statements
│   ├── FnDeclNode        — fn <ident>(<params>) <block>
│   ├── BlockNode         — { statement* }
│   ├── LetStmtNode       — let mut? <ident> (: <type>)? = <expr>;
│   ├── ReturnStmtNode    — return <expr>?;
│   ├── WhileStmtNode     — while <expr> <block>
│   ├── IfStmtNode        — if <expr> <block> (else (block | if_stmt))?
│   └── ExprStmtNode      — <expr>;
└── Expressions
    ├── AssignExprNode    — <ident> = <expr>
    ├── BinaryExprNode    — <expr> <op> <expr>
    ├── UnaryExprNode     — -<expr>
    ├── CallExprNode      — <ident>(<args>)
    ├── IdentExprNode     — <ident>
    ├── NumberLiteralNode — <number>
    └── StringLiteralNode — "<string>"
```

## Public API

### `enum class NodeKind`
One entry per concrete node type (15 total).

### `struct AstNode`
Base struct with a `NodeKind kind` field. All concrete nodes embed this.
No virtual dispatch — `kind` is used for downcasting.

### `using AstNodePtr = std::unique_ptr<AstNode>`
Ownership alias. All nodes are heap-allocated and transferred via `unique_ptr`.

## Ownership Model
- The `ProgramNode` owns all top-level statement nodes.
- Each compound node owns its children via `AstNodePtr` fields or `std::vector<AstNodePtr>`.
- No shared ownership (`shared_ptr`) anywhere — ownership tree is a DAG without cycles.

## Design Constraints
- No virtual methods — keeps the struct layout simple and avoids vtable overhead.
- Use `static_cast<ConcreteNode*>(ptr.get())` to downcast after checking `kind`.
- `number` literals are stored as `std::string` — numeric conversion belongs in semantic analysis.
- Line numbers are stored on each node for error reporting downstream.
