#include "ObjDump.h"

#include <string>
#include <iostream>
#include <iomanip>
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

    for (size_t i = 0; i < contents.size(); i++) {
        Instructions_t instruction = (Instructions_t)(contents.at(i)&0xFF);
        int instructionSize = getInstructionSize(instruction);
        if (instructionSize == 2) {
            int operand = (contents.at(i+1) & 0xFF);
            dissembledCode.push_back({(int)i, instruction, getInstructionStr(instruction), true, operand, ""});
            i++;
        } else if (instruction == 1) {
            dissembledCode.push_back({(int)i, instruction, getInstructionStr(instruction), false, 0, ""});
        } else {
            std::stringstream label;
            label << "var" << ++labelCount;
            labels.push_back({(int)i, label.str()});
            label << ": DB";
            dissembledCode.push_back({(int)i, DB, label.str(), true, (contents.at(i)&0xFF), ""});
        }
    }

    for (size_t i = 0; i < dissembledCode.size(); i++) {
        if (dissembledCode.at(i).hasOperand) {
            if (isAddressInstruction(dissembledCode.at(i).instruction)) {
                std::vector<Label_t>::iterator it = std::find_if(labels.begin(), labels.end(), [&cm = dissembledCode.at(i).operand](const Label_t& m) -> bool { return cm == m.address; });
                if (it != labels.end()) {
                    dissembledCode.at(i).addressOperand = it->name;
                } else {
                    for (size_t j = 0; j < dissembledCode.size(); j++) {
                        if (dissembledCode.at(i).operand == dissembledCode.at(j).address) {
                            std::stringstream label2;
                            label2 << "label" << ++otherLabelCount;
                            dissembledCode.at(i).addressOperand = label2.str();
                            CodeLine_t temp = {0, LABEL, label2.str(), false, 0, ""};
                            dissembledCode.insert(dissembledCode.begin()+j, temp);
                            i++;
                            break;
                        }
                    }
                }
            }
        }
    }


    std::ofstream asmFile("a.asm");

    for (size_t i = 0; i < dissembledCode.size(); i++) {
        if (dissembledCode.at(i).instruction == LABEL) {
            std::cout << dissembledCode.at(i).instructionStr << ":" << std::endl;
            asmFile << dissembledCode.at(i).instructionStr << ":" << std::endl;
            continue;
        }

        if (dissembledCode.at(i).hasOperand) {
            if (isAddressInstruction(dissembledCode.at(i).instruction)) {
                std::vector<Label_t>::iterator it = std::find_if(labels.begin(), labels.end(), [&cm = dissembledCode.at(i).operand](const Label_t& m) -> bool { return cm == m.address; });
                if (it != labels.end()) {
                    std::cout << "    " << dissembledCode.at(i).instructionStr << " [" << it->name << "]" << std::endl;
                    asmFile << "    " << dissembledCode.at(i).instructionStr << " [" << it->name << "]" << std::endl;
                } else {
                    std::cout << "    " << dissembledCode.at(i).instructionStr << " [" << dissembledCode.at(i).addressOperand << "]" << std::endl;
                    asmFile << "    " << dissembledCode.at(i).instructionStr << " [" << dissembledCode.at(i).addressOperand << "]" << std::endl;
                }
            } else {
                if (dissembledCode.at(i).instruction != DB) {
                    std::cout << "    ";
                    asmFile << "    ";
                }
                std::cout << dissembledCode.at(i).instructionStr << " " << std::setw(2) << std::setfill('0') << "0x" << dissembledCode.at(i).operand << std::endl;
                asmFile << dissembledCode.at(i).instructionStr << " " << std::setw(2) << std::setfill('0') << "0x" << dissembledCode.at(i).operand << std::endl;
            }
        } else {
            std::cout << "    " << dissembledCode.at(i).instructionStr << std::endl;
            asmFile << "    " << dissembledCode.at(i).instructionStr << std::endl;
        }
    }
}