#include "ObjDump.h"

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <iterator>

#include "Instructions.h"

typedef struct CodeLine {
    int address;
    Instructions_t instruction;
    std::string instructionStr;
    bool hasOperand;
    int operand;
} CodeLine_t;

void objdump(std::istream &binfile) {
    std::vector<uint8_t> contents;
    std::vector<CodeLine_t> dissembledCode;
    int labelCount = 0;
    binfile.unsetf(std::ios::skipws);
    binfile.seekg(0, std::ios_base::end);
    size_t fileSize = binfile.tellg();
    binfile.seekg(0, std::ios_base::beg);
    contents.resize(0);
    contents.reserve(0);
    contents.shrink_to_fit();
    contents.reserve(fileSize);
    contents.insert(contents.begin(), std::istream_iterator<uint8_t>(binfile), std::istream_iterator<uint8_t>());

    for (int i = 0; i < contents.size(); i++) {
        Instructions_t instruction = (Instructions_t)(contents.at(i)&0xFF);
        int instructionSize = getInstructionSize(instruction);
        if (instructionSize == 2) {
            int operand = (contents.at(i+1) & 0xFF);
            dissembledCode.push_back({i, instruction, getInstructionStr(instruction), true, operand});
            i++;
        } else if (instruction == 1) {
            dissembledCode.push_back({i, instruction, getInstructionStr(instruction), false, 0});
        } else {
            std::stringstream label;
            label << "var" << ++labelCount << ": DB";
            dissembledCode.push_back({i, DB, label.str(), true, (contents.at(i)&0xFF)});
        }
    }

    for (int i = 0; i < dissembledCode.size(); i++) {
        if (dissembledCode.at(i).hasOperand) {
            printf("%02X: %s %02X\n", dissembledCode.at(i).address, dissembledCode.at(i).instructionStr.c_str(), dissembledCode.at(i).operand);
        } else {
            printf("%02X: %s\n", dissembledCode.at(i).address, dissembledCode.at(i).instructionStr.c_str());
        }
//        std::cout << std::hex << std::uppercase << dissembledCode.at(i).address << ": " 
//                  << dissembledCode.at(i).instructionStr << " " 
//                  << std::hex << std::uppercase << dissembledCode.at(i).operand << std::endl;
    }
}