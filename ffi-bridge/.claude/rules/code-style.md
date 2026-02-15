# Code Style

## C++ Naming Conventions
- Functions: `snake_case` (C linkage convention, e.g., `add`, `multiply`)
- Variables: `camelCase`
- Constants: `UPPER_SNAKE_CASE`
- Files: `snake_case`

## C++ Patterns to Use
- Always wrap exported functions in `extern "C" { ... }`
- Use `-fPIC` flag for position-independent code
- Use simple C-compatible types for the public API (int, double, const char*)
- Keep the public API minimal — complex types stay internal

## C++ Patterns to Avoid
- No C++ classes/templates in the exported API (ctypes can't handle them)
- No STL types in function signatures (std::string, std::vector, etc.)
- No exceptions crossing the FFI boundary
- No `using namespace std;` in headers

## Python Naming Conventions
- Functions/variables: `snake_case`
- Classes: `PascalCase`
- Constants: `UPPER_SNAKE_CASE`

## Python Patterns to Use
- Set `restype` and `argtypes` on every ctypes function
- Use `pathlib.Path` for library path resolution
- Wrap raw ctypes calls in a clean Python class
