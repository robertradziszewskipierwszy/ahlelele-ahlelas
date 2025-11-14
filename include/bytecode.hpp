#pragma once

#include <cstdint>
#include <vector>

namespace ahlelele {

enum class OpCode : uint8_t {
    PRINT_CHAR = 0,
    PRINT_NUM = 1,
    ADD = 2,
    SUB = 3,
    MUL = 4,
    DIV = 5,
    DUP = 6,
    SWAP = 7,
    DROP = 8,
    HALT = 9,
    PUSH = 255
};

using Bytecode = std::vector<uint8_t>;

}

