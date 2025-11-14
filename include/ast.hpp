#pragma once

#include <cstdint>
#include <vector>
#include <memory>

namespace ahlelele {

enum class InstructionType : uint8_t {
    PUSH,
    EXECUTE
};

struct Instruction {
    InstructionType type;
    int64_t value;

    Instruction(InstructionType t, int64_t v)
        : type{t}, value{v} {}
};

using Program = std::vector<Instruction>;

}

