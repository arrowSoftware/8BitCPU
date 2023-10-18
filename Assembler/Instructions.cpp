#include "Instructions.h"
#include "Helpers.h"

int getInstructionSize(Instructions_t instruction) {
    int size = 0;
    for (int i = 0; i < 27; i++) {
        if (instructionDetails[i].opCode == instruction) {
            size = instructionDetails[i].size;
            break;
        }
    }
    return size;
}

Instructions_t getInstructionEnum(std::string instruction, bool addr) {
    if (isEqual(instruction, "LDA")) {
        if (addr) {
            return LDA_ADDR;
        } else {
            return LDA_NUM;
        }
    } else if (isEqual(instruction, "STA")) {
        return STA_ADDR;
    } else if (isEqual(instruction, "LDB")) {
        if (addr) {
            return LDB_ADDR;
        } else {
            return LDB_NUM;
        }
    } else if (isEqual(instruction, "STB")) {
        return STB_ADDR;
    } else if (isEqual(instruction, "ADD")) {
        if (addr) {
            return ADD_ADDR;
        } else {
            return ADD_NUM;
        }
    } else if (isEqual(instruction, "SUB")) {
        if (addr) {
            return SUB_ADDR;
        } else {
            return SUB_NUM;
        }
    } else if (isEqual(instruction, "OUTA")) {
        return OUTA;
    } else if (isEqual(instruction, "OUTB")) {
        return OUTB;
    } else if (isEqual(instruction, "OUT")) {
        if (addr) {
            return OUT_ADDR;
        } else {
            return OUT_NUM;
        }
    } else if (isEqual(instruction, "JMP")) {
        return JMP_ADDR;
    } else if (isEqual(instruction, "JPZ")) {
        return JPZ_ADDR;
    } else if (isEqual(instruction, "JPC")) {
        return JPC_ADDR;
    } else if (isEqual(instruction, "HLT")) {
        return HLT;
    }
    return NOP;
}