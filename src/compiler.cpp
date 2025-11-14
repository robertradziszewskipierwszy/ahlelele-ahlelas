#include "compiler.hpp"
#include "lexer.hpp"
#include "parser.hpp"
#include "codegen.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iostream>

namespace ahlelele {

bool Compiler::compile(const std::filesystem::path& input_path,
                       const std::filesystem::path& output_path) {
    try {
        const std::string source = read_source_file(input_path);
        
        Lexer lexer{source};
        const auto tokens = lexer.tokenize();
        
        Parser parser{tokens};
        const auto program = parser.parse();
        
        CodeGenerator codegen;
        const auto bytecode = codegen.generate(program);
        
        write_executable(output_path, bytecode);
        
        return true;
        
    } catch (const std::exception& e) {
        std::cerr << "Compilation error: " << e.what() << '\n';
        return false;
    }
}

std::string Compiler::read_source_file(const std::filesystem::path& path) {
    std::ifstream file{path, std::ios::binary};
    
    if (!file) {
        throw std::runtime_error{
            "Cannot open source file: " + path.string()
        };
    }
    
    std::ostringstream buffer;
    buffer << file.rdbuf();
    
    return buffer.str();
}

void Compiler::write_executable(const std::filesystem::path& path,
                                const std::vector<uint8_t>& bytecode) {
    std::ofstream file{path, std::ios::binary};
    
    if (!file) {
        throw std::runtime_error{
            "Cannot create output file: " + path.string()
        };
    }
    
    constexpr uint32_t magic_number = 0x414C4841;
    file.write(reinterpret_cast<const char*>(&magic_number), sizeof(magic_number));
    
    const uint64_t bytecode_size = bytecode.size();
    file.write(reinterpret_cast<const char*>(&bytecode_size), sizeof(bytecode_size));
    
    file.write(reinterpret_cast<const char*>(bytecode.data()), 
               static_cast<std::streamsize>(bytecode.size()));
}

}

