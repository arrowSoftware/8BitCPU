#ifndef __Tokens_H__
#define __Tokens_H__

#include <string>
#include <stdint.h>

typedef enum Instructions {
    NOP,
    HLT,
    LDA_NUM,
    LDA_ADDR,
    STA_ADDR,
    LDB_NUM,
    LDB_ADDR,
    STB_ADDR,
    ADD_NUM,
    ADD_ADDR,
    SUB_NUM,
    SUB_ADDR,
    AND_NUM,
    AND_ADDR,
    OR_NUM,
    OR_ADDR,
    XOR_NUM,
    XOR_ADDR,
    NOTA,
    NOT_ADDR,
    OUTA,
    OUTB,
    OUT_NUM,
    OUT_ADDR,
    JMP_ADDR,
    JPZ_ADDR,
    JPC_ADDR,
    RST,
    DB,
    LABEL,
} Instructions_t;

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
    }
    return NOP;
}
typedef struct InstructionDetails {
    Instructions_t name;
    uint8_t opCode;
    int size;
} InstructionDetails_t;

static const InstructionDetails_t instructionDetails[27] = {
    {NOP,      0x00, 1},
    {HLT,      0x01, 1},
    {LDA_NUM,  0x02, 2},
    {LDA_ADDR, 0x03, 2},
    {STA_ADDR, 0x04, 2},
    {LDB_NUM,  0x05, 2},
    {LDB_ADDR, 0x06, 2},
    {STB_ADDR, 0x07, 2},
    {ADD_NUM,  0x08, 2},
    {ADD_ADDR, 0x09, 2},
    {SUB_NUM,  0x0A, 2},
    {SUB_ADDR, 0x0B, 2},
    {AND_NUM,  0x0C, 2},
    {ADD_ADDR, 0x0D, 2},
    {OR_NUM,   0x0E, 2},
    {OR_ADDR,  0x0F, 2},
    {XOR_NUM,  0x10, 2},
    {XOR_ADDR, 0x11, 2},
    {NOTA,     0x12, 1},
    {NOT_ADDR, 0x13, 2},
    {OUTA,     0x14, 1},
    {OUTB,     0x15, 1},
    {OUT_NUM,  0x16, 2},
    {OUT_ADDR, 0x17, 2},
    {JMP_ADDR, 0x18, 2},
    {JPZ_ADDR, 0x19, 2},
    {JPC_ADDR, 0x1A, 2}
};

int getInstructionSize(Instructions_t instruction) {
    for (int i = 0; i < 27; i++) {
        if (instructionDetails[i].opCode == instruction) {
            return instructionDetails[i].size;
        }
    }
    return 0;
}

#endif // __Tokens_H__