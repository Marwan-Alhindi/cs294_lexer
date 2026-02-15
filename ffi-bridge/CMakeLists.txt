cmake_minimum_required(VERSION 3.14)
project(ffi_bridge LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Shared library (.so / .dylib) ---
add_library(mathlib SHARED
    src/mathlib/mathlib.cpp
)
target_compile_options(mathlib PRIVATE -fPIC)

# --- GoogleTest ---
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)
FetchContent_MakeAvailable(googletest)

enable_testing()

# --- C++ tests ---
add_executable(mathlib_test
    src/mathlib/mathlib_test.cc
    src/mathlib/mathlib.cpp
)
target_link_libraries(mathlib_test GTest::gtest_main)
add_test(NAME MathLibTests COMMAND mathlib_test)
