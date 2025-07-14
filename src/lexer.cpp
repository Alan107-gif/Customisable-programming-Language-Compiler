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
            case '=': tokens.push_back({TokenType::Equal, "="}); break;
            case ';': tokens.push_back({TokenType::Semicolon, ";"}); break;
            case '(': tokens.push_back({TokenType::LParen, "("}); break;
            case ')': tokens.push_back({TokenType::RParen, ")"}); break;
            default: throw std::runtime_error(std::string("Unexpected character: ") + c);
        }
        ++i;
    }
    tokens.push_back({TokenType::End, ""});
    return tokens;
}
