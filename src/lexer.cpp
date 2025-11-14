#include "lexer.hpp"
#include <cctype>
#include <stdexcept>

namespace ahlelele {

Lexer::Lexer(std::string source)
    : source_{std::move(source)}
    , position_{0}
    , line_{1}
    , column_{1}
{}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;
    
    while (!is_at_end()) {
        skip_whitespace();
        
        if (is_at_end()) {
            break;
        }
        
        if (current_char() == '#') {
            skip_comment();
            continue;
        }
        
        auto token = next_token();
        if (token) {
            tokens.push_back(*token);
        }
    }
    
    tokens.emplace_back(TokenType::END_OF_FILE, line_, column_);
    return tokens;
}

std::optional<Token> Lexer::next_token() {
    const size_t start_line = line_;
    const size_t start_column = column_;
    
    if (std::isdigit(current_char()) || current_char() == '-') {
        auto number = parse_number();
        if (number) {
            return Token{TokenType::NUMBER, *number, start_line, start_column};
        }
        return std::nullopt;
    }
    
    if (std::isalpha(current_char())) {
        std::string word;
        while (!is_at_end() && std::isalpha(current_char())) {
            word += current_char();
            advance();
        }
        
        if (word == "ahlelele") {
            return Token{TokenType::AHLELELE, start_line, start_column};
        }
        if (word == "ahlelas") {
            return Token{TokenType::AHLELAS, start_line, start_column};
        }
        
        throw std::runtime_error{
            "Unknown keyword '" + word + "' at line " + 
            std::to_string(start_line) + ", column " + 
            std::to_string(start_column)
        };
    }
    
    throw std::runtime_error{
        "Unexpected character '" + std::string(1, current_char()) + 
        "' at line " + std::to_string(start_line) + 
        ", column " + std::to_string(start_column)
    };
}

void Lexer::skip_whitespace() {
    while (!is_at_end() && std::isspace(current_char())) {
        advance();
    }
}

void Lexer::skip_comment() {
    while (!is_at_end() && current_char() != '\n') {
        advance();
    }
}

std::optional<int64_t> Lexer::parse_number() {
    std::string number_str;
    
    if (current_char() == '-') {
        number_str += current_char();
        advance();
    }
    
    if (is_at_end() || !std::isdigit(current_char())) {
        return std::nullopt;
    }
    
    while (!is_at_end() && std::isdigit(current_char())) {
        number_str += current_char();
        advance();
    }
    
    return std::stoll(number_str);
}

char Lexer::current_char() const {
    if (is_at_end()) {
        return '\0';
    }
    return source_[position_];
}

char Lexer::peek_char() const {
    if (position_ + 1 >= source_.size()) {
        return '\0';
    }
    return source_[position_ + 1];
}

void Lexer::advance() {
    if (is_at_end()) {
        return;
    }
    
    if (current_char() == '\n') {
        ++line_;
        column_ = 1;
    } else {
        ++column_;
    }
    
    ++position_;
}

bool Lexer::is_at_end() const {
    return position_ >= source_.size();
}

}

