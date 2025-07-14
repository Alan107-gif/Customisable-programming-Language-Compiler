#pragma once
#include <string>
#include <vector>

enum class TokenType {
    End,
    Identifier,
    Number,
    Let,
    Print,
    If,
    Else,
    While,
    Plus,
    Minus,
    Star,
    Slash,
    Equal,
    EqualEqual,
    BangEqual,
    Greater,
    GreaterEqual,
    Less,
    LessEqual,
    Semicolon,
    LParen,
    RParen,
    LBrace,
    RBrace
};

struct Token {
    TokenType type;
    std::string text;
};

std::vector<Token> lex(const std::string& source);
