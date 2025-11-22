#include <operations.h>

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
