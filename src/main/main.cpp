#include "../lexer/lexer.h"
#include <fstream>
#include <iostream>
#include <sstream>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: rustc <source_file>" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "Error: could not open file '" << argv[1] << "'" << std::endl;
        return 1;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string source = buffer.str();

    Lexer lexer(source);
    std::vector<Token> tokens = lexer.tokenize();

    for (const auto& tok : tokens) {
        if (tok.type == TokenType::EOF_TOKEN) {
            break;
        }
        std::cout << tokenTypeToString(tok.type) << " " << tok.lexeme << std::endl;
    }

    return 0;
}
