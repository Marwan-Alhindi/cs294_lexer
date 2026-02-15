"""Python-side tests: verify C++ functions work correctly through ctypes FFI."""

import sys
from pathlib import Path

import pytest

# Add project root to path
project_root = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(project_root))

from src.bindings.mathlib_wrapper import MathLib

# Resolve library path
LIB_PATH = project_root / "build" / "libmathlib.dylib"
if not LIB_PATH.exists():
    LIB_PATH = project_root / "build" / "libmathlib.so"


@pytest.fixture
def lib():
    if not LIB_PATH.exists():
        pytest.skip("Shared library not built. Run: cmake -B build && cmake --build build")
    return MathLib(str(LIB_PATH))


# --- add ---

def test_add_positive(lib):
    assert lib.add(3, 5) == 8

def test_add_zero(lib):
    assert lib.add(0, 0) == 0
    assert lib.add(5, 0) == 5

def test_add_negative(lib):
    assert lib.add(-3, -5) == -8
    assert lib.add(-3, 5) == 2


# --- subtract ---

def test_subtract_basic(lib):
    assert lib.subtract(10, 3) == 7
    assert lib.subtract(3, 10) == -7


# --- multiply ---

def test_multiply_basic(lib):
    assert lib.multiply(3, 5) == 15
    assert lib.multiply(-3, 5) == -15

def test_multiply_zero(lib):
    assert lib.multiply(0, 100) == 0


# --- divide ---

def test_divide_basic(lib):
    assert lib.divide(10.0, 2.0) == pytest.approx(5.0)
    assert lib.divide(7.0, 2.0) == pytest.approx(3.5)

def test_divide_by_zero(lib):
    assert lib.divide(10.0, 0.0) == pytest.approx(0.0)

def test_divide_negative(lib):
    assert lib.divide(-10.0, 2.0) == pytest.approx(-5.0)


# --- factorial ---

def test_factorial_basic(lib):
    assert lib.factorial(0) == 1
    assert lib.factorial(1) == 1
    assert lib.factorial(5) == 120

def test_factorial_negative(lib):
    assert lib.factorial(-1) == -1


# --- fibonacci ---

def test_fibonacci_basic(lib):
    assert lib.fibonacci(0) == 0
    assert lib.fibonacci(1) == 1
    assert lib.fibonacci(5) == 5
    assert lib.fibonacci(10) == 55

def test_fibonacci_negative(lib):
    assert lib.fibonacci(-1) == -1
