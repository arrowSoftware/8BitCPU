#include "Instructions.h"

int getInstructionSize(Instructions_t instruction) {
    for (int i = 0; i < 27; i++) {
        if (instructionDetails[i].opCode == instruction) {
            return instructionDetails[i].size;
        }
    }
    return 0;
}

Instructions_t getInstructionEnum(std::string instruction, bool addr) {
    if (instruction == "LDA") {
        if (addr) {
            return LDA_ADDR;
        } else {
            return LDA_NUM;
        }
    } else if (instruction == "STA") {
        return STA_ADDR;
    } else if (instruction == "LDB") {
        if (addr) {
            return LDB_ADDR;
        } else {
            return LDB_NUM;
        }
    } else if (instruction == "STB") {
        return STB_ADDR;
    } else if (instruction == "ADD") {
        if (addr) {
            return ADD_ADDR;
        } else {
            return ADD_NUM;
        }
    } else if (instruction == "SUB") {
        if (addr) {
            return SUB_ADDR;
        } else {
            return SUB_NUM;
        }
    } else if (instruction == "OUTA") {
        return OUTA;
    } else if (instruction == "OUTB") {
        return OUTB;
    } else if (instruction == "OUT") {
        if (addr) {
            return OUT_ADDR;
        } else {
            return OUT_NUM;
        }
    } else if (instruction == "JMP") {
        return JMP_ADDR;
    } else if (instruction == "JPZ") {
        return JPZ_ADDR;
    } else if (instruction == "JPC") {
        return JPC_ADDR;
    } else if (instruction == "HLT") {
        return HLT;
    }
    return NOP;
}