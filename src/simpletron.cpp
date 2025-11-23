#include <simpletron.h>
#include <operations.h>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <format>
#include <charconv>
#include <ranges>

// Uncomment to enable debug mode with advanced diagnostics
// #define DEBUG_MODE

/*
1. [x] Validate input between -9999 to 9999
2. [x] Check for overflow errors
3. [x] Check for invalid address
4. [ ] Improve dump_program
5. [x] *** Attempt to divide by zero ***
6. [x] *** Simpletron execution abnormally terminated ***
7. [x] Trim whitespaces
8. [x] Tests
9. [ ] Fix crash when invalid path is specified

*/

std::string& trim_left(std::string& s)
{
    s.erase(s.begin(), std::ranges::find_if(s, [](const unsigned char ch) noexcept {
                return std::isgraph(ch);
            }));

    return s;
}

std::string& trim_right(std::string& s)
{
    s.erase(std::ranges::find_if(std::ranges::reverse_view(s),
                                 [](const unsigned char ch) noexcept {
                                     return std::isgraph(ch);
                                 })
                .base(),
            s.end());

    return s;
}

std::string& trim(std::string& s)
{
    return trim_left(trim_right(s));
}

bool is_valid(const std::string& line) {
    return !line.empty();
}

void load_program(std::istream& prog, Memory& mem) {
    std::string line;

    while (std::getline(prog, line)) {
        trim(line);
        if (is_valid(line)) {
            short instruction = std::stoi(line);
            mem.push_back(instruction);    
        }
        line.clear();
    }
}

void load_program(std::string& prog, Memory& mem) {
    std::istringstream iss(prog);
    load_program(iss, mem);
}

void dump_program(std::ostream& os, const Memory& mem) {
    for (size_t idx = 0; idx < size(mem); ++idx) {
        os << std::showpos << std::setw(5) << std::setfill('0') << std::internal << mem[idx] << '\n';
    }
}

void decode(const short instruction, short& opcode, short& address) {
    opcode = instruction / 100;
    address = instruction % 100;
}


void validate_address(const Memory& mem, short address) {
    if (address < 0 || address >= static_cast<short>(mem.size())) {
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

void read_number(std::istream& input, short& num) {
    std::string str;
    input >> str;

    if (!input) {
        throw std::runtime_error("Stream error");
    }

    auto [ptr, ec] = std::from_chars(str.data(), str.data() + str.size(), num);

    if (ec == std::errc::invalid_argument) {
        throw std::invalid_argument(std::format("Invalid argument '{}'", ptr));
    } else if (ec == std::errc::result_out_of_range) {
        throw std::out_of_range(std::format("Value doesn't fit inside the type '{}'", typeid(num).name()));
    }
}

void check_overflows(const auto num) {
    if (num < -9999 || num > 9999) {
        throw std::out_of_range(std::format("Number {} is outside of range [-9999, 9999]", num));
    }
}

void debug(const short opcode, const short address, const Machine& machine) {

    constexpr std::string_view fmt = "{:>5} | {:5}| {:>4} | {:>4} | {:5}\n";
    static bool printed_caption = false;
    if (!printed_caption) {
        std::cout << std::format(fmt, "PTR", "INST", "ADDR", "VAL", "ACCUM");
        std::cout << "-----------------------------------" << '\n';
        printed_caption = true;
    }

    bool print_value = true;
    bool print_accum = true;

    if (opcode == BRANCH || opcode == BRANCHNEG || opcode == BRANCHZERO || opcode == HALT) { print_value = false; }
    if (opcode == HALT) { print_accum = false; }
    
    std::cout << std::format(fmt, 
        std::format("-> {:02d}", machine.instruction_ptr - &machine.mem[0]), 
        std::format("{}", opcode_to_str(opcode)),
        std::format("{:02d}", address),
        std::format("{}", print_value ? std::to_string(get_value(machine.mem, address)) : " "),
        std::format("[{:>4}]", (print_accum ? std::to_string(machine.accumulator) : ""))
    );
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

    short num{};
    int val{};
    switch(opcode){
        case READ:
            read_number(input, num);
            check_overflows(num);
            get_value(mem, address) = num;
            break;
        case WRITE:
            output << get_value(mem, address);
            break;
        case LOAD:
            acm = get_value(mem, address);
            break;
        case STORE:
            get_value(mem, address) = acm;
            break;
        case ADD:
            acm += get_value(mem, address);
            check_overflows(acm);
            break;
        case SUBTRACT:
            acm -= get_value(mem, address);
            check_overflows(acm);
            break;
        case DIVIDE:
            if (get_value(mem, address) == 0) {
                throw std::runtime_error("Attempt to divide by zero");
            }
            acm /= get_value(mem, address);
            break;
        case MULTIPLY:
            val = static_cast<int>(acm) * static_cast<int>(get_value(mem, address));
            check_overflows(val);
            acm = static_cast<short>(val);
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

#ifdef DEBUG_MODE
    debug(opcode, address, machine);
    if (branched) {
        std::cout << '\n';
    }
#endif

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

void run_simpletron(std::istream& prog, std::istream& input, std::ostream& output) {
    /*
    1. Initialize machine - DONE
    2. Load program into memory - DONE
    3. Start execution
    */
    Machine machine;
    load_program(prog, machine.mem);

    run_program(machine, input, output);
}

std::string run_simpletron(std::string_view progsv, std::string_view inputsv)
{
    std::istringstream prog(std::string{progsv});
    std::istringstream input(std::string{inputsv});
    std::ostringstream output;
    
    run_simpletron(prog, input, output);
    std::string out = output.str();
    trim(out);
    return out;
}