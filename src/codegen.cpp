#include "codegen.hpp"
#include <cstring>

namespace ahlelele {

Bytecode CodeGenerator::generate(const Program& program) {
    bytecode_.clear();
    
    for (const auto& instruction : program) {
        if (instruction.type == InstructionType::PUSH) {
            emit_byte(static_cast<uint8_t>(OpCode::PUSH));
            emit_int64(instruction.value);
        } else if (instruction.type == InstructionType::EXECUTE) {
            emit_byte(static_cast<uint8_t>(instruction.value));
        }
    }
    
    emit_byte(static_cast<uint8_t>(OpCode::HALT));
    
    return bytecode_;
}

void CodeGenerator::emit_byte(uint8_t byte) {
    bytecode_.push_back(byte);
}

void CodeGenerator::emit_int64(int64_t value) {
    const auto* bytes = reinterpret_cast<const uint8_t*>(&value);
    for (size_t i = 0; i < sizeof(int64_t); ++i) {
        bytecode_.push_back(bytes[i]);
    }
}

}

