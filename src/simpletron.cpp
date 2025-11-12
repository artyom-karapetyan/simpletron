#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
/*
100 element array - memory
accumulator
instruction pointer
instruction set
input - *txt file* or string
simulator

User: 

*/

bool run_simpletron(std::istream& prog, std::istream& input, std::ostream& out) {
    return false;
}

void usage() {
    std::string file_name;
    std::ifstream program(file_name);

    if (run_simpletron(program, std::cin, std::cout)) {
        std::cout << "Program executed succesfully.\n";
    }
    else {
        std::cout << "Failed to execute program.\n";
    }
}

void test_case(const std::string& prog, const std::string& in, const std::string& out, bool result) {
    std::istringstream program(prog);
    std::istringstream input(in);
    std::ostringstream output;

    bool res = run_simpletron(program, input, output);

    // 1. ensure res is true
    // 2. ensure out equal to output.str();
    // ASSERT_EQ(result, res);
    // EXEPCT_EQ(out, output.str());
}

void test() {
    test_case("code", "1 2", "3", true);
    test_case("code", "2", "", false);
    test_case("code", "2", "", false);
}