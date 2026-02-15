#include "mathlib.h"
#include <gtest/gtest.h>

// --- add ---

TEST(MathLib, AddPositive) {
    EXPECT_EQ(add(3, 5), 8);
}

TEST(MathLib, AddZero) {
    EXPECT_EQ(add(0, 0), 0);
    EXPECT_EQ(add(5, 0), 5);
    EXPECT_EQ(add(0, 7), 7);
}

TEST(MathLib, AddNegative) {
    EXPECT_EQ(add(-3, -5), -8);
    EXPECT_EQ(add(-3, 5), 2);
}

// --- subtract ---

TEST(MathLib, SubtractBasic) {
    EXPECT_EQ(subtract(10, 3), 7);
    EXPECT_EQ(subtract(3, 10), -7);
}

TEST(MathLib, SubtractZero) {
    EXPECT_EQ(subtract(5, 0), 5);
    EXPECT_EQ(subtract(0, 5), -5);
}

// --- multiply ---

TEST(MathLib, MultiplyBasic) {
    EXPECT_EQ(multiply(3, 5), 15);
    EXPECT_EQ(multiply(-3, 5), -15);
}

TEST(MathLib, MultiplyZero) {
    EXPECT_EQ(multiply(0, 100), 0);
    EXPECT_EQ(multiply(100, 0), 0);
}

// --- divide ---

TEST(MathLib, DivideBasic) {
    EXPECT_DOUBLE_EQ(divide(10.0, 2.0), 5.0);
    EXPECT_DOUBLE_EQ(divide(7.0, 2.0), 3.5);
}

TEST(MathLib, DivideByZero) {
    EXPECT_DOUBLE_EQ(divide(10.0, 0.0), 0.0);
    EXPECT_DOUBLE_EQ(divide(0.0, 0.0), 0.0);
}

TEST(MathLib, DivideNegative) {
    EXPECT_DOUBLE_EQ(divide(-10.0, 2.0), -5.0);
    EXPECT_DOUBLE_EQ(divide(10.0, -2.0), -5.0);
}

// --- factorial ---

TEST(MathLib, FactorialBasic) {
    EXPECT_EQ(factorial(0), 1);
    EXPECT_EQ(factorial(1), 1);
    EXPECT_EQ(factorial(5), 120);
    EXPECT_EQ(factorial(10), 3628800);
}

TEST(MathLib, FactorialNegative) {
    EXPECT_EQ(factorial(-1), -1);
    EXPECT_EQ(factorial(-5), -1);
}

// --- fibonacci ---

TEST(MathLib, FibonacciBasic) {
    EXPECT_EQ(fibonacci(0), 0);
    EXPECT_EQ(fibonacci(1), 1);
    EXPECT_EQ(fibonacci(2), 1);
    EXPECT_EQ(fibonacci(5), 5);
    EXPECT_EQ(fibonacci(10), 55);
}

TEST(MathLib, FibonacciNegative) {
    EXPECT_EQ(fibonacci(-1), -1);
    EXPECT_EQ(fibonacci(-5), -1);
}
