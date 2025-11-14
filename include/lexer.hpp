#pragma once

#include "token.hpp"
#include <string>
#include <vector>
#include <optional>

namespace ahlelele {

class Lexer {
public:
    explicit Lexer(std::string source);
    
    std::vector<Token> tokenize();

private:
    std::optional<Token> next_token();
    void skip_whitespace();
    void skip_comment();
    std::optional<int64_t> parse_number();
    
    char current_char() const;
    char peek_char() const;
    void advance();
    bool is_at_end() const;

    std::string source_;
    size_t position_;
    size_t line_;
    size_t column_;
};

}

