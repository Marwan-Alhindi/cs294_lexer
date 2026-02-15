#include "lexer.h"

Lexer::Lexer(const std::string& source)
    : source(source), pos(0), line(1) {}

Token Lexer::nextToken() {
    // TODO: implement
    return Token{TokenType::EOF_TOKEN, "", line};
}

std::vector<Token> Lexer::tokenize() {
    // TODO: implement
    return {};
}

char Lexer::peekChar() const {
    // TODO: implement
    return '\0';
}

char Lexer::advance() {
    // TODO: implement
    return '\0';
}

void Lexer::skipWhitespace() {
    // TODO: implement
}

void Lexer::skipComments() {
    // TODO: implement
}

Token Lexer::readIdentifier() {
    // TODO: implement
    return Token{TokenType::IDENT, "", line};
}

Token Lexer::readNumber() {
    // TODO: implement
    return Token{TokenType::NUMBER, "", line};
}

Token Lexer::readString() {
    // TODO: implement
    return Token{TokenType::STRING, "", line};
}
