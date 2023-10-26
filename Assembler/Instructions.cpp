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

std::string getInstructionStr(Instructions_t instruction) {
    switch (instruction) {
        case (NOP):      { return "NOP"; break; }
        case (HLT):      { return "HLT"; break; }
        case (LDA_NUM):  { return "LDA"; break; }
        case (LDA_ADDR): { return "LDA"; break; }
        case (STA_ADDR): { return "STA"; break; }
        case (LDB_NUM):  { return "LDB"; break; }
        case (LDB_ADDR): { return "LDB"; break; }
        case (STB_ADDR): { return "STB"; break; }
        case (ADD_NUM):  { return "ADD"; break; }
        case (ADD_ADDR): { return "ADD"; break; }
        case (SUB_NUM):  { return "SUB"; break; }
        case (SUB_ADDR): { return "SUB"; break; }
        case (AND_NUM):  { return "AND"; break; }
        case (AND_ADDR): { return "AND"; break; }
        case (OR_NUM):   { return "OR"; break; }
        case (OR_ADDR):  { return "OR"; break; }
        case (XOR_NUM):  { return "XOR"; break; }
        case (XOR_ADDR): { return "XOR"; break; }
        case (NOTA):     { return "NOTA"; break; }
        case (NOT_ADDR): { return "NOT"; break; }
        case (OUTA):     { return "OUTA"; break; }
        case (OUTB):     { return "OUTB"; break; }
        case (OUT_NUM):  { return "OUT"; break; }
        case (OUT_ADDR): { return "OUT"; break; }
        case (JMP_ADDR): { return "JMP"; break; }
        case (JPZ_ADDR): { return "JPZ"; break; }
        case (JPC_ADDR): { return "JPC"; break; }
        case (RST):      { return "RST"; break; }
        default: { return "UNKNOWN"; break; }
    }
}

bool isAddressInstruction(Instructions_t instruction) {
    switch (instruction) {
        case LDA_ADDR:
        case STA_ADDR:
        case LDB_ADDR:
        case STB_ADDR:
        case ADD_ADDR:
        case SUB_ADDR:
        case AND_ADDR:
        case XOR_ADDR:
        case OR_ADDR:
        case NOT_ADDR:
        case OUT_ADDR:
        case JMP_ADDR:
        case JPZ_ADDR:
        case JPC_ADDR: { return true; }
        case NOP:
        case HLT:
        case LDA_NUM:
        case LDB_NUM:
        case ADD_NUM:
        case SUB_NUM:
        case AND_NUM:
        case OR_NUM:
        case XOR_NUM:
        case NOTA:
        case OUTA:
        case OUTB:
        case OUT_NUM:
        case RST:
        default: { return false; }
    }
}
