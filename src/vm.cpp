#include "vm.h"
#include <iostream>
#include <stdexcept>

void VM::run(const Program& program) {
    stack.clear();
    env.clear();
    env.push_back({});
    functions = program.functions;
    const auto& code = program.code;
    std::vector<size_t> callStack;
    for (size_t ip = 0; ip < code.size(); ++ip) {
        const Instruction& inst = code[ip];
        switch (inst.op) {
            case OpCode::PUSH_CONST:
                stack.push_back(std::stoi(inst.text));
                break;
            case OpCode::LOAD_VAR: {
                bool found = false;
                for (auto it = env.rbegin(); it != env.rend(); ++it) {
                    auto f = it->find(inst.text);
                    if (f != it->end()) { stack.push_back(f->second); found = true; break; }
                }
                if (!found)
                    throw std::runtime_error("Undefined variable: " + inst.text);
                break; }
            case OpCode::STORE_VAR:
                if (stack.empty()) throw std::runtime_error("Stack underflow");
                env.back()[inst.text] = stack.back();
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
            case OpCode::CALL: {
                auto it = functions.find(inst.text);
                if (it == functions.end()) throw std::runtime_error("Undefined function: " + inst.text);
                const Function& fn = it->second;
                if (inst.arg != (int)fn.params.size()) throw std::runtime_error("Arity mismatch in call to " + inst.text);
                std::unordered_map<std::string,int> frame;
                for (int i = inst.arg-1; i >= 0; --i) {
                    if (stack.empty()) throw std::runtime_error("Stack underflow");
                    frame[fn.params[i]] = stack.back();
                    stack.pop_back();
                }
                env.push_back(frame);
                callStack.push_back(ip);
                ip = fn.address - 1;
                break; }
            case OpCode::RET:
                if (callStack.empty()) return; // end of program
                env.pop_back();
                ip = callStack.back();
                callStack.pop_back();
                break;
            case OpCode::POP:
                if (stack.empty()) throw std::runtime_error("Stack underflow");
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
