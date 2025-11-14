#include "vm.hpp"
#include <iostream>
#include <stdexcept>
#include <cstring>

namespace ahlelele {

void VirtualMachine::execute(const Bytecode& bytecode) {
    if (bytecode.empty()) {
        return;
    }
    
    instruction_pointer_ = bytecode.data();
    bytecode_end_ = bytecode.data() + bytecode.size();
    stack_.clear();
    
    bool running = true;
    
    while (running && instruction_pointer_ < bytecode_end_) {
        const auto opcode = static_cast<OpCode>(read_byte());
        
        switch (opcode) {
            case OpCode::PUSH: {
                const int64_t value = read_int64();
                push(value);
                break;
            }
            
            case OpCode::PRINT_CHAR: {
                const int64_t value = pop();
                std::cout << static_cast<char>(value);
                break;
            }
            
            case OpCode::PRINT_NUM: {
                const int64_t value = pop();
                std::cout << value;
                break;
            }
            
            case OpCode::ADD: {
                const int64_t b = pop();
                const int64_t a = pop();
                push(a + b);
                break;
            }
            
            case OpCode::SUB: {
                const int64_t b = pop();
                const int64_t a = pop();
                push(a - b);
                break;
            }
            
            case OpCode::MUL: {
                const int64_t b = pop();
                const int64_t a = pop();
                push(a * b);
                break;
            }
            
            case OpCode::DIV: {
                const int64_t b = pop();
                const int64_t a = pop();
                if (b == 0) {
                    throw std::runtime_error{"Division by zero"};
                }
                push(a / b);
                break;
            }
            
            case OpCode::DUP: {
                const int64_t value = peek();
                push(value);
                break;
            }
            
            case OpCode::SWAP: {
                if (stack_.size() < 2) {
                    throw std::runtime_error{"Stack underflow on SWAP"};
                }
                const int64_t a = pop();
                const int64_t b = pop();
                push(a);
                push(b);
                break;
            }
            
            case OpCode::DROP: {
                pop();
                break;
            }
            
            case OpCode::HALT: {
                running = false;
                break;
            }
            
            default:
                throw std::runtime_error{
                    "Unknown opcode: " + std::to_string(static_cast<int>(opcode))
                };
        }
    }
}

void VirtualMachine::push(int64_t value) {
    stack_.push_back(value);
}

int64_t VirtualMachine::pop() {
    if (stack_.empty()) {
        throw std::runtime_error{"Stack underflow"};
    }
    const int64_t value = stack_.back();
    stack_.pop_back();
    return value;
}

int64_t VirtualMachine::peek() const {
    if (stack_.empty()) {
        throw std::runtime_error{"Stack underflow"};
    }
    return stack_.back();
}

uint8_t VirtualMachine::read_byte() {
    if (instruction_pointer_ >= bytecode_end_) {
        throw std::runtime_error{"Unexpected end of bytecode"};
    }
    return *instruction_pointer_++;
}

int64_t VirtualMachine::read_int64() {
    if (instruction_pointer_ + sizeof(int64_t) > bytecode_end_) {
        throw std::runtime_error{"Unexpected end of bytecode"};
    }
    
    int64_t value;
    std::memcpy(&value, instruction_pointer_, sizeof(int64_t));
    instruction_pointer_ += sizeof(int64_t);
    
    return value;
}

}

