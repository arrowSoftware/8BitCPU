#include "Assembler.h"

#include <fstream>
#include <iostream>

int main(int argc, char **argv) {
    std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        std::cerr << "Missing input file" << std::endl;
        return -1;
    }
    std::cout << "Assembling " << argv[1] << std::endl;
    outputCompiledCode(assemble(inputFile));
    return 0;
}
