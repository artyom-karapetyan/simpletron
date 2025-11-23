#pragma once

#include <iosfwd>
#include <vector>
#include <string_view>
#include <string>

using Memory = std::vector<short>;

struct Machine {
    Memory mem{};
    short* instruction_ptr{nullptr};
    int accumulator{};
};

std::string& trim_right(std::string& s);
std::string& trim_left(std::string& s);
std::string& trim(std::string& s);

void load_program(std::istream& prog, Memory& mem);

void dump_program(std::ostream& os, const Memory& mem);

void run_simpletron(std::istream& prog, std::istream& input, std::ostream& output);

std::string run_simpletron(std::string_view prog, std::string_view input);