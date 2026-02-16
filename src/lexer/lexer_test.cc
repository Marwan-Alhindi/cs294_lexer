#include "lexer.h"
#include <gtest/gtest.h>

// Helper: tokenize a string and return the token types (excluding EOF)
static std::vector<TokenType> types(const std::string& src) {
    Lexer lexer(src);
    auto tokens = lexer.tokenize();
    std::vector<TokenType> result;
    for (const auto& t : tokens) {
        if (t.type != TokenType::EOF_TOKEN) {
            result.push_back(t.type);
        }
    }
    return result;
}

// Helper: tokenize and return lexemes (excluding EOF)
static std::vector<std::string> lexemes(const std::string& src) {
    Lexer lexer(src);
    auto tokens = lexer.tokenize();
    std::vector<std::string> result;
    for (const auto& t : tokens) {
        if (t.type != TokenType::EOF_TOKEN) {
            result.push_back(t.lexeme);
        }
    }
    return result;
}

// --- Keywords ---

TEST(Lexer, TokenizesKeywords) {
    auto t = types("fn let mut if else while return");
    ASSERT_EQ(t.size(), 7u);
    EXPECT_EQ(t[0], TokenType::FN);
    EXPECT_EQ(t[1], TokenType::LET);
    EXPECT_EQ(t[2], TokenType::MUT);
    EXPECT_EQ(t[3], TokenType::IF);
    EXPECT_EQ(t[4], TokenType::ELSE);
    EXPECT_EQ(t[5], TokenType::WHILE);
    EXPECT_EQ(t[6], TokenType::RETURN);
}

// --- Identifiers ---

TEST(Lexer, TokenizesIdentifiers) {
    auto t = types("foo _bar x1");
    ASSERT_EQ(t.size(), 3u);
    EXPECT_EQ(t[0], TokenType::IDENT);
    EXPECT_EQ(t[1], TokenType::IDENT);
    EXPECT_EQ(t[2], TokenType::IDENT);
}

TEST(Lexer, IdentifierLexemes) {
    auto l = lexemes("foo _bar x1");
    ASSERT_EQ(l.size(), 3u);
    EXPECT_EQ(l[0], "foo");
    EXPECT_EQ(l[1], "_bar");
    EXPECT_EQ(l[2], "x1");
}

// --- Edge case: fn_name is IDENT, not FN ---

TEST(Lexer, KeywordPrefixIsIdentifier) {
    auto t = types("fn_name");
    ASSERT_EQ(t.size(), 1u);
    EXPECT_EQ(t[0], TokenType::IDENT);
}

// --- Numbers ---

TEST(Lexer, TokenizesNumbers) {
    auto t = types("42 0 123");
    ASSERT_EQ(t.size(), 3u);
    EXPECT_EQ(t[0], TokenType::NUMBER);
    EXPECT_EQ(t[1], TokenType::NUMBER);
    EXPECT_EQ(t[2], TokenType::NUMBER);

    auto l = lexemes("42 0 123");
    EXPECT_EQ(l[0], "42");
    EXPECT_EQ(l[1], "0");
    EXPECT_EQ(l[2], "123");
}

// --- Strings ---

TEST(Lexer, TokenizesStrings) {
    auto t = types("\"hello\" \"world\"");
    ASSERT_EQ(t.size(), 2u);
    EXPECT_EQ(t[0], TokenType::STRING);
    EXPECT_EQ(t[1], TokenType::STRING);
}

TEST(Lexer, StringLexemes) {
    auto l = lexemes("\"hello\"");
    ASSERT_EQ(l.size(), 1u);
    EXPECT_EQ(l[0], "hello");
}

TEST(Lexer, UnterminatedStringIsIllegal) {
    auto t = types("\"unterminated");
    ASSERT_EQ(t.size(), 1u);
    EXPECT_EQ(t[0], TokenType::ILLEGAL);
}

// --- Operators ---

TEST(Lexer, TokenizesSingleCharOperators) {
    auto t = types("+ - * / = < >");
    ASSERT_EQ(t.size(), 7u);
    EXPECT_EQ(t[0], TokenType::PLUS);
    EXPECT_EQ(t[1], TokenType::MINUS);
    EXPECT_EQ(t[2], TokenType::STAR);
    EXPECT_EQ(t[3], TokenType::SLASH);
    EXPECT_EQ(t[4], TokenType::ASSIGN);
    EXPECT_EQ(t[5], TokenType::LT);
    EXPECT_EQ(t[6], TokenType::GT);
}

