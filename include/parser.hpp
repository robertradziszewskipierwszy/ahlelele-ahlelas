#pragma once

#include "token.hpp"
#include "ast.hpp"
#include <vector>
#include <optional>

namespace ahlelele {

class Parser {
public:
    explicit Parser(std::vector<Token> tokens);
    
    Program parse();

private:
    std::optional<Instruction> parse_instruction();
    
    const Token& current_token() const;
    const Token& peek_token() const;
    void advance();
    bool is_at_end() const;

    std::vector<Token> tokens_;
    size_t position_;
};

}

