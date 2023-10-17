#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <iomanip>

#include "Instructions.h"

std::string trim(const std::string& str,
                 const std::string& whitespace = " \t")
{
    const auto strBegin = str.find_first_not_of(whitespace);
    if (strBegin == std::string::npos)
        return ""; // no content

    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}

std::string reduce(const std::string& str,
                   const std::string& fill = " ",
                   const std::string& whitespace = " \t")
{
    // trim first
    auto result = trim(str, whitespace);

    // replace sub ranges
    auto beginSpace = result.find_first_of(whitespace);
    while (beginSpace != std::string::npos)
    {
        const auto endSpace = result.find_first_not_of(whitespace, beginSpace);
        const auto range = endSpace - beginSpace;

        result.replace(beginSpace, range, fill);

        const auto newStart = beginSpace + fill.length();
        beginSpace = result.find_first_of(whitespace, newStart);
    }

    return result;
}

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
} CompiledLine_t;

typedef struct CodeLabel {
    int lineNumber;
    int address;
    std::string name;
} CodeLabel_t;

int main(int argc, char **argv) {
    printf("Assembling %s\n", argv[1]);

    std::ifstream asmfile(argv[1]);
    std::string line;
    std::vector<CodeLine_t> rawCode;
    int lineNumber = 1;
    std::vector<CodeLabel_t> labels;
    std::vector<CompiledLine_t> compiledLine;

    // Read entire file into memory
    while (std::getline(asmfile, line)) {
        if (line != "") {
            rawCode.push_back({lineNumber, reduce(line), {}});
        }
        lineNumber++;
    }

    std::vector<CodeLine_t>::iterator it = rawCode.begin();
    std::string temp;
    int currentAddress = 0;

    // tokenize each line of code.
    while (it != rawCode.end()) {
        std::stringstream ss(it->line);
        while(std::getline(ss, temp, ' ')) {
            it->tokens.push_back(temp);
        }

        for (int i = 0; i < it->tokens.size(); i++) {
            // Gather the labels.
            if (it->tokens.at(i).find(":") != std::string::npos) {
                labels.push_back({it->lineNumber, currentAddress, it->tokens.at(i).substr(0, it->tokens.at(i).find(":"))});
            }

            if ((it->tokens.at(i) == "LDA") || (it->tokens.at(i) == "STA") ||
                (it->tokens.at(i) == "LDB") || (it->tokens.at(i) == "STB") ||
                (it->tokens.at(i) == "STB") || (it->tokens.at(i) == "ADD") ||
                (it->tokens.at(i) == "SUB") || (it->tokens.at(i) == "OUT") ||
                (it->tokens.at(i) == "JMP") || (it->tokens.at(i) == "JPZ") ||
                (it->tokens.at(i) == "JPC")) {

                if (it->tokens.size() < i+2) {
                    std::cout << "Error: Line " << it->lineNumber << " Operand missing - " << it->line << std::endl;
                    return -1;
                } else {
                    std::string operand = it->tokens.at(i+1);
                    compiledLine.push_back({currentAddress, getInstructionEnum(it->tokens.at(i), true), operand, 0, it->line});
                    currentAddress += getInstructionSize(getInstructionEnum(it->tokens.at(i), true));
                }
            } else if ((it->tokens.at(i) == "HLT") || (it->tokens.at(i) == "OUTA") || (it->tokens.at(i) == "OUTB")) {
                if (it->tokens.size() > i+1) {
                    std::cout << "Error: Line " << it->lineNumber << " Instruction " << it->tokens.at(i) << " does not support operands - " << it->line << std::endl;
                    return -1;
                }
                compiledLine.push_back({currentAddress, getInstructionEnum(it->tokens.at(i), false), "", 0, it->line});
                currentAddress += getInstructionSize(getInstructionEnum(it->tokens.at(i), false));
            } else if (it->tokens.at(i) == "DB") {
                if (it->tokens.size() < i+2) {
                    std::cout << "Error: Line " << it->lineNumber << " Missing variable initializer - " << it->line << std::endl;
                    return -1;
                }

                compiledLine.push_back({currentAddress, DB, it->tokens.at(i+1), std::stoi(it->tokens.at(i+1)), it->line});
                currentAddress++;
            }
        }
        
        ++it;
    }
 
    for (int i = 0; i < compiledLine.size(); i++) {
        std::cout << std::right << std::setw(3) << std::setfill(' ') << std::uppercase << std::hex << compiledLine.at(i).address << ":" << std::setw(6) << " ";

        if (compiledLine.at(i).instruction != DB) {
            std::cout << std::setw(2) << std::setfill('0') << std::uppercase << std::hex << compiledLine.at(i).instruction << " ";
        }

        for (int j = 0; j < labels.size(); j++) {
            if (compiledLine.at(i).rawOperand.find(labels.at(j).name) != std::string::npos) {
                compiledLine.at(i).operand = labels.at(j).address;
                break;
            }
        }

        if (compiledLine.at(i).rawOperand != "") {
            std::cout << std::setw(2) << std::setfill('0') << std::uppercase << std::hex << compiledLine.at(i).operand << " "  << std::setfill(' ') << std::setw(6) << " ";
            if (compiledLine.at(i).instruction == DB) {
                std::cout << "   ";
            }
        } else {
            std::cout << std::setfill(' ') << std::setw(9) << " ";
        }

        std::cout << compiledLine.at(i).rawCode << std::endl;
    }

    return 0;
}