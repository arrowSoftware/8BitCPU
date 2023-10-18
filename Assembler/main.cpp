#include "Assembler.h"

#include <fstream>

int main(int argc, char **argv) {
    std::ifstream inputFile(argv[1]);
    printf("Assembling %s\n", argv[1]);
    outputCompiledCode(assemble(inputFile));
}
