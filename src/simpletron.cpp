#include <simpletron.h>

#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <format>

// Uncomment to enable debug mode with advanced diagnostics
#define DEBUG_MODE

// Input/output operations
const short READ       = 10;
const short WRITE      = 11;

// Load and store operations
const short LOAD       = 20;
const short STORE      = 21;

// Arithmetic operations
const short ADD        = 30;
const short SUBTRACT   = 31;
const short DIVIDE     = 32;
const short MULTIPLY   = 33;

// Transfer-of-control operations
const short BRANCH     = 40;
const short BRANCHNEG  = 41;
const short BRANCHZERO = 42;

const short HALT       = 43;

std::string_view opcode_to_str(int opcode) {
    switch (opcode) {
        case READ:
            return "READ";
        case WRITE:
            return "WRTE";
        case LOAD:
            return "LOAD";
        case STORE:
            return "STRE";
        case ADD:
            return "ADD ";
        case SUBTRACT:
            return "SUBT";
        case DIVIDE:
            return "DIVI";
        case MULTIPLY:
            return "MULT";
        case BRANCH:
            return "BRAN";
        case BRANCHNEG:
            return "BRNG";
        case BRANCHZERO:
            return "BRZE";
        case HALT:
            return "HALT";
        default:
            return "????";
    }
}

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

void decode(const short instruction, short& opcode, short& address) {
    opcode = instruction / 100;
    address = instruction % 100;
}


void validate_address(const Memory& mem, short address) {
    if (address < 0 || address >= mem.size()) {
        throw std::runtime_error(
            std::string("Attempt to access memory at invalid address: ") + 
            std::to_string(address));
    }
}

const short& get_value(const Memory& mem, short address) {
    validate_address(mem, address);
    return mem[address];
}

short& get_value(Memory& mem, short address) {
    validate_address(mem, address);
    return mem[address];
}

void debug(const short opcode, const short address, const Machine& machine) {

    static int print_caption = []() {
        std::cout << "  PTR | INST | ADDR | VAL | ACCUM " << std::endl;
        std::cout << "----------------------------------" << std::endl;
        return 0;
    }();

    // std::string val = std::to_string(get_value(machine.mem, address));
    bool print_value = true;
    bool print_accum = true;

    if (opcode == BRANCH || opcode == BRANCHNEG || opcode == BRANCHZERO || opcode == HALT) { print_value = false; }
    if (opcode == HALT) { print_accum = false; }
    
    std::cout << "-> " << std::setw(2) << std::setfill('0') << machine.instruction_ptr - &machine.mem[0]
              << "   " << std::setw(4) << opcode_to_str(opcode)
              << "     " << std::setw(2) << address
              << "  " << std::setw(4) << std::setfill(' ');
    
    if (print_value)  {
        std::cout << get_value(machine.mem, address);
    }
    else {
        std::cout << " ";
    }

    if (print_accum) {
        std::cout << "   [" << std::setw(4) << machine.accumulator << "]";
    }
    std::cout << '\n';
}

bool execute(Machine& machine, 
             const short opcode, 
             const short address, 
             std::istream& input, 
             std::ostream& output) {
    auto& acm = machine.accumulator;
    auto& mem = machine.mem;
    auto& ptr = machine.instruction_ptr;
    bool branched = false;

#ifdef DEBUG_MODE
    debug(opcode, address, machine);
#endif

    short num{};
    short val{};
    switch(opcode){
        case READ:
            input >> num;
            get_value(mem, address) = num;
            break;
        case WRITE:
            output << get_value(mem, address) << '\n';
            break;
        case LOAD:
            acm = get_value(mem, address);
            break;
        case STORE:
            get_value(mem, address) = acm;
            break;
        case ADD:
            acm += get_value(mem, address);
            break;
        case SUBTRACT:
            acm -= get_value(mem, address);
            break;
        case DIVIDE:
            if (get_value(mem, address) == 0) {return false;}
            acm /= get_value(mem, address);
            break;
        case MULTIPLY:
            acm *= get_value(mem, address);
            break;
        case BRANCH:
            ptr = &get_value(mem, address);
            branched = true; 
            break;
        case BRANCHNEG:
            if (acm < 0) {
                ptr = &get_value(mem, address);
                branched = true; 
            }
            break;
        case BRANCHZERO:
            if (acm == 0) {
                ptr = &get_value(mem, address);
                branched = true; 
            }
            break;
        case HALT:
            break;
    }

    if (!branched) {
        ++ptr;
    }
    
    return true;
}

bool run_program(Machine& machine, std::istream& input, std::ostream& output) {
    machine.instruction_ptr = &(machine.mem[0]);
    short opcode{};
    short address{};

    while (true) {
        short instruction = (*machine.instruction_ptr);
        
        decode(instruction, opcode, address);
        if (!execute(machine, opcode, address, input, output)) {
            return false;
        }

        if (opcode == HALT) {
            break;
        }
    }
    
    return true;
}

bool run_simpletron(std::istream& prog, std::istream& input, std::ostream& output) {
    /*
    1. Initialize machine - DONE
    2. Load program into memory - DONE
    3. Start execution
    */
    Machine machine;
    load_program(prog, machine.mem);

    return run_program(machine, input, output);
}