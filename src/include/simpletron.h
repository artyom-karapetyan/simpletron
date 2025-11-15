#pragma once

#include <iosfwd>
#include <vector>

using Memory = std::vector<short>;

struct Machine {
    Memory mem{};
    short* instruction_ptr{nullptr};
    int accumulator{};
};

void load_program(std::istream& prog, Memory& mem);

void dump_program(std::ostream& os, const Memory& mem);

bool run_simpletron(std::istream& prog, std::istream& input, std::ostream& output);
