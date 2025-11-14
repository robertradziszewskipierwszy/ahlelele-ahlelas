#include "parser.hpp"
#include <stdexcept>

namespace ahlelele {

Parser::Parser(std::vector<Token> tokens)
    : tokens_{std::move(tokens)}
    , position_{0}
{}

Program Parser::parse() {
    Program program;
    
    while (!is_at_end()) {
        if (current_token().type == TokenType::END_OF_FILE) {
            break;
        }
        
        auto instruction = parse_instruction();
        if (instruction) {
            program.push_back(*instruction);
        }
    }
    
    return program;
}

std::optional<Instruction> Parser::parse_instruction() {
    const Token& token = current_token();
    
    if (token.type == TokenType::AHLELELE) {
        advance();
        
        if (current_token().type != TokenType::NUMBER) {
            throw std::runtime_error{
                "Expected number after 'ahlelele' at line " + 
                std::to_string(token.line)
            };
        }
        
        const int64_t value = std::get<int64_t>(current_token().value);
        advance();
        
        return Instruction{InstructionType::PUSH, value};
    }
    
    if (token.type == TokenType::AHLELAS) {
        advance();
        
        if (current_token().type != TokenType::NUMBER) {
            throw std::runtime_error{
                "Expected number after 'ahlelas' at line " + 
                std::to_string(token.line)
            };
        }
        
        const int64_t value = std::get<int64_t>(current_token().value);
        advance();
        
        return Instruction{InstructionType::EXECUTE, value};
    }
    
    throw std::runtime_error{
        "Unexpected token at line " + std::to_string(token.line)
    };
}

const Token& Parser::current_token() const {
    return tokens_[position_];
}

const Token& Parser::peek_token() const {
    if (position_ + 1 >= tokens_.size()) {
        return tokens_.back();
    }
    return tokens_[position_ + 1];
}

void Parser::advance() {
    if (!is_at_end()) {
        ++position_;
    }
}

bool Parser::is_at_end() const {
    return position_ >= tokens_.size() || 
           current_token().type == TokenType::END_OF_FILE;
}

}

