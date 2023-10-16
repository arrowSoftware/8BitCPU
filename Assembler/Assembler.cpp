#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <iomanip>

#include "Instructions.h"

typedef struct CodeLine {
    Instructions_t instruction;
    std::string rawArgument;
    int convertedArgument;
    std::string code;
    int address;
} CodeLine_t;

typedef struct CodeLabel {
    std::string name;
    int lineNumber;
    int address;
} CodeLabel_t;

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

bool isOneByteInstruction(std::string instruction) {
    if (instruction == "NOP" || instruction == "HLT" || instruction == "OUTA" || instruction == "OUTB") {
        return true;
    }
    return false;
}

int main(int argc, char **argv) {
    printf("Assembling %s\n", argv[1]);
    std::ifstream asmfile(argv[1]);
    std::string line;
    int lineNumber = 0;
    int currentAddress = 0;
    std::vector<CodeLabel_t> labels;
    std::vector<CodeLine_t> code;
    std::vector<CodeLine_t> compiled;

    while (std::getline(asmfile, line)) {
        if (line != "") {
            std::string reduced = reduce(line);
            code.push_back({NOP, "", 0, reduced, currentAddress});
            if (reduced.find(":") != std::string::npos) {
                labels.push_back({reduced.substr(0, reduced.find(':')), lineNumber, 0});
            }
            printf("[*] %02X: %s\n", lineNumber, line.c_str());
            lineNumber++;
        }
    }

    std::vector<CodeLabel_t>::iterator label_it = labels.begin();
    while (label_it != labels.end())
    {
        printf("[*] Label @ %02X: %s\n", label_it->lineNumber, label_it->name.c_str());
        ++label_it;
    }

    std::vector<CodeLine_t>::iterator it = code.begin();
    while (it != code.end()) {
        std::string line = it->code;
        std::vector<std::string> tokens;
        std::istringstream iss(line);
        std::string temp;

        while (std::getline(iss, temp, ' ')) {
            tokens.push_back(temp);
        }

        std::string instruction = tokens.at(0);
        std::string argument;

        if ((instruction == "LDA") ||
            (instruction == "STA") ||
            (instruction == "OUT") ||
            (instruction == "ADD") ||
            (instruction == "STB") ||
            (instruction == "STA") ||
            (instruction == "JMP") ||
            (instruction == "JPC") ||
            (instruction == "JPZ")) {

            argument = tokens.at(1);
            it->rawArgument = argument;
            it->address = currentAddress;

            if (argument.find('[') != std::string::npos) {
                it->instruction = getInstructionEnum(instruction, true);
            } else {
                it->instruction = getInstructionEnum(instruction, false);
            }

            compiled.push_back({it->instruction, it->rawArgument, 0, line, it->address});
            currentAddress += getInstructionSize(it->instruction);
        } else if ((instruction == "HLT") || (instruction == "OUTA") || (instruction == "OUTB")) {
            it->instruction = getInstructionEnum(instruction, false);
            it->rawArgument = argument;
            it->address = currentAddress;
            compiled.push_back({it->instruction, it->rawArgument, 0, line, it->address});
            currentAddress += getInstructionSize(it->instruction);
        } else if (instruction.find(":") && tokens.size() > 1) {
            if (tokens.at(1) == "DB") {
                for (std::vector<CodeLabel_t>::iterator iter = labels.begin(); iter != labels.end(); ++iter) {
                    if (instruction.substr(0, instruction.find(":")) == iter->name) {
                        iter->address = currentAddress;
                        compiled.push_back({DB, tokens.at(2), std::stoi(tokens.at(2)), line, iter->address});
                        break;
                    }
                }

                currentAddress++;
            }
        } else if (instruction.find(":") && tokens.size() == 1) {
            for (std::vector<CodeLabel_t>::iterator iter = labels.begin(); iter != labels.end(); ++iter) {
                if (instruction.substr(0, instruction.find(":")) == iter->name) {
                    iter->address = currentAddress;
                    compiled.push_back({LABEL, "", 0, line, iter->address});
                    break;
                }
            }
        }

        ++it;
    }

    std::ofstream datafile("a.hex");
    datafile << "v2.0 raw" << std::endl;

    it = compiled.begin();
    while (it != compiled.end()) {
        if (it->instruction == LABEL) {
        } else if (it->instruction == DB) {
            std::cout << std::right << std::setw(3) << std::setfill(' ') << std::uppercase << std::hex << it->address << ":" << std::setw(6) << " ";
            std::cout << std::setw(2) << std::setfill('0') << std::uppercase << std::hex << it->convertedArgument << " "  << std::setfill(' ') << std::setw(9) << " ";
            std::cout << it->code << std::endl;

            datafile << std::setw(2) << std::setfill('0') << std::uppercase << std::hex << it->convertedArgument << std::endl;
        } else {
            for (std::vector<CodeLabel_t>::iterator iter = labels.begin(); iter != labels.end(); ++iter) {
                if (it->rawArgument.find("[") != std::string::npos) {
                    if (iter->name == it->rawArgument.substr(it->rawArgument.find("[")+1, it->rawArgument.find(']')-1)) {
                        it->convertedArgument = iter->address;
                        break;
                    }
                }
            }

            std::cout << std::right << std::setw(3) << std::setfill(' ') << std::uppercase << std::hex << it->address << ":" << std::setw(6) << " ";
            std::cout << std::setw(2) << std::setfill('0') << std::uppercase << std::hex << it->instruction << " ";
            std::cout << std::setw(2) << std::setfill('0') << std::uppercase << std::hex << it->convertedArgument << " "  << std::setfill(' ') << std::setw(6) << " ";
            std::cout << it->code << std::endl;

            datafile << std::setw(2) << std::setfill('0') << std::uppercase << std::hex << it->instruction << " ";
            datafile << std::setw(2) << std::setfill('0') << std::uppercase << std::hex << it->convertedArgument << std::endl;
         }
        ++it;
    }

    return 0;
}