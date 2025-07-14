#include "lexer.h"
#include "parser.h"
#include "vm.h"
#include <fstream>
#include <iostream>
#include <sstream>

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: cplc <source.cpl>" << std::endl;
        return 1;
    }
    std::ifstream in(argv[1]);
    if (!in) {
        std::cerr << "Unable to open file: " << argv[1] << std::endl;
        return 1;
    }
    std::stringstream buffer;
    buffer << in.rdbuf();
    auto tokens = lex(buffer.str());
    Program prog = parse(tokens);
    VM vm;
    vm.run(prog);
    return 0;
}
