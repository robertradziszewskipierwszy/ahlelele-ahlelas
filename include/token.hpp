#pragma once

#include <cstdint>
#include <string>
#include <variant>

namespace ahlelele {

enum class TokenType : uint8_t {
    AHLELELE,
    AHLELAS,
    NUMBER,
    END_OF_FILE,
    INVALID
};

struct Token {
    TokenType type;
    std::variant<std::monostate, int64_t> value;
    size_t line;
    size_t column;

    Token(TokenType t, size_t l, size_t c)
        : type{t}, value{std::monostate{}}, line{l}, column{c} {}

    Token(TokenType t, int64_t v, size_t l, size_t c)
        : type{t}, value{v}, line{l}, column{c} {}
};

}

