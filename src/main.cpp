#include <simpletron.h>
#include <iostream>
#include <fstream>

int main(int argc, char* argv[]) {
    try {
        std::string file_name = "input.txt";
        if (argc > 1) {
            file_name = argv[1];
        }
        std::ifstream program(file_name);

        if (!program) {
            std::cerr << "Failed to open input file: " << file_name << std::endl;
            return 1;
        }

        Machine machine;
        load_program(program, machine.mem);
        dump_program(std::cout, machine.mem);

        // std::string prog = R"(
        //     +1007
        //     +1008
        //     +2007
        //     +3008
        //     +2109
        //     +1109
        //     +4300
        //     +0000
        //     +0000
        //     +0000
        // )";

        // if (run_simpletron(program, std::cin, std::cout)) {
        //     std::cout << "Program executed succesfully.\n";
        // }
        // else {
        //     std::cout << "Failed to execute program.\n";
        // }
    }
    catch (const std::exception& e) {
        std::cout << "exception: " << e.what() << std::endl;
    }

    return 0;
}