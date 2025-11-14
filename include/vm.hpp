#pragma once

#include "bytecode.hpp"
#include <vector>
#include <cstdint>

namespace ahlelele {

class VirtualMachine {
public:
    void execute(const Bytecode& bytecode);

private:
    void push(int64_t value);
    int64_t pop();
    int64_t peek() const;
    
    uint8_t read_byte();
    int64_t read_int64();

    std::vector<int64_t> stack_;
    const uint8_t* instruction_pointer_;
    const uint8_t* bytecode_end_;
};

}

