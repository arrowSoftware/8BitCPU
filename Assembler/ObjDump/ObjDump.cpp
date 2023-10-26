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
    std::string addressOperand;
} CodeLine_t;

typedef struct Label {
    int address;
    std::string name;
} Label_t;

void objdump(std::istream &binfile) {
    std::vector<uint8_t> contents;
    std::vector<CodeLine_t> dissembledCode;
    std::vector<Label_t> labels;
    int labelCount = 0;
    int otherLabelCount = 0;
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
            dissembledCode.push_back({i, instruction, getInstructionStr(instruction), true, operand, ""});
            i++;
        } else if (instruction == 1) {
            dissembledCode.push_back({i, instruction, getInstructionStr(instruction), false, 0, ""});
        } else {
            std::stringstream label;
            label << "var" << ++labelCount;
            labels.push_back({i, label.str()});
            label << ": DB";
            dissembledCode.push_back({i, DB, label.str(), true, (contents.at(i)&0xFF), ""});
        }
    }

    for (int i = 0; i < dissembledCode.size(); i++) {
        if (dissembledCode.at(i).hasOperand) {
            if (isAddressInstruction(dissembledCode.at(i).instruction)) {
                std::vector<Label_t>::iterator it = std::find_if(labels.begin(), labels.end(), [&cm = dissembledCode.at(i).operand](const Label_t& m) -> bool { return cm == m.address; }); 
                if (it != labels.end()) {
                    dissembledCode.at(i).addressOperand = it->name;
                } else {
                    for (int carl = 0; carl < dissembledCode.size(); carl++) {
                        if (dissembledCode.at(i).operand == dissembledCode.at(carl).address) {
                            std::stringstream label2;
                            label2 << "label" << ++otherLabelCount;
//                            labels.push_back({i, label.str()});
                            dissembledCode.at(i).addressOperand = label2.str();
                            CodeLine_t temp = {0, LABEL, label2.str(), false, 0, ""};
                            dissembledCode.insert(dissembledCode.begin()+carl, temp);
                            i++;
                            break;
                        }
                    }
                }
            }
        }
//        std::cout << std::hex << std::uppercase << dissembledCode.at(i).address << ": " 
//                  << dissembledCode.at(i).instructionStr << " " 
//                  << std::hex << std::uppercase << dissembledCode.at(i).operand << std::endl;
    }


    for (int i = 0; i < dissembledCode.size(); i++) {
        if (dissembledCode.at(i).instruction == LABEL) {
            printf("%s:\n", dissembledCode.at(i).addressOperand.c_str());
        }

        if (dissembledCode.at(i).hasOperand) {
            if (isAddressInstruction(dissembledCode.at(i).instruction)) {
                std::vector<Label_t>::iterator it = std::find_if(labels.begin(), labels.end(), [&cm = dissembledCode.at(i).operand](const Label_t& m) -> bool { return cm == m.address; }); 
                if (it != labels.end()) {
                    printf("%02X: %s [%s]\n", dissembledCode.at(i).address, dissembledCode.at(i).instructionStr.c_str(), it->name.c_str());
                } else {
                    printf("%02X: %s [%s]\n", dissembledCode.at(i).address, dissembledCode.at(i).instructionStr.c_str(), dissembledCode.at(i).addressOperand.c_str());
                }
            } else {
                printf("%02X: %s %02X\n", dissembledCode.at(i).address, dissembledCode.at(i).instructionStr.c_str(), dissembledCode.at(i).operand);
            }
        } else {
            printf("%02X: %s\n", dissembledCode.at(i).address, dissembledCode.at(i).instructionStr.c_str());
        }
    }
}


/*
00: LDA 00
02: STA [var1]
04: OUT [var1]
06: LDA 01
08: STA [var2]
0A: OUT [var2]
0C: LDA [var1]
0E: ADD [var2]
10: STB [var1]
12: STA [var2]
14: JPC [todo]
16: JMP [todo]
18: HLT
19: var1: DB 00
1A: var2: DB 00
*/