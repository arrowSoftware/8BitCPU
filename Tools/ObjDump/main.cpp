#include "ObjDump.h"

#include <fstream>
#include <iostream>

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Usage: objdump [inputfile]" << std::endl;
        return -1;
    }

    std::ifstream inputFile(argv[1], std::ios::in | std::ios::binary);

    if (!inputFile.is_open()) {
        std::cerr << "Missing input file" << std::endl;
        return -1;
    }

    std::cout << "Dummping " << argv[1] << std::endl;
    objdump(inputFile);
    return 0;
}
