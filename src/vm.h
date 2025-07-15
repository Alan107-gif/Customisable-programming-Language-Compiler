#pragma once
#include "parser.h"
#include <vector>
#include <string>
#include <unordered_map>

class VM {
public:
    void run(const Program& program);
private:
    std::vector<int> stack;
    std::vector<std::unordered_map<std::string,int>> env;
    std::unordered_map<std::string, Function> functions;
};
