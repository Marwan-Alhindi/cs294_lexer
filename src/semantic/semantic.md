# Semantic Analyzer Module

## Status: Not Yet Implemented

## Purpose
Performs semantic validation on the AST produced by the parser. Catches errors that
are syntactically valid but semantically incorrect — type mismatches, undefined variables,
wrong number of arguments, etc.

## Planned Input / Output

- **Input:** `ProgramNode*` (root of the AST from the parser)
- **Output:** Annotated AST with resolved types, or a list of `SemanticError` structs

## Planned Analyses

### Name Resolution
- Build a symbol table (scoped: function params, let bindings, function names)
- Report error on use of undeclared identifier
- Report error on re-declaration in same scope

### Type Checking
- Infer types of expressions (integer, string, bool from comparison)
- Check that binary operator operands have compatible types
- Check that function call argument count matches declaration
- Check that `return` expression type matches function return type

## Planned API (sketch)

```cpp
struct SemanticError {
    std::string message;
    int line;
};

class SemanticAnalyzer {
public:
    explicit SemanticAnalyzer(ProgramNode* root);
    bool analyze();
    const std::vector<SemanticError>& errors() const;
};
```

## Design Notes
- Walk the AST with a visitor pattern or a recursive `analyzeNode(AstNode*)` function.
- Symbol table: `std::vector<std::unordered_map<std::string, TypeInfo>>` — stack of scopes.
- Push scope on `FnDeclNode` and `BlockNode`, pop on exit.
- No exceptions — errors collected like in the parser.
