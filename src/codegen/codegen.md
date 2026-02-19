# Code Generation Module

## Status: Not Yet Implemented

## Purpose
Translates the semantically-validated AST into backend output.
The initial target is three-address code (TAC) printed to stdout.
A later target may be LLVM IR for actual compilation.

## Planned Input / Output

- **Input:** Annotated `ProgramNode*` (after semantic analysis)
- **Output:** Three-address code or LLVM IR as a string / stdout

## Planned Design

### Three-Address Code (Phase 1)
Simple linear IR where each instruction has at most one operator and three operands.

Example — `let x = a + b * c;` becomes:
```
t0 = b * c
t1 = a + t0
x  = t1
```

### LLVM IR (Phase 2 — optional)
Use LLVM C API or `llvm::IRBuilder` to emit `.ll` text.
Each function maps to an `llvm::Function`, each block to an `llvm::BasicBlock`.

## Planned API (sketch)

```cpp
class CodeGen {
public:
    explicit CodeGen(ProgramNode* root);
    std::string emit();   // returns generated code as string
};
```

## Design Notes
- Walk the AST recursively, emitting instructions for each expression and statement.
- Maintain a temp counter (`t0`, `t1`, ...) for intermediate values.
- Function calls map to call instructions with argument lists.
- Control flow (`if`, `while`) maps to labels and conditional jumps.
