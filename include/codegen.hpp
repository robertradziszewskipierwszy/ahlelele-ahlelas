#pragma once

#include "ast.hpp"
#include "bytecode.hpp"

namespace ahlelele {

class CodeGenerator {
public:
    Bytecode generate(const Program& program);

private:
    void emit_byte(uint8_t byte);
    void emit_int64(int64_t value);

    Bytecode bytecode_;
};

}

