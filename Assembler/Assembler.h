#ifndef __Assembler_H__
#define __Assembler_H__

#include <sstream>
#include <vector>
#include <string>

#include "Instructions.h"

typedef struct CodeLine {
    int lineNumber;
    std::string line;
    std::vector<std::string> tokens;
} CodeLine_t;

typedef struct CompiledLine {
    int address;
    Instructions_t instruction;
    std::string rawOperand;
    int operand;
    std::string rawCode;
    int lineNumber;
} CompiledLine_t;

typedef struct CodeLabel {
    int lineNumber;
    int address;
    std::string name;
} CodeLabel_t;

std::vector<CompiledLine_t> assemble(std::istream &asmfile);
void outputCompiledCode(std::vector<CompiledLine_t> compiledCode);

#endif // __Assembler_H__
