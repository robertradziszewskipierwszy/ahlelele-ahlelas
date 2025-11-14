#include "compiler.hpp"
#include "vm.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <optional>
#include <vector>
#include <cstdint>

namespace {

struct Arguments {
    std::filesystem::path input_path;
    std::filesystem::path output_path;
    bool execute_mode{false};
};

void print_usage() {
    std::cout << "Ahlelele Ahlelas Compiler v1.0.0\n\n";
    std::cout << "Usage:\n";
    std::cout << "  Compile: ahlelele --in <source.ahl> --out <executable>\n";
    std::cout << "  Execute: ahlelele --exec <executable>\n";
    std::cout << "\nDescription:\n";
    std::cout << "  Compiles Ahlelele Ahlelas source code to bytecode executable\n";
    std::cout << "  or executes a compiled bytecode file.\n";
}

std::optional<Arguments> parse_arguments(int argc, char* argv[]) {
    if (argc < 3) {
        return std::nullopt;
    }
    
    Arguments args;
    
    for (int i = 1; i < argc; ++i) {
        const std::string arg{argv[i]};
        
        if (arg == "--in" && i + 1 < argc) {
            args.input_path = argv[++i];
        } else if (arg == "--out" && i + 1 < argc) {
            args.output_path = argv[++i];
        } else if (arg == "--exec" && i + 1 < argc) {
            args.input_path = argv[++i];
            args.execute_mode = true;
        } else if (arg == "--help" || arg == "-h") {
            return std::nullopt;
        }
    }
    
    if (args.execute_mode) {
        if (args.input_path.empty()) {
            return std::nullopt;
        }
        return args;
    }
    
    if (args.input_path.empty() || args.output_path.empty()) {
        return std::nullopt;
    }
    
    return args;
}

bool execute_bytecode(const std::filesystem::path& path) {
    std::ifstream file{path, std::ios::binary};
    
    if (!file) {
        std::cerr << "Cannot open executable file: " << path << '\n';
        return false;
    }
    
    uint32_t magic_number;
    file.read(reinterpret_cast<char*>(&magic_number), sizeof(magic_number));
    
    if (magic_number != 0x414C4841) {
        std::cerr << "Invalid executable file format\n";
        return false;
    }
    
    uint64_t bytecode_size;
    file.read(reinterpret_cast<char*>(&bytecode_size), sizeof(bytecode_size));
    
    std::vector<uint8_t> bytecode(bytecode_size);
    file.read(reinterpret_cast<char*>(bytecode.data()), 
              static_cast<std::streamsize>(bytecode_size));
    
    try {
        ahlelele::VirtualMachine vm;
        vm.execute(bytecode);
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Runtime error: " << e.what() << '\n';
        return false;
    }
}

}

int main(int argc, char* argv[]) {
    const auto args = parse_arguments(argc, argv);
    
    if (!args) {
        print_usage();
        return 1;
    }
    
    if (args->execute_mode) {
        return execute_bytecode(args->input_path) ? 0 : 1;
    }
    
    ahlelele::Compiler compiler;
    const bool success = compiler.compile(args->input_path, args->output_path);
    
    if (success) {
        std::cout << "Compilation successful: " << args->output_path << '\n';
        return 0;
    }
    
    return 1;
}

