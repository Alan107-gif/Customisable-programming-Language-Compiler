#pragma once
#include "parser.h"
#include <vector>
#include <string>
#include <unordered_map>

class VM {
public:
    void run(const std::vector<Instruction>& code);
private:
    std::vector<int> stack;
    std::unordered_map<std::string,int> vars;
};
