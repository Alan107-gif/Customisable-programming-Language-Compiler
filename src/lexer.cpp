#include "lexer.h"
#include <cctype>
#include <stdexcept>

std::vector<Token> lex(const std::string& source) {
    std::vector<Token> tokens;
    size_t i = 0;
    while (i < source.size()) {
        char c = source[i];
        if (std::isspace(static_cast<unsigned char>(c))) {
            ++i;
            continue;
        }
        if (std::isalpha(static_cast<unsigned char>(c)) || c == '_') {
            size_t start = i;
            while (i < source.size() && (std::isalnum(static_cast<unsigned char>(source[i])) || source[i] == '_'))
                ++i;
            std::string text = source.substr(start, i - start);
            TokenType type = TokenType::Identifier;
            if (text == "let") type = TokenType::Let;
            else if (text == "print") type = TokenType::Print;
            else if (text == "if") type = TokenType::If;
            else if (text == "else") type = TokenType::Else;
            else if (text == "while") type = TokenType::While;
            else if (text == "fn") type = TokenType::Fn;
            else if (text == "return") type = TokenType::Return;
            tokens.push_back({type, text});
            continue;
        }
        if (std::isdigit(static_cast<unsigned char>(c))) {
            size_t start = i;
            while (i < source.size() && std::isdigit(static_cast<unsigned char>(source[i])))
                ++i;
            tokens.push_back({TokenType::Number, source.substr(start, i - start)});
            continue;
        }
        switch (c) {
            case '+': tokens.push_back({TokenType::Plus, "+"}); break;
            case '-': tokens.push_back({TokenType::Minus, "-"}); break;
            case '*': tokens.push_back({TokenType::Star, "*"}); break;
            case '/': tokens.push_back({TokenType::Slash, "/"}); break;
            case '=':
                if (i + 1 < source.size() && source[i+1] == '=') { tokens.push_back({TokenType::EqualEqual, "=="}); ++i; }
                else tokens.push_back({TokenType::Equal, "="});
                break;
            case '!':
                if (i + 1 < source.size() && source[i+1] == '=') { tokens.push_back({TokenType::BangEqual, "!="}); ++i; }
                else throw std::runtime_error("Unexpected character: !");
                break;
            case '>':
                if (i + 1 < source.size() && source[i+1] == '=') { tokens.push_back({TokenType::GreaterEqual, ">="}); ++i; }
                else tokens.push_back({TokenType::Greater, ">"});
                break;
            case '<':
                if (i + 1 < source.size() && source[i+1] == '=') { tokens.push_back({TokenType::LessEqual, "<="}); ++i; }
                else tokens.push_back({TokenType::Less, "<"});
                break;
            case '{': tokens.push_back({TokenType::LBrace, "{"}); break;
            case '}': tokens.push_back({TokenType::RBrace, "}"}); break;
            case ';': tokens.push_back({TokenType::Semicolon, ";"}); break;
            case '(': tokens.push_back({TokenType::LParen, "("}); break;
            case ')': tokens.push_back({TokenType::RParen, ")"}); break;
            case ',': tokens.push_back({TokenType::Comma, ","}); break;
            default: throw std::runtime_error(std::string("Unexpected character: ") + c);
        }
        ++i;
    }
    tokens.push_back({TokenType::End, ""});
    return tokens;
}
