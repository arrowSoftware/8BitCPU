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
    int referenceCount;
} CodeLabel_t;

struct find_name {
    std::string name;
    find_name(std::string name) : name(name) {}
    bool operator()(CodeLabel_t const &c) const {
        return c.name == name;
    }
};

std::vector<CompiledLine_t> assemble(std::istream &asmfile);
void outputCompiledCode(std::vector<CompiledLine_t> compiledCode);

#endif // __Assembler_H__
