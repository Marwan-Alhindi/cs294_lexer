import ctypes
from pathlib import Path


class MathLib:
    def __init__(self, lib_path: str):
        self._lib = ctypes.CDLL(lib_path)

        # add
        self._lib.add.argtypes = [ctypes.c_int, ctypes.c_int]
        self._lib.add.restype = ctypes.c_int

        # subtract
        self._lib.subtract.argtypes = [ctypes.c_int, ctypes.c_int]
        self._lib.subtract.restype = ctypes.c_int

        # multiply
        self._lib.multiply.argtypes = [ctypes.c_int, ctypes.c_int]
        self._lib.multiply.restype = ctypes.c_int

        # divide
        self._lib.divide.argtypes = [ctypes.c_double, ctypes.c_double]
        self._lib.divide.restype = ctypes.c_double

        # factorial
        self._lib.factorial.argtypes = [ctypes.c_int]
        self._lib.factorial.restype = ctypes.c_int

        # fibonacci
        self._lib.fibonacci.argtypes = [ctypes.c_int]
        self._lib.fibonacci.restype = ctypes.c_int

    def add(self, a: int, b: int) -> int:
        return self._lib.add(a, b)

    def subtract(self, a: int, b: int) -> int:
        return self._lib.subtract(a, b)

    def multiply(self, a: int, b: int) -> int:
        return self._lib.multiply(a, b)

    def divide(self, a: float, b: float) -> float:
        return self._lib.divide(a, b)

    def factorial(self, n: int) -> int:
        return self._lib.factorial(n)

    def fibonacci(self, n: int) -> int:
        return self._lib.fibonacci(n)
