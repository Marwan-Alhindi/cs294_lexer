cmake_minimum_required(VERSION 3.14)
project(rustc_lexer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Main binary ---
add_executable(rustc
    src/main/main.cpp
    src/lexer/lexer.cpp
    src/token/token.cpp
)

# --- GoogleTest ---
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)
FetchContent_MakeAvailable(googletest)

enable_testing()

# --- Token tests ---
add_executable(token_test
    src/token/token_test.cc
    src/token/token.cpp
)
target_link_libraries(token_test GTest::gtest_main)
add_test(NAME TokenTests COMMAND token_test)

# --- Lexer tests ---
add_executable(lexer_test
    src/lexer/lexer_test.cc
    src/lexer/lexer.cpp
    src/token/token.cpp
)
target_link_libraries(lexer_test GTest::gtest_main)
add_test(NAME LexerTests COMMAND lexer_test)
