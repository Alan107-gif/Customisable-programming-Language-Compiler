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
    PRINT,
    CMP_EQ,
    CMP_NEQ,
    CMP_LT,
    CMP_LE,
    CMP_GT,
    CMP_GE,
    JMP,
    JMP_IF_FALSE
};

struct Instruction {
    OpCode op;
    std::string text; // variable name or number as string
    int arg = 0;      // used for jump targets
};

std::vector<Instruction> parse(const std::vector<Token>& tokens);
