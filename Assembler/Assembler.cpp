#include <fstream>
#include <map>
#include <iostream>
#include <iomanip>
#include <iterator>

#include "Assembler.h"

// TODO allow upper and lower case instructions

std::vector<CodeLabel_t> labels;

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

int parseNumber(std::string number) {
    if (number.substr(0,2) == "0x") {
        return std::stoi(number.substr(2, number.length()), nullptr, 16);
    } else if (number.substr(0, 2) == "0o") {
        return std::stoi(number.substr(2, number.length()), nullptr, 8);
    } else if (number[number.length()-1] == 'd') {
        return std::stoi(number.substr(0, number.length()-1), nullptr, 10);
    } else if (number[number.length()-1] == 'b') {
        return std::stoi(number.substr(0, number.length()-1), nullptr, 2);
    } else {
        return std::stoi(number, nullptr, 10);
    }

    return -1;
}

void outputCompiledCode(std::vector<CompiledLine_t> compiledCode) {
    std::ofstream hexFile("a.hex");
    std::ofstream binFile("a.bin",  std::ios::out | std::ios::binary);
    hexFile << "v2.0 raw" << std::endl;

    for (int i = 0; i < compiledCode.size(); i++) {
        std::cout << std::right << std::setw(3) << std::setfill(' ') << std::uppercase << std::hex << compiledCode.at(i).address << ":" << std::setw(6) << " ";

        if (compiledCode.at(i).instruction != DB) {
            std::cout << std::setw(2) << std::setfill('0') << std::uppercase << std::hex << compiledCode.at(i).instruction << " ";
            hexFile << std::setw(2) << std::setfill('0') << std::uppercase << std::hex << compiledCode.at(i).instruction << " ";
            binFile << static_cast<unsigned char>(compiledCode.at(i).instruction & 0xFF);
        }

        if (compiledCode.at(i).rawOperand != "") {
            std::cout << std::setw(2) << std::setfill('0') << std::uppercase << std::hex << compiledCode.at(i).operand << " "  << std::setfill(' ') << std::setw(6) << " ";
            hexFile << std::setw(2) << std::setfill('0') << std::uppercase << std::hex << compiledCode.at(i).operand << std::endl;
            binFile << static_cast<unsigned char>(compiledCode.at(i).operand & 0xFF);

            if (compiledCode.at(i).instruction == DB) {
                std::cout << "   ";
            }
        } else {
            std::cout << std::setfill(' ') << std::setw(9) << " ";
        }

        std::cout << compiledCode.at(i).rawCode << std::endl;
    }
}

std::vector<CompiledLine_t> assemble(std::istream &asmfile) {
    std::string line;
    std::vector<CodeLine_t> rawCode;
    int lineNumber = 1;
    std::vector<CompiledLine_t> compiledLine;
    labels.clear();

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
            if (temp.find(";") == std::string::npos) {
                it->tokens.push_back(temp);
            }
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
                    return {};
                } else {
                    std::string operand = it->tokens.at(i+1);
                    if (operand.find("[") != std::string::npos) {
                        compiledLine.push_back({currentAddress, getInstructionEnum(it->tokens.at(i), true), operand, 0, it->line, it->lineNumber});
                    } else {
                        int number = parseNumber(operand);
                        if (number == -1) {
                            std::cout << "Error: Line " << it->lineNumber << " Invalid number format - " << it->line << std::endl;
                            return {};
                        } else if (number > 255) {
                            std::cout << "Error: Line " << it->lineNumber << " Number '"<< number << "' exceeds 8 bit max 255 - " << it->line << std::endl;
                            return {};
                        }
                        compiledLine.push_back({currentAddress, getInstructionEnum(it->tokens.at(i), false), operand, parseNumber(operand), it->line, it->lineNumber});
                    }
                    currentAddress += getInstructionSize(getInstructionEnum(it->tokens.at(i), true));
                }
            } else if ((it->tokens.at(i) == "HLT") || (it->tokens.at(i) == "OUTA") || (it->tokens.at(i) == "OUTB") || (it->tokens.at(i) == "NOP")) {
                if (it->tokens.size() > i+1) {
                    std::cout << "Error: Line " << it->lineNumber << " Instruction " << it->tokens.at(i) << " does not support operands - " << it->line << std::endl;
                    return {};
                }
                compiledLine.push_back({currentAddress, getInstructionEnum(it->tokens.at(i), false), "", 0, it->line, it->lineNumber});
                currentAddress += getInstructionSize(getInstructionEnum(it->tokens.at(i), false));
            } else if (it->tokens.at(i) == "DB") {
                if (it->tokens.size() < i+2) {
                    std::cout << "Error: Line " << it->lineNumber << " Missing variable initializer - " << it->line << std::endl;
                    return {};
                }

                compiledLine.push_back({currentAddress, DB, it->tokens.at(i+1), std::stoi(it->tokens.at(i+1)), it->line, it->lineNumber});
                currentAddress++;
            }
        }

        ++it;
    }

    for (int i = 0; i < compiledLine.size(); i++) {
        for (int j = 0; j < labels.size(); j++) {
            if (compiledLine.at(i).rawOperand.find("[") != std::string::npos) {
                if (compiledLine.at(i).rawOperand.find(labels.at(j).name) != std::string::npos) {
                    compiledLine.at(i).operand = labels.at(j).address;
                    break;
                }

                // No labels found.
                if (j == labels.size() - 1) {
                    std::cout << "Error: Line " << compiledLine.at(i).lineNumber << " undefined reference to '" << compiledLine.at(i).rawOperand << "'" << std::endl;
                    return {};
                }
            }
        }
    }
    return compiledLine;
}

//int main(int argc, char **argv) {
//    std::ifstream inputFile(argv[1]);
//    printf("Assembling %s\n", argv[1]);
//    outputCompiledCode(assemble(inputFile));
//}
