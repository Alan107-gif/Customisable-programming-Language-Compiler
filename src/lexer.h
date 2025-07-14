#pragma once
#include <string>
#include <vector>

enum class TokenType {
    End,
    Identifier,
    Number,
    Let,
    Print,
    Plus,
    Minus,
    Star,
    Slash,
    Equal,
    Semicolon,
    LParen,
    RParen
};

struct Token {
    TokenType type;
    std::string text;
};

std::vector<Token> lex(const std::string& source);
