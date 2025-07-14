#pragma once
#include "lexer.h"
#include <vector>
#include <string>
#include <unordered_map>

enum class OpCode {
    PUSH_CONST,
    LOAD_VAR,
    STORE_VAR,
    ADD,
    SUB,
    MUL,
    DIV,
    PRINT
};

struct Instruction {
    OpCode op;
    std::string text; // variable name or number as string
};

std::vector<Instruction> parse(const std::vector<Token>& tokens);
