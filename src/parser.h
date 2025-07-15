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
    JMP_IF_FALSE,
    CALL,
    RET,
    POP
};

struct Instruction {
    OpCode op;
    std::string text; // variable name, number or function name
    int arg = 0;      // jump targets or argument count
};

struct Function {
    size_t address;
    std::vector<std::string> params;
};

struct Program {
    std::vector<Instruction> code;
    std::unordered_map<std::string, Function> functions;
};

Program parse(const std::vector<Token>& tokens);