TEST(Lexer, TokenizesDoubleCharOperators) {
    auto t = types("== != <= >=");
    ASSERT_EQ(t.size(), 4u);
    EXPECT_EQ(t[0], TokenType::EQ);
    EXPECT_EQ(t[1], TokenType::NEQ);
    EXPECT_EQ(t[2], TokenType::LTE);
    EXPECT_EQ(t[3], TokenType::GTE);
}

// --- Edge case: == is EQ, not two ASSIGNs ---

TEST(Lexer, DoubleEqualsIsOneToken) {
    Lexer lexer("==");
    auto tokens = lexer.tokenize();
    // Should be exactly 1 token + EOF
    int nonEof = 0;
    for (const auto& t : tokens) {
        if (t.type != TokenType::EOF_TOKEN) nonEof++;
    }
    EXPECT_EQ(nonEof, 1);
    EXPECT_EQ(tokens[0].type, TokenType::EQ);
}

// --- Punctuation ---

TEST(Lexer, TokenizesPunctuation) {
    auto t = types("( ) { } ; : ,");
    ASSERT_EQ(t.size(), 7u);
    EXPECT_EQ(t[0], TokenType::LPAREN);
    EXPECT_EQ(t[1], TokenType::RPAREN);
    EXPECT_EQ(t[2], TokenType::LBRACE);
    EXPECT_EQ(t[3], TokenType::RBRACE);
    EXPECT_EQ(t[4], TokenType::SEMICOLON);
    EXPECT_EQ(t[5], TokenType::COLON);
    EXPECT_EQ(t[6], TokenType::COMMA);
}

// --- Whitespace ---

TEST(Lexer, SkipsWhitespace) {
    auto t = types("  fn  \t  main  \n  ");
    ASSERT_EQ(t.size(), 2u);
    EXPECT_EQ(t[0], TokenType::FN);
    EXPECT_EQ(t[1], TokenType::IDENT);
}

// --- Comments ---

TEST(Lexer, SkipsLineComments) {
    auto t = types("fn // this is a comment\nmain");
    ASSERT_EQ(t.size(), 2u);
    EXPECT_EQ(t[0], TokenType::FN);
    EXPECT_EQ(t[1], TokenType::IDENT);
}

TEST(Lexer, SkipsBlockComments) {
    auto t = types("fn /* block comment */ main");
    ASSERT_EQ(t.size(), 2u);
    EXPECT_EQ(t[0], TokenType::FN);
    EXPECT_EQ(t[1], TokenType::IDENT);
}

// --- Empty input ---

TEST(Lexer, EmptyInputReturnsEof) {
    Lexer lexer("");
    auto tokens = lexer.tokenize();
    ASSERT_EQ(tokens.size(), 1u);
    EXPECT_EQ(tokens[0].type, TokenType::EOF_TOKEN);
}

// --- Line tracking ---

TEST(Lexer, TracksLineNumbers) {
    Lexer lexer("fn\nmain\n()");
    auto tokens = lexer.tokenize();
    // fn is on line 1
    EXPECT_EQ(tokens[0].line, 1);
    // main is on line 2
    EXPECT_EQ(tokens[1].line, 2);
    // ( is on line 3
    EXPECT_EQ(tokens[2].line, 3);
}

// --- Full program ---

TEST(Lexer, TokenizesSimpleFunction) {
    std::string src = "fn main() {\n    let x = 42;\n}";
    auto t = types(src);
    std::vector<TokenType> expected = {
        TokenType::FN, TokenType::IDENT, TokenType::LPAREN, TokenType::RPAREN,
        TokenType::LBRACE,
        TokenType::LET, TokenType::IDENT, TokenType::ASSIGN, TokenType::NUMBER,
        TokenType::SEMICOLON,
        TokenType::RBRACE
    };
    ASSERT_EQ(t.size(), expected.size());
    for (size_t i = 0; i < expected.size(); i++) {
        EXPECT_EQ(t[i], expected[i]) << "Mismatch at token index " << i;
    }
}

// --- Illegal characters ---

TEST(Lexer, IllegalCharacterProducesIllegalToken) {
    auto t = types("@");
    ASSERT_EQ(t.size(), 1u);
    EXPECT_EQ(t[0], TokenType::ILLEGAL);
}
