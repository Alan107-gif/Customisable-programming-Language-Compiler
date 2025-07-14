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
        } else if (match(TokenType::If)) {
            parseIf();
        } else if (match(TokenType::While)) {
            parseWhile();
        } else if (match(TokenType::Print)) {
            parseExpression();
            expect(TokenType::Semicolon);
            code.push_back({OpCode::PRINT, ""});
        } else if (peek().type == TokenType::Identifier && pos + 1 < tokens.size() && tokens[pos+1].type == TokenType::Equal) {
            std::string name = advance().text; // identifier
            advance(); // '='
            parseExpression();
            expect(TokenType::Semicolon);
            code.push_back({OpCode::STORE_VAR, name});
        } else {
            throw std::runtime_error("Expected statement");
        }
    }

    void parseBlock() {
        while (!match(TokenType::RBrace)) {
            parseStatement();
        }
    }

    void patchJump(size_t index, size_t target) {
        code[index].arg = static_cast<int>(target);
    }

    void parseIf() {
        expect(TokenType::LParen);
        parseExpression();
        expect(TokenType::RParen);
        size_t jmpIfIndex = code.size();
        code.push_back({OpCode::JMP_IF_FALSE, "", 0});
        expect(TokenType::LBrace);
        parseBlock();
        if (match(TokenType::Else)) {
            size_t jmpIndex = code.size();
            code.push_back({OpCode::JMP, "", 0});
            patchJump(jmpIfIndex, code.size());
            expect(TokenType::LBrace);
            parseBlock();
            patchJump(jmpIndex, code.size());
        } else {
            patchJump(jmpIfIndex, code.size());
        }
    }

    void parseWhile() {
        size_t loopStart = code.size();
        expect(TokenType::LParen);
        parseExpression();
        expect(TokenType::RParen);
        size_t jmpIfIndex = code.size();
        code.push_back({OpCode::JMP_IF_FALSE, "", 0});
        expect(TokenType::LBrace);
        parseBlock();
        code.push_back({OpCode::JMP, "", static_cast<int>(loopStart)});
        patchJump(jmpIfIndex, code.size());
    }

    Token expect(TokenType type) {
        if (peek().type != type)
            throw std::runtime_error("Unexpected token");
        return advance();
    }

    void parseExpression() { parseEquality(); }

    void parseEquality() {
        parseComparison();
        while (true) {
            if (match(TokenType::EqualEqual)) {
                parseComparison();
                code.push_back({OpCode::CMP_EQ, ""});
            } else if (match(TokenType::BangEqual)) {
                parseComparison();
                code.push_back({OpCode::CMP_NEQ, ""});
            } else {
                break;
            }
        }
    }

    void parseComparison() {
        parseAdd();
        while (true) {
            if (match(TokenType::Greater)) {
                parseAdd();
                code.push_back({OpCode::CMP_GT, ""});
            } else if (match(TokenType::GreaterEqual)) {
                parseAdd();
                code.push_back({OpCode::CMP_GE, ""});
            } else if (match(TokenType::Less)) {
                parseAdd();
                code.push_back({OpCode::CMP_LT, ""});
            } else if (match(TokenType::LessEqual)) {
                parseAdd();
                code.push_back({OpCode::CMP_LE, ""});
            } else {
                break;
            }
        }
    }

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
