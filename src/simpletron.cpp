#include <simpletron.h>

#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>

/*
100 element array - memory
accumulator
instruction pointer
instruction set
input - *txt file* or string
simulator

User: 
*/

void trim_whitespaces(std::string& line) {

}

bool is_valid(const std::string& line) {
    return !line.empty();
}

void load_program(std::istream& prog, Memory& mem) {
    std::string line;

    while (std::getline(prog, line)) {
        trim_whitespaces(line);
        if (is_valid(line)) {
            short instruction = std::stoi(line);
            mem.push_back(instruction);    
        }
    }
}

void load_program(std::string& prog, Memory& mem) {
    std::istringstream iss(prog);
    load_program(prog, mem);
}

void dump_program(std::ostream& os, const Memory& mem) {
    for (int idx = 0; idx < size(mem); ++idx) {
        os << std::showpos << std::setw(5) << std::setfill('0') << std::internal << mem[idx] << '\n';
    }
}

bool run_program(Machine& machine, std::istream& input, std::ostream& output) {
    return true;
}

bool run_simpletron(std::istream& prog, std::istream& input, std::ostream& output) {
    /*
    1. Initialize machine - DONE
    2. Load program into memory
    3. Start execution
    */
    Machine machine;
    load_program(prog, machine.mem);

    return run_program(machine, input, output);
}