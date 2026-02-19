#include "parser.h"
#include <stdexcept>

// ============================================================
// Constructor — prime the two-token lookahead
// ============================================================
Parser::Parser(const std::string& source)
    : lexer_(source),
      current_(Token{TokenType::EOF_TOKEN, "", 0}),
      peek_(Token{TokenType::EOF_TOKEN, "", 0}) {
    // Call advance() twice to fill current_ and peek_.
    advance();
    advance();
}

// ============================================================
// Token navigation helpers
// ============================================================

void Parser::advance() {
    current_ = peek_;
    peek_ = lexer_.nextToken();
}

bool Parser::check(TokenType type) const {
    return current_.type == type;
}

bool Parser::match(TokenType type) {
    if (check(type)) {
        advance();
        return true;
    }
    return false;
}

Token Parser::expect(TokenType type, const std::string& errorMsg) {
    if (check(type)) {
        Token tok = current_;
        advance();
        return tok;
    }
    recordError(errorMsg, current_.line);
    return current_;  // Return current so parsing can attempt to continue
}

// ============================================================
// Error handling
// ============================================================

void Parser::recordError(const std::string& msg, int line) {
    errors_.push_back(ParseError{msg, line});
}

void Parser::synchronize() {
    // Skip tokens until we find a likely statement boundary
    while (!check(TokenType::EOF_TOKEN)) {
        if (check(TokenType::SEMICOLON)) {
            advance();  // consume the semicolon
            return;
        }
        if (check(TokenType::RBRACE)) {
            return;  // do NOT consume — let the enclosing block handle it
        }
        // Statement-keyword boundaries
        if (check(TokenType::FN) || check(TokenType::LET) ||
            check(TokenType::RETURN) || check(TokenType::WHILE) ||
            check(TokenType::IF)) {
            return;
        }
        advance();
    }
}

// ============================================================
// Public API
// ============================================================

bool Parser::hasErrors() const {
    return !errors_.empty();
}

const std::vector<ParseError>& Parser::errors() const {
    return errors_;
}

// ============================================================
// Top-level
// ============================================================

std::unique_ptr<ProgramNode> Parser::parseProgram() {
    auto program = std::make_unique<ProgramNode>();
    while (!check(TokenType::EOF_TOKEN)) {
        auto stmt = parseStatement();
        if (stmt) {
            program->statements.push_back(std::move(stmt));
        }
    }
    return program;
}

// ============================================================
// Statements
// ============================================================

AstNodePtr Parser::parseStatement() {
    if (check(TokenType::FN))     return parseFnDecl();
    if (check(TokenType::LET))    return parseLetStmt();
    if (check(TokenType::RETURN)) return parseReturnStmt();
    if (check(TokenType::WHILE))  return parseWhileStmt();
    if (check(TokenType::IF))     return parseIfStmt();
    if (check(TokenType::LBRACE)) return parseBlock();
    return parseExprStmt();
}

AstNodePtr Parser::parseFnDecl() {
    int line = current_.line;
    advance();  // consume FN

    Token nameTok = expect(TokenType::IDENT, "Expected function name after 'fn'");
    auto node = std::make_unique<FnDeclNode>(nameTok.lexeme, line);

    expect(TokenType::LPAREN, "Expected '(' after function name");

    // Parse parameter list: (ident: ident, ident: ident, ...)
    if (!check(TokenType::RPAREN)) {
        do {
            Token paramName = expect(TokenType::IDENT, "Expected parameter name");
            expect(TokenType::COLON, "Expected ':' after parameter name");
            Token paramType = expect(TokenType::IDENT, "Expected parameter type");
            node->params.push_back(ParamNode{paramName.lexeme, paramType.lexeme, paramName.line});
        } while (match(TokenType::COMMA));
    }

    expect(TokenType::RPAREN, "Expected ')' after parameters");

    auto body = parseBlock();
    if (body) {
        node->body = std::move(body);
    }
    return node;
}

AstNodePtr Parser::parseBlock() {
    int line = current_.line;
    expect(TokenType::LBRACE, "Expected '{'");

    auto block = std::make_unique<BlockNode>(line);
    while (!check(TokenType::RBRACE) && !check(TokenType::EOF_TOKEN)) {
        auto stmt = parseStatement();
        if (stmt) {
            block->statements.push_back(std::move(stmt));
        }
    }

    expect(TokenType::RBRACE, "Expected '}'");
    return block;
}

AstNodePtr Parser::parseLetStmt() {
    int line = current_.line;
    advance();  // consume LET

    bool isMut = match(TokenType::MUT);
    Token nameTok = expect(TokenType::IDENT, "Expected variable name after 'let'");

    auto node = std::make_unique<LetStmtNode>(isMut, nameTok.lexeme, line);

    // Optional type annotation: : typename
    if (match(TokenType::COLON)) {
        Token typeTok = expect(TokenType::IDENT, "Expected type name after ':'");
        node->typeName = typeTok.lexeme;
    }

    expect(TokenType::ASSIGN, "Expected '=' in let statement");
    node->init = parseExpression();
    expect(TokenType::SEMICOLON, "Expected ';' after let statement");
    return node;
}

