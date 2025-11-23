#include <simpletron.h>
#include <iostream>
#include <fstream>
#include <sstream>

int main(int argc, char* argv[]) {
    try {
        std::string file_name = "input.sml";
        if (argc > 1) {
            file_name = argv[1];
        }
        std::ifstream program(file_name);

        if (!program) {
            std::cerr << "Failed to open input file: " << file_name << std::endl;
            return 1;
        }

        Machine machine;
        //load_program(program, machine.mem);
        //dump_program(std::cout, machine.mem);

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
        std::istringstream iss("5 0");

        run_simpletron(program, iss, std::cout);
    }
    catch (const std::exception& e) {
        std::cout << "*** " << e.what() << " ***\n";
        std::cout << "*** Simpletron execution abnormally terminated ***" << std::endl;
    }

    return 0;
}

