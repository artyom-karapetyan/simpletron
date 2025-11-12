#include <iostream>
#include <simpletron.h>

void usage() {
}

int main() {
    try {
    }
    catch (const std::exception& e) {
        std::cout << "exception: " << e.what() << std::endl;
    }

    return 0;
}