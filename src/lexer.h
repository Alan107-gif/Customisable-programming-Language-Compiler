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
    Fn,
    Return,
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
    RBrace,
    Comma
};

struct Token {
    TokenType type;
    std::string text;
};

std::vector<Token> lex(const std::string& source);