AstNodePtr Parser::parseReturnStmt() {
    int line = current_.line;
    advance();  // consume RETURN

    auto node = std::make_unique<ReturnStmtNode>(line);

    // Optional return value
    if (!check(TokenType::SEMICOLON) && !check(TokenType::EOF_TOKEN)) {
        node->value = parseExpression();
    }

    expect(TokenType::SEMICOLON, "Expected ';' after return statement");
    return node;
}

AstNodePtr Parser::parseWhileStmt() {
    int line = current_.line;
    advance();  // consume WHILE

    auto node = std::make_unique<WhileStmtNode>(line);
    node->condition = parseExpression();
    node->body = parseBlock();
    return node;
}

AstNodePtr Parser::parseIfStmt() {
    int line = current_.line;
    advance();  // consume IF

    auto node = std::make_unique<IfStmtNode>(line);
    node->condition = parseExpression();
    node->thenBranch = parseBlock();

    if (match(TokenType::ELSE)) {
        if (check(TokenType::IF)) {
            node->elseBranch = parseIfStmt();  // else if chain
        } else {
            node->elseBranch = parseBlock();
        }
    }

    return node;
}

AstNodePtr Parser::parseExprStmt() {
    int line = current_.line;
    auto node = std::make_unique<ExprStmtNode>(line);
    node->expr = parseExpression();
    expect(TokenType::SEMICOLON, "Expected ';' after expression statement");
    return node;
}

// ============================================================
// Expressions (precedence: assignment < comparison < additive
//              < multiplicative < unary < primary)
// ============================================================

AstNodePtr Parser::parseExpression() {
    return parseAssignment();
}

AstNodePtr Parser::parseAssignment() {
    // Look ahead: if current is IDENT and peek is ASSIGN, it's an assignment.
    if (check(TokenType::IDENT) && peek_.type == TokenType::ASSIGN) {
        std::string target = current_.lexeme;
        int line = current_.line;
        advance();  // consume IDENT
        advance();  // consume ASSIGN
        auto node = std::make_unique<AssignExprNode>(target, line);
        node->value = parseAssignment();  // right-associative
        return node;
    }
    return parseComparison();
}

AstNodePtr Parser::parseComparison() {
    auto left = parseAdditive();

    while (check(TokenType::EQ) || check(TokenType::NEQ) ||
           check(TokenType::LT) || check(TokenType::GT) ||
           check(TokenType::LTE) || check(TokenType::GTE)) {
        std::string op = current_.lexeme;
        int line = current_.line;
        advance();
        auto node = std::make_unique<BinaryExprNode>(op, line);
        node->left = std::move(left);
        node->right = parseAdditive();
        left = std::move(node);
    }

    return left;
}

AstNodePtr Parser::parseAdditive() {
    auto left = parseMultiplicative();

    while (check(TokenType::PLUS) || check(TokenType::MINUS)) {
        std::string op = current_.lexeme;
        int line = current_.line;
        advance();
        auto node = std::make_unique<BinaryExprNode>(op, line);
        node->left = std::move(left);
        node->right = parseMultiplicative();
        left = std::move(node);
    }

    return left;
}

AstNodePtr Parser::parseMultiplicative() {
    auto left = parseUnary();

    while (check(TokenType::STAR) || check(TokenType::SLASH)) {
        std::string op = current_.lexeme;
        int line = current_.line;
        advance();
        auto node = std::make_unique<BinaryExprNode>(op, line);
        node->left = std::move(left);
        node->right = parseUnary();
        left = std::move(node);
    }

    return left;
}

AstNodePtr Parser::parseUnary() {
    if (check(TokenType::MINUS)) {
        std::string op = current_.lexeme;
        int line = current_.line;
        advance();
        auto node = std::make_unique<UnaryExprNode>(op, line);
        node->operand = parseUnary();  // right-recursive for e.g. --x
        return node;
    }
    return parsePrimary();
}

AstNodePtr Parser::parsePrimary() {
    // Number literal
    if (check(TokenType::NUMBER)) {
        auto node = std::make_unique<NumberLiteralNode>(current_.lexeme, current_.line);
        advance();
        return node;
    }

    // String literal
    if (check(TokenType::STRING)) {
        auto node = std::make_unique<StringLiteralNode>(current_.lexeme, current_.line);
        advance();
        return node;
    }

    // Identifier or function call
    if (check(TokenType::IDENT)) {
        std::string name = current_.lexeme;
        int line = current_.line;
        advance();

        // Function call: ident(...)
        if (check(TokenType::LPAREN)) {
            advance();  // consume LPAREN
            auto node = std::make_unique<CallExprNode>(name, line);
            if (!check(TokenType::RPAREN)) {
                do {
                    node->args.push_back(parseExpression());
                } while (match(TokenType::COMMA));
            }
            expect(TokenType::RPAREN, "Expected ')' after call arguments");
            return node;
        }

        return std::make_unique<IdentExprNode>(name, line);
    }

    // Grouped expression: (expr)
    if (check(TokenType::LPAREN)) {
        advance();  // consume LPAREN
        auto expr = parseExpression();
        expect(TokenType::RPAREN, "Expected ')' after grouped expression");
        return expr;
    }

    // Unexpected token
    recordError("Unexpected token '" + current_.lexeme + "' in expression", current_.line);
    synchronize();
    return nullptr;
}
