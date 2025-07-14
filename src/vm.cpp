#include "vm.h"
#include <iostream>
#include <stdexcept>

void VM::run(const std::vector<Instruction>& code) {
    stack.clear();
    for (size_t ip = 0; ip < code.size(); ++ip) {
        const Instruction& inst = code[ip];
        switch (inst.op) {
            case OpCode::PUSH_CONST:
                stack.push_back(std::stoi(inst.text));
                break;
            case OpCode::LOAD_VAR:
                if (vars.find(inst.text) == vars.end())
                    throw std::runtime_error("Undefined variable: " + inst.text);
                stack.push_back(vars[inst.text]);
                break;
            case OpCode::STORE_VAR:
                if (stack.empty()) throw std::runtime_error("Stack underflow");
                vars[inst.text] = stack.back();
                stack.pop_back();
                break;
            case OpCode::ADD:
                if (stack.size() < 2) throw std::runtime_error("Stack underflow");
                stack[stack.size()-2] += stack.back();
                stack.pop_back();
                break;
            case OpCode::SUB:
                if (stack.size() < 2) throw std::runtime_error("Stack underflow");
                stack[stack.size()-2] -= stack.back();
                stack.pop_back();
                break;
            case OpCode::MUL:
                if (stack.size() < 2) throw std::runtime_error("Stack underflow");
                stack[stack.size()-2] *= stack.back();
                stack.pop_back();
                break;
            case OpCode::DIV:
                if (stack.size() < 2) throw std::runtime_error("Stack underflow");
                stack[stack.size()-2] /= stack.back();
                stack.pop_back();
                break;
            case OpCode::PRINT:
                if (stack.empty()) throw std::runtime_error("Stack underflow");
                std::cout << stack.back() << std::endl;
                stack.pop_back();
                break;
            case OpCode::CMP_EQ:
                if (stack.size() < 2) throw std::runtime_error("Stack underflow");
                stack[stack.size()-2] = (stack[stack.size()-2] == stack.back());
                stack.pop_back();
                break;
            case OpCode::CMP_NEQ:
                if (stack.size() < 2) throw std::runtime_error("Stack underflow");
                stack[stack.size()-2] = (stack[stack.size()-2] != stack.back());
                stack.pop_back();
                break;
            case OpCode::CMP_LT:
                if (stack.size() < 2) throw std::runtime_error("Stack underflow");
                stack[stack.size()-2] = (stack[stack.size()-2] < stack.back());
                stack.pop_back();
                break;
            case OpCode::CMP_LE:
                if (stack.size() < 2) throw std::runtime_error("Stack underflow");
                stack[stack.size()-2] = (stack[stack.size()-2] <= stack.back());
                stack.pop_back();
                break;
            case OpCode::CMP_GT:
                if (stack.size() < 2) throw std::runtime_error("Stack underflow");
                stack[stack.size()-2] = (stack[stack.size()-2] > stack.back());
                stack.pop_back();
                break;
            case OpCode::CMP_GE:
                if (stack.size() < 2) throw std::runtime_error("Stack underflow");
                stack[stack.size()-2] = (stack[stack.size()-2] >= stack.back());
                stack.pop_back();
                break;
            case OpCode::JMP:
                ip = inst.arg - 1;
                break;
            case OpCode::JMP_IF_FALSE:
                if (stack.empty()) throw std::runtime_error("Stack underflow");
                if (!stack.back()) ip = inst.arg - 1;
                stack.pop_back();
                break;
        }
    }
}
