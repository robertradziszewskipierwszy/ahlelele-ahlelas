#pragma once

#include <string>
#include <filesystem>
#include <vector>
#include <cstdint>

namespace ahlelele {

class Compiler {
public:
    bool compile(const std::filesystem::path& input_path,
                 const std::filesystem::path& output_path);

private:
    std::string read_source_file(const std::filesystem::path& path);
    void write_executable(const std::filesystem::path& path,
                         const std::vector<uint8_t>& bytecode);
};

}

