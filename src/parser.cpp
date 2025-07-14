#include "parser.h"
#include <stdexcept>

namespace {
struct Parser {
    const std::vector<Token>& tokens;
    size_t pos = 0;
    std::vector<Instruction> code;
    std::unordered_map<std::string, int> vars; // for variable existence

    Parser(const std::vector<Token>& t) : tokens(t) {}

    const Token& peek() const { return tokens[pos]; }
    const Token& advance() { return tokens[pos++]; }

    bool match(TokenType type) {
        if (peek().type == type) { advance(); return true; }
        return false;
    }

    void parseProgram() {
        while (peek().type != TokenType::End) {
            parseStatement();
        }
    }

    void parseStatement() {
        if (match(TokenType::Let)) {
            std::string name = expect(TokenType::Identifier).text;
            expect(TokenType::Equal);
            parseExpression();
            expect(TokenType::Semicolon);
            code.push_back({OpCode::STORE_VAR, name});
        } else if (match(TokenType::Print)) {
            parseExpression();
            expect(TokenType::Semicolon);
            code.push_back({OpCode::PRINT, ""});
        } else {
            throw std::runtime_error("Expected statement");
        }
    }

    Token expect(TokenType type) {
        if (peek().type != type)
            throw std::runtime_error("Unexpected token");
        return advance();
    }

    void parseExpression() { parseAdd(); }

    void parseAdd() {
        parseMul();
        while (true) {
            if (match(TokenType::Plus)) {
                parseMul();
                code.push_back({OpCode::ADD, ""});
            } else if (match(TokenType::Minus)) {
                parseMul();
                code.push_back({OpCode::SUB, ""});
            } else {
                break;
            }
        }
    }

    void parseMul() {
        parsePrimary();
        while (true) {
            if (match(TokenType::Star)) {
                parsePrimary();
                code.push_back({OpCode::MUL, ""});
            } else if (match(TokenType::Slash)) {
                parsePrimary();
                code.push_back({OpCode::DIV, ""});
            } else {
                break;
            }
        }
    }

    void parsePrimary() {
        if (match(TokenType::Number)) {
            code.push_back({OpCode::PUSH_CONST, tokens[pos-1].text});
        } else if (match(TokenType::Identifier)) {
            code.push_back({OpCode::LOAD_VAR, tokens[pos-1].text});
        } else if (match(TokenType::LParen)) {
            parseExpression();
            expect(TokenType::RParen);
        } else {
            throw std::runtime_error("Expected expression");
        }
    }
};
} // namespace

std::vector<Instruction> parse(const std::vector<Token>& tokens) {
    Parser p(tokens);
    p.parseProgram();
    return p.code;
}
