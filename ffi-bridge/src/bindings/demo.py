"""Demo script: calls C++ shared library from Python via ctypes."""

import sys
from pathlib import Path

# Add src to path so we can import the wrapper
sys.path.insert(0, str(Path(__file__).resolve().parent.parent.parent))

from src.bindings.mathlib_wrapper import MathLib


def main():
    # Resolve library path relative to project root
    project_root = Path(__file__).resolve().parent.parent.parent
    lib_path = project_root / "build" / "libmathlib.dylib"

    if not lib_path.exists():
        # Try .so extension (Linux)
        lib_path = project_root / "build" / "libmathlib.so"

    if not lib_path.exists():
        print(f"Error: shared library not found. Build first with:")
        print(f"  cmake -B build && cmake --build build")
        sys.exit(1)

    lib = MathLib(str(lib_path))

    print("=== FFI Bridge Demo ===")
    print(f"add(3, 5)        = {lib.add(3, 5)}")
    print(f"subtract(10, 3)  = {lib.subtract(10, 3)}")
    print(f"multiply(4, 7)   = {lib.multiply(4, 7)}")
    print(f"divide(10, 3)    = {lib.divide(10.0, 3.0)}")
    print(f"divide(10, 0)    = {lib.divide(10.0, 0.0)}")
    print(f"factorial(5)     = {lib.factorial(5)}")
    print(f"fibonacci(10)    = {lib.fibonacci(10)}")


if __name__ == "__main__":
    main()
