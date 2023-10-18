#include "Assembler.h"
#include <string>
#include <iostream>
#include <sstream>

#include <stdio.h>
#include <gtest/gtest.h>

TEST(TestNOP, NOP_Valid) {
    std::stringstream testData;
    testData << "NOP" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_NE(0, compiledCode.size());
    ASSERT_EQ(0, compiledCode.at(0).address);
    ASSERT_EQ(0, compiledCode.at(0).instruction);
    ASSERT_EQ(0, compiledCode.at(0).operand);
    ASSERT_EQ("NOP", compiledCode.at(0).rawCode);
}

TEST(TestNOP, NOP_Valid_ignoreCase) {
    std::stringstream testData;
    testData << "nop" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_NE(0, compiledCode.size());
    ASSERT_EQ(0, compiledCode.at(0).address);
    ASSERT_EQ(0, compiledCode.at(0).instruction);
    ASSERT_EQ(0, compiledCode.at(0).operand);
    ASSERT_EQ("nop", compiledCode.at(0).rawCode);
}

TEST(TestNOP, NOP_Invalid_operand1) {
    std::stringstream testData;
    testData << "NOP 0x20" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_EQ(0, compiledCode.size());
}

TEST(TestNOP, NOP_Invalid_operand2) {
    std::stringstream testData;
    testData << "NOP [address]" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_EQ(0, compiledCode.size());
}

TEST(TestHLT, HLT_Valid) {
    std::stringstream testData;
    testData << "HLT" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_NE(0, compiledCode.size());
    ASSERT_EQ(0, compiledCode.at(0).address);
    ASSERT_EQ(1, compiledCode.at(0).instruction);
    ASSERT_EQ(0, compiledCode.at(0).operand);
    ASSERT_EQ("HLT", compiledCode.at(0).rawCode);
}

TEST(TestHLT, HLT_Valid_ignoreCase) {
    std::stringstream testData;
    testData << "hlt" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_NE(0, compiledCode.size());
    ASSERT_EQ(0, compiledCode.at(0).address);
    ASSERT_EQ(1, compiledCode.at(0).instruction);
    ASSERT_EQ(0, compiledCode.at(0).operand);
    ASSERT_EQ("hlt", compiledCode.at(0).rawCode);
}

TEST(TestHLT, HLT_Invalid_operand1) {
    std::stringstream testData;
    testData << "HLT 0x20" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_EQ(0, compiledCode.size());
}

TEST(TestHLT, HLT_Invalid_operand2) {
    std::stringstream testData;
    testData << "HLT [address]" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_EQ(0, compiledCode.size());
}

TEST(TestLDA_NUM, LDA_ignoreCase) {
    std::stringstream testData;
    testData << "lda 200" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_NE(0, compiledCode.size());
    ASSERT_EQ(0, compiledCode.at(0).address);
    ASSERT_EQ(2, compiledCode.at(0).instruction);
    ASSERT_EQ(200, compiledCode.at(0).operand);
    ASSERT_EQ("lda 200", compiledCode.at(0).rawCode);
}

TEST(TestLDA_NUM, LDA_decimal) {
    std::stringstream testData;
    testData << "LDA 200" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_NE(0, compiledCode.size());
    ASSERT_EQ(0, compiledCode.at(0).address);
    ASSERT_EQ(2, compiledCode.at(0).instruction);
    ASSERT_EQ(200, compiledCode.at(0).operand);
    ASSERT_EQ("LDA 200", compiledCode.at(0).rawCode);
}

TEST(TestLDA_NUM, LDA_Hex) {
    std::stringstream testData;
    testData << "LDA 0xCD" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_NE(0, compiledCode.size());
    ASSERT_EQ(0, compiledCode.at(0).address);
    ASSERT_EQ(2, compiledCode.at(0).instruction);
    ASSERT_EQ(0xCD, compiledCode.at(0).operand);
    ASSERT_EQ("LDA 0xCD", compiledCode.at(0).rawCode);
}

TEST(TestLDA_NUM, LDA_Octal) {
    std::stringstream testData;
    testData << "LDA 0o20" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_NE(0, compiledCode.size());
    ASSERT_EQ(0, compiledCode.at(0).address);
    ASSERT_EQ(2, compiledCode.at(0).instruction);
    ASSERT_EQ(16, compiledCode.at(0).operand);
    ASSERT_EQ("LDA 0o20", compiledCode.at(0).rawCode);
}

TEST(TestLDA_NUM, LDA_explicitDecimal) {
    std::stringstream testData;
    testData << "LDA 150d" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_NE(0, compiledCode.size());
    ASSERT_EQ(0, compiledCode.at(0).address);
    ASSERT_EQ(2, compiledCode.at(0).instruction);
    ASSERT_EQ(150, compiledCode.at(0).operand);
    ASSERT_EQ("LDA 150d", compiledCode.at(0).rawCode);
}

TEST(TestLDA_NUM, LDA_binary) {
    std::stringstream testData;
    testData << "LDA 011b" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_NE(0, compiledCode.size());
    ASSERT_EQ(0, compiledCode.at(0).address);
    ASSERT_EQ(2, compiledCode.at(0).instruction);
    ASSERT_EQ(3, compiledCode.at(0).operand);
    ASSERT_EQ("LDA 011b", compiledCode.at(0).rawCode);
}

TEST(TestLDA_ADDR, LDA_ValidAddr) {
    std::stringstream testData;
    testData << "LDA [variable]" << std::endl;
    testData << "variable: DB 0x10" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_NE(0, compiledCode.size());
    ASSERT_EQ(0, compiledCode.at(0).address);
    ASSERT_EQ(3, compiledCode.at(0).instruction);
    ASSERT_EQ(2, compiledCode.at(0).operand);
    ASSERT_EQ("LDA [variable]", compiledCode.at(0).rawCode);
}

TEST(TestLDA_ADDR, LDA_InvalidAddr) {
    std::stringstream testData;
    testData << "LDA [unknown]" << std::endl;
    testData << "variable: DB 0x10" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_EQ(0, compiledCode.size());
}

TEST(TestLDA_ADDR, LDA_InvalidDirectAddr) {
    std::stringstream testData;
    testData << "LDA [0x23]" << std::endl;
    testData << "variable: DB 0x10" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_EQ(0, compiledCode.size());
}

TEST(TestSTA_ADDR, STA_ValidAddr) {
    std::stringstream testData;
    testData << "STA [variable]" << std::endl;
    testData << "variable: DB 0x10" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_NE(0, compiledCode.size());
    ASSERT_EQ(0, compiledCode.at(0).address);
    ASSERT_EQ(4, compiledCode.at(0).instruction);
    ASSERT_EQ(2, compiledCode.at(0).operand);
    ASSERT_EQ("STA [variable]", compiledCode.at(0).rawCode);
}

TEST(TestSTA_ADDR, STA_ignoreCase) {
    std::stringstream testData;
    testData << "sta [variable]" << std::endl;
    testData << "variable: DB 0x10" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_NE(0, compiledCode.size());
    ASSERT_EQ(0, compiledCode.at(0).address);
    ASSERT_EQ(4, compiledCode.at(0).instruction);
    ASSERT_EQ(2, compiledCode.at(0).operand);
    ASSERT_EQ("sta [variable]", compiledCode.at(0).rawCode);
}

TEST(TestSTA_ADDR, STA_InvalidAddr) {
    std::stringstream testData;
    testData << "STA [unknown]" << std::endl;
    testData << "variable: DB 0x10" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_EQ(0, compiledCode.size());
}

TEST(TestSTA_ADDR, STA_InvalidDirectAddr) {
    std::stringstream testData;
    testData << "STA [0x23]" << std::endl;
    testData << "variable: DB 0x10" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_EQ(0, compiledCode.size());
}

TEST(TestLDB_NUM, LDB_decimal) {
    std::stringstream testData;
    testData << "LDB 200" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_NE(0, compiledCode.size());
    ASSERT_EQ(0, compiledCode.at(0).address);
    ASSERT_EQ(5, compiledCode.at(0).instruction);
    ASSERT_EQ(200, compiledCode.at(0).operand);
    ASSERT_EQ("LDB 200", compiledCode.at(0).rawCode);
}

TEST(TestLDB_NUM, LDB_ignoreCase) {
    std::stringstream testData;
    testData << "ldb 200" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_NE(0, compiledCode.size());
    ASSERT_EQ(0, compiledCode.at(0).address);
    ASSERT_EQ(5, compiledCode.at(0).instruction);
    ASSERT_EQ(200, compiledCode.at(0).operand);
    ASSERT_EQ("ldb 200", compiledCode.at(0).rawCode);
}

TEST(TestLDB_NUM, LDB_Hex) {
    std::stringstream testData;
    testData << "LDB 0xCD" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_NE(0, compiledCode.size());
    ASSERT_EQ(0, compiledCode.at(0).address);
    ASSERT_EQ(5, compiledCode.at(0).instruction);
    ASSERT_EQ(0xCD, compiledCode.at(0).operand);
    ASSERT_EQ("LDB 0xCD", compiledCode.at(0).rawCode);
}

TEST(TestLDB_NUM, LDB_Octal) {
    std::stringstream testData;
    testData << "LDB 0o20" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_NE(0, compiledCode.size());
    ASSERT_EQ(0, compiledCode.at(0).address);
    ASSERT_EQ(5, compiledCode.at(0).instruction);
    ASSERT_EQ(16, compiledCode.at(0).operand);
    ASSERT_EQ("LDB 0o20", compiledCode.at(0).rawCode);
}

TEST(TestLDB_NUM, LDB_explicitDecimal) {
    std::stringstream testData;
    testData << "LDB 150d" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_NE(0, compiledCode.size());
    ASSERT_EQ(0, compiledCode.at(0).address);
    ASSERT_EQ(5, compiledCode.at(0).instruction);
    ASSERT_EQ(150, compiledCode.at(0).operand);
    ASSERT_EQ("LDB 150d", compiledCode.at(0).rawCode);
}

TEST(TestLDB_NUM, LDB_binary) {
    std::stringstream testData;
    testData << "LDB 011b" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_NE(0, compiledCode.size());
    ASSERT_EQ(0, compiledCode.at(0).address);
    ASSERT_EQ(5, compiledCode.at(0).instruction);
    ASSERT_EQ(3, compiledCode.at(0).operand);
    ASSERT_EQ("LDB 011b", compiledCode.at(0).rawCode);
}

TEST(TestLDB_ADDR, LDB_ValidAddr) {
    std::stringstream testData;
    testData << "LDB [variable]" << std::endl;
    testData << "variable: DB 0x10" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_NE(0, compiledCode.size());
    ASSERT_EQ(0, compiledCode.at(0).address);
    ASSERT_EQ(6, compiledCode.at(0).instruction);
    ASSERT_EQ(2, compiledCode.at(0).operand);
    ASSERT_EQ("LDB [variable]", compiledCode.at(0).rawCode);
}

TEST(TestLDB_ADDR, LDB_InvalidAddr) {
    std::stringstream testData;
    testData << "LDB [unknown]" << std::endl;
    testData << "variable: DB 0x10" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_EQ(0, compiledCode.size());
}

TEST(TestLDB_ADDR, LDB_InvalidDirectAddr) {
    std::stringstream testData;
    testData << "LDB [0x23]" << std::endl;
    testData << "variable: DB 0x10" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_EQ(0, compiledCode.size());
}

TEST(TestSTB_ADDR, STB_ValidAddr) {
    std::stringstream testData;
    testData << "STB [variable]" << std::endl;
    testData << "variable: DB 0x10" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_NE(0, compiledCode.size());
    ASSERT_EQ(0, compiledCode.at(0).address);
    ASSERT_EQ(7, compiledCode.at(0).instruction);
    ASSERT_EQ(2, compiledCode.at(0).operand);
    ASSERT_EQ("STB [variable]", compiledCode.at(0).rawCode);
}

TEST(TestSTB_ADDR, STB_ignoreCase) {
    std::stringstream testData;
    testData << "stb [variable]" << std::endl;
    testData << "variable: DB 0x10" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_NE(0, compiledCode.size());
    ASSERT_EQ(0, compiledCode.at(0).address);
    ASSERT_EQ(7, compiledCode.at(0).instruction);
    ASSERT_EQ(2, compiledCode.at(0).operand);
    ASSERT_EQ("stb [variable]", compiledCode.at(0).rawCode);
}

TEST(TestSTB_ADDR, STB_InvalidAddr) {
    std::stringstream testData;
    testData << "STB [unknown]" << std::endl;
    testData << "variable: DB 0x10" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_EQ(0, compiledCode.size());
}

TEST(TestSTB_ADDR, STB_InvalidDirectAddr) {
    std::stringstream testData;
    testData << "STB [0x23]" << std::endl;
    testData << "variable: DB 0x10" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_EQ(0, compiledCode.size());
}

TEST(TestADD_NUM, ADD_decimal) {
    std::stringstream testData;
    testData << "ADD 200" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_NE(0, compiledCode.size());
    ASSERT_EQ(0, compiledCode.at(0).address);
    ASSERT_EQ(8, compiledCode.at(0).instruction);
    ASSERT_EQ(200, compiledCode.at(0).operand);
    ASSERT_EQ("ADD 200", compiledCode.at(0).rawCode);
}

TEST(TestADD_NUM, ADD_ignoreCase) {
    std::stringstream testData;
    testData << "add 200" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_NE(0, compiledCode.size());
    ASSERT_EQ(0, compiledCode.at(0).address);
    ASSERT_EQ(8, compiledCode.at(0).instruction);
    ASSERT_EQ(200, compiledCode.at(0).operand);
    ASSERT_EQ("add 200", compiledCode.at(0).rawCode);
}

TEST(TestADD_NUM, ADD_Hex) {
    std::stringstream testData;
    testData << "ADD 0xCD" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_NE(0, compiledCode.size());
    ASSERT_EQ(0, compiledCode.at(0).address);
    ASSERT_EQ(8, compiledCode.at(0).instruction);
    ASSERT_EQ(0xCD, compiledCode.at(0).operand);
    ASSERT_EQ("ADD 0xCD", compiledCode.at(0).rawCode);
}

TEST(TestADD_NUM, ADD_Octal) {
    std::stringstream testData;
    testData << "ADD 0o20" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_NE(0, compiledCode.size());
    ASSERT_EQ(0, compiledCode.at(0).address);
    ASSERT_EQ(8, compiledCode.at(0).instruction);
    ASSERT_EQ(16, compiledCode.at(0).operand);
    ASSERT_EQ("ADD 0o20", compiledCode.at(0).rawCode);
}

TEST(TestADD_NUM, ADD_explicitDecimal) {
    std::stringstream testData;
    testData << "ADD 150d" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_NE(0, compiledCode.size());
    ASSERT_EQ(0, compiledCode.at(0).address);
    ASSERT_EQ(8, compiledCode.at(0).instruction);
    ASSERT_EQ(150, compiledCode.at(0).operand);
    ASSERT_EQ("ADD 150d", compiledCode.at(0).rawCode);
}

TEST(TestADD_NUM, ADD_binary) {
    std::stringstream testData;
    testData << "ADD 011b" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_NE(0, compiledCode.size());
    ASSERT_EQ(0, compiledCode.at(0).address);
    ASSERT_EQ(8, compiledCode.at(0).instruction);
    ASSERT_EQ(3, compiledCode.at(0).operand);
    ASSERT_EQ("ADD 011b", compiledCode.at(0).rawCode);
}

TEST(TestADD_ADDR, ADD_ValidAddr) {
    std::stringstream testData;
    testData << "ADD [variable]" << std::endl;
    testData << "variable: DB 0x10" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_NE(0, compiledCode.size());
    ASSERT_EQ(0, compiledCode.at(0).address);
    ASSERT_EQ(9, compiledCode.at(0).instruction);
    ASSERT_EQ(2, compiledCode.at(0).operand);
    ASSERT_EQ("ADD [variable]", compiledCode.at(0).rawCode);
}

TEST(TestADD_ADDR, ADD_InvalidAddr) {
    std::stringstream testData;
    testData << "ADD [unknown]" << std::endl;
    testData << "variable: DB 0x10" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_EQ(0, compiledCode.size());
}

TEST(TestADD_ADDR, ADD_InvalidDirectAddr) {
    std::stringstream testData;
    testData << "ADD [0x23]" << std::endl;
    testData << "variable: DB 0x10" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_EQ(0, compiledCode.size());
}

TEST(TestSUB_NUM, SUB_decimal) {
    std::stringstream testData;
    testData << "SUB 200" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_NE(0, compiledCode.size());
    ASSERT_EQ(0, compiledCode.at(0).address);
    ASSERT_EQ(0xA, compiledCode.at(0).instruction);
    ASSERT_EQ(200, compiledCode.at(0).operand);
    ASSERT_EQ("SUB 200", compiledCode.at(0).rawCode);
}

TEST(TestSUB_NUM, SUB_ignoreCase) {
    std::stringstream testData;
    testData << "sub 200" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_NE(0, compiledCode.size());
    ASSERT_EQ(0, compiledCode.at(0).address);
    ASSERT_EQ(0xA, compiledCode.at(0).instruction);
    ASSERT_EQ(200, compiledCode.at(0).operand);
    ASSERT_EQ("sub 200", compiledCode.at(0).rawCode);
}

TEST(TestSUB_NUM, SUB_Hex) {
    std::stringstream testData;
    testData << "SUB 0xCD" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_NE(0, compiledCode.size());
    ASSERT_EQ(0, compiledCode.at(0).address);
    ASSERT_EQ(0xA, compiledCode.at(0).instruction);
    ASSERT_EQ(0xCD, compiledCode.at(0).operand);
    ASSERT_EQ("SUB 0xCD", compiledCode.at(0).rawCode);
}

TEST(TestSUB_NUM, SUB_Octal) {
    std::stringstream testData;
    testData << "SUB 0o20" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_NE(0, compiledCode.size());
    ASSERT_EQ(0, compiledCode.at(0).address);
    ASSERT_EQ(0xA, compiledCode.at(0).instruction);
    ASSERT_EQ(16, compiledCode.at(0).operand);
    ASSERT_EQ("SUB 0o20", compiledCode.at(0).rawCode);
}

TEST(TestSUB_NUM, SUB_explicitDecimal) {
    std::stringstream testData;
    testData << "SUB 150d" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_NE(0, compiledCode.size());
    ASSERT_EQ(0, compiledCode.at(0).address);
    ASSERT_EQ(0xA, compiledCode.at(0).instruction);
    ASSERT_EQ(150, compiledCode.at(0).operand);
    ASSERT_EQ("SUB 150d", compiledCode.at(0).rawCode);
}

TEST(TestSUB_NUM, SUB_binary) {
    std::stringstream testData;
    testData << "SUB 011b" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_NE(0, compiledCode.size());
    ASSERT_EQ(0, compiledCode.at(0).address);
    ASSERT_EQ(0xA, compiledCode.at(0).instruction);
    ASSERT_EQ(3, compiledCode.at(0).operand);
    ASSERT_EQ("SUB 011b", compiledCode.at(0).rawCode);
}

TEST(TestSUB_ADDR, SUB_ValidAddr) {
    std::stringstream testData;
    testData << "SUB [variable]" << std::endl;
    testData << "variable: DB 0x10" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_NE(0, compiledCode.size());
    ASSERT_EQ(0, compiledCode.at(0).address);
    ASSERT_EQ(0xb, compiledCode.at(0).instruction);
    ASSERT_EQ(2, compiledCode.at(0).operand);
    ASSERT_EQ("SUB [variable]", compiledCode.at(0).rawCode);
}

TEST(TestSUB_ADDR, SUB_InvalidAddr) {
    std::stringstream testData;
    testData << "SUB [unknown]" << std::endl;
    testData << "variable: DB 0x10" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_EQ(0, compiledCode.size());
}

TEST(TestSUB_ADDR, SUB_InvalidDirectAddr) {
    std::stringstream testData;
    testData << "SUB [0x23]" << std::endl;
    testData << "variable: DB 0x10" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_EQ(0, compiledCode.size());
}

TEST(TestAND_NUM, AND_decimal) {
    GTEST_SKIP() << "Needs implementation";
}

TEST(TestAND_NUM, AND_ignoreCase) {
    GTEST_SKIP() << "Needs implementation";
}

TEST(TestAND_NUM, AND_hex) {
    GTEST_SKIP() << "Needs implementation";
}

TEST(TestAND_NUM, AND_Octal) {
    GTEST_SKIP() << "Needs implementation";
}

TEST(TestAND_NUM, AND_explicitDecimal) {
    GTEST_SKIP() << "Needs implementation";
}

TEST(TestAND_NUM, AND_binary) {
    GTEST_SKIP() << "Needs implementation";
}

TEST(TestAND_ADDR, AND_ValidAddr) {
    GTEST_SKIP() << "Needs implementation";
}

TEST(TestAND_ADDR, AND_InvalidAddr) {
    GTEST_SKIP() << "Needs implementation";
}

TEST(TestAND_ADDR, AND_InalidDirectAddr) {
    GTEST_SKIP() << "Needs implementation";
}

TEST(TestOR_NUM, OR_decimal) {
    GTEST_SKIP() << "Needs implementation";
}

TEST(TestOR_NUM, OR_ignoreCase) {
    GTEST_SKIP() << "Needs implementation";
}

TEST(TestOR_NUM, OR_hex) {
    GTEST_SKIP() << "Needs implementation";
}

TEST(TestOR_NUM, OR_Octal) {
    GTEST_SKIP() << "Needs implementation";
}

TEST(TestOR_NUM, OR_explicitDecimal) {
    GTEST_SKIP() << "Needs implementation";
}

TEST(TestOR_NUM, OR_binary) {
    GTEST_SKIP() << "Needs implementation";
}

TEST(TestOR_ADDR, OR_ValidAddr) {
    GTEST_SKIP() << "Needs implementation";
}

TEST(TestOR_ADDR, OR_InvalidAddr) {
    GTEST_SKIP() << "Needs implementation";
}

TEST(TestOR_ADDR, OR_InalidDirectAddr) {
    GTEST_SKIP() << "Needs implementation";
}

TEST(TestXOR_NUM, XOR_ignoreCase) {
    GTEST_SKIP() << "Needs implementation";
}

TEST(TestXOR_NUM, XOR_decimal) {
    GTEST_SKIP() << "Needs implementation";
}

TEST(TestXOR_NUM, XOR_hex) {
    GTEST_SKIP() << "Needs implementation";
}

TEST(TestXOR_NUM, XOR_Octal) {
    GTEST_SKIP() << "Needs implementation";
}

TEST(TestXOR_NUM, XOR_explicitDecimal) {
    GTEST_SKIP() << "Needs implementation";
}

TEST(TestXOR_NUM, XOR_binary) {
    GTEST_SKIP() << "Needs implementation";
}

TEST(TestXOR_ADDR, XOR_ValidAddr) {
    GTEST_SKIP() << "Needs implementation";
}

TEST(TestXOR_ADDR, XOR_InvalidAddr) {
    GTEST_SKIP() << "Needs implementation";
}

TEST(TestXOR_ADDR, XOR_InalidDirectAddr) {
    GTEST_SKIP() << "Needs implementation";
}

TEST(TestNOTA, NOTA_Valid) {
    GTEST_SKIP() << "Needs implementation";
}

TEST(TestNOTA, NOTA_ignoreCase) {
    GTEST_SKIP() << "Needs implementation";
}

TEST(TestNOTA, NOTA_Invalid_operand1) {
    GTEST_SKIP() << "Needs implementation";
}

TEST(TestNOTA, NOTA_Invalid_operand2) {
    GTEST_SKIP() << "Needs implementation";
}

TEST(TestNOT_ADDR, NOT_ValidAddr) {
    GTEST_SKIP() << "Needs implementation";
}

TEST(TestNOT_ADDR, NOTA_ignoreCase) {
    GTEST_SKIP() << "Needs implementation";
}

TEST(TestNOT_ADDR, NOT_InvalidAddr) {
    GTEST_SKIP() << "Needs implementation";
}

TEST(TestNOT_ADDR, NOT_InalidDirectAddr) {
    GTEST_SKIP() << "Needs implementation";
}

TEST(TestOUTA, OUTA_Valid) {
    std::stringstream testData;
    testData << "OUTA" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_NE(0, compiledCode.size());
    ASSERT_EQ(0, compiledCode.at(0).address);
    ASSERT_EQ(0x14, compiledCode.at(0).instruction);
    ASSERT_EQ(0, compiledCode.at(0).operand);
    ASSERT_EQ("OUTA", compiledCode.at(0).rawCode);
}

TEST(TestOUTA, OUTA_ignoreCase) {
    std::stringstream testData;
    testData << "outa" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_NE(0, compiledCode.size());
    ASSERT_EQ(0, compiledCode.at(0).address);
    ASSERT_EQ(0x14, compiledCode.at(0).instruction);
    ASSERT_EQ(0, compiledCode.at(0).operand);
    ASSERT_EQ("outa", compiledCode.at(0).rawCode);
}

TEST(TestOUTA, OUTA_Invalid_operand1) {
    std::stringstream testData;
    testData << "OUTA 0x20" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_EQ(0, compiledCode.size());
}

TEST(TestOUTA, OUTA_Invalid_operand2) {
    std::stringstream testData;
    testData << "OUTA [address]" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_EQ(0, compiledCode.size());
}

TEST(TestOUTB, OUTB_Valid) {
    std::stringstream testData;
    testData << "OUTB" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_NE(0, compiledCode.size());
    ASSERT_EQ(0, compiledCode.at(0).address);
    ASSERT_EQ(0x15, compiledCode.at(0).instruction);
    ASSERT_EQ(0, compiledCode.at(0).operand);
    ASSERT_EQ("OUTB", compiledCode.at(0).rawCode);
}

TEST(TestOUTB, OUTB_ignoreCase) {
    std::stringstream testData;
    testData << "outb" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_NE(0, compiledCode.size());
    ASSERT_EQ(0, compiledCode.at(0).address);
    ASSERT_EQ(0x15, compiledCode.at(0).instruction);
    ASSERT_EQ(0, compiledCode.at(0).operand);
    ASSERT_EQ("outb", compiledCode.at(0).rawCode);
}

TEST(TestOUTB, OUTB_Invalid_operand1) {
    std::stringstream testData;
    testData << "OUTB 0x20" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_EQ(0, compiledCode.size());
}

TEST(TestOUTB, OUTB_Invalid_operand2) {
    std::stringstream testData;
    testData << "OUTB [address]" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_EQ(0, compiledCode.size());
}

TEST(TestOUT_ADDR, OUT_ValidAddr) {
    std::stringstream testData;
    testData << "OUT [variable]" << std::endl;
    testData << "variable: DB 0x10" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_NE(0, compiledCode.size());
    ASSERT_EQ(0, compiledCode.at(0).address);
    ASSERT_EQ(0x17, compiledCode.at(0).instruction);
    ASSERT_EQ(2, compiledCode.at(0).operand);
    ASSERT_EQ("OUT [variable]", compiledCode.at(0).rawCode);
}

TEST(TestOUT_ADDR, OUT_ignoreCase) {
    std::stringstream testData;
    testData << "out [variable]" << std::endl;
    testData << "variable: DB 0x10" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_NE(0, compiledCode.size());
    ASSERT_EQ(0, compiledCode.at(0).address);
    ASSERT_EQ(0x17, compiledCode.at(0).instruction);
    ASSERT_EQ(2, compiledCode.at(0).operand);
    ASSERT_EQ("out [variable]", compiledCode.at(0).rawCode);
}

TEST(TestOUT_ADDR, OUT_InvalidAddr) {
    std::stringstream testData;
    testData << "OUT [unknown]" << std::endl;
    testData << "variable: DB 0x10" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_EQ(0, compiledCode.size());
}

TEST(TestOUT_ADDR, OUT_InvalidDirectAddr) {
    std::stringstream testData;
    testData << "OUT [0x23]" << std::endl;
    testData << "variable: DB 0x10" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_EQ(0, compiledCode.size());
}

TEST(TestJMP_ADDR, JMP_ValidAddr) {
    std::stringstream testData;
    testData << "JMP [variable]" << std::endl;
    testData << "variable: DB 0x10" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_NE(0, compiledCode.size());
    ASSERT_EQ(0, compiledCode.at(0).address);
    ASSERT_EQ(0x18, compiledCode.at(0).instruction);
    ASSERT_EQ(2, compiledCode.at(0).operand);
    ASSERT_EQ("JMP [variable]", compiledCode.at(0).rawCode);
}

TEST(TestJMP_ADDR, JMP_ignoreCase) {
    std::stringstream testData;
    testData << "jmp [variable]" << std::endl;
    testData << "variable: DB 0x10" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_NE(0, compiledCode.size());
    ASSERT_EQ(0, compiledCode.at(0).address);
    ASSERT_EQ(0x18, compiledCode.at(0).instruction);
    ASSERT_EQ(2, compiledCode.at(0).operand);
    ASSERT_EQ("jmp [variable]", compiledCode.at(0).rawCode);
}

TEST(TestJMP_ADDR, JMP_InvalidAddr) {
    std::stringstream testData;
    testData << "JMP [unknown]" << std::endl;
    testData << "variable: DB 0x10" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_EQ(0, compiledCode.size());
}

TEST(TestJMP_ADDR, JMP_InvalidDirectAddr) {
    std::stringstream testData;
    testData << "JMP [0x23]" << std::endl;
    testData << "variable: DB 0x10" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_EQ(0, compiledCode.size());
}

TEST(TestJPZ_ADDR, JPZ_ValidAddr) {
    std::stringstream testData;
    testData << "JPZ [variable]" << std::endl;
    testData << "variable: DB 0x10" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_NE(0, compiledCode.size());
    ASSERT_EQ(0, compiledCode.at(0).address);
    ASSERT_EQ(0x19, compiledCode.at(0).instruction);
    ASSERT_EQ(2, compiledCode.at(0).operand);
    ASSERT_EQ("JPZ [variable]", compiledCode.at(0).rawCode);
}

TEST(TestJPZ_ADDR, JPZ_ignoreCase) {
    std::stringstream testData;
    testData << "jpz [variable]" << std::endl;
    testData << "variable: DB 0x10" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_NE(0, compiledCode.size());
    ASSERT_EQ(0, compiledCode.at(0).address);
    ASSERT_EQ(0x19, compiledCode.at(0).instruction);
    ASSERT_EQ(2, compiledCode.at(0).operand);
    ASSERT_EQ("jpz [variable]", compiledCode.at(0).rawCode);
}

TEST(TestJPZ_ADDR, JPZ_InvalidAddr) {
    std::stringstream testData;
    testData << "JPZ [unknown]" << std::endl;
    testData << "variable: DB 0x10" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_EQ(0, compiledCode.size());
}

TEST(TestJPZ_ADDR, JPZ_InvalidDirectAddr) {
    std::stringstream testData;
    testData << "JPZ [0x23]" << std::endl;
    testData << "variable: DB 0x10" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_EQ(0, compiledCode.size());
}

TEST(TestJPC_ADDR, JPC_ValidAddr) {
    std::stringstream testData;
    testData << "JPC [variable]" << std::endl;
    testData << "variable: DB 0x10" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_NE(0, compiledCode.size());
    ASSERT_EQ(0, compiledCode.at(0).address);
    ASSERT_EQ(0x1A, compiledCode.at(0).instruction);
    ASSERT_EQ(2, compiledCode.at(0).operand);
    ASSERT_EQ("JPC [variable]", compiledCode.at(0).rawCode);
}

TEST(TestJPC_ADDR, JPC_ignoreCase) {
    std::stringstream testData;
    testData << "jpc [variable]" << std::endl;
    testData << "variable: DB 0x10" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_NE(0, compiledCode.size());
    ASSERT_EQ(0, compiledCode.at(0).address);
    ASSERT_EQ(0x1A, compiledCode.at(0).instruction);
    ASSERT_EQ(2, compiledCode.at(0).operand);
    ASSERT_EQ("jpc [variable]", compiledCode.at(0).rawCode);
}

TEST(TestJPC_ADDR, JPC_InvalidAddr) {
    std::stringstream testData;
    testData << "JPC [unknown]" << std::endl;
    testData << "variable: DB 0x10" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_EQ(0, compiledCode.size());
}

TEST(TestJPC_ADDR, JPC_InvalidDirectAddr) {
    std::stringstream testData;
    testData << "JPC [0x23]" << std::endl;
    testData << "variable: DB 0x10" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_EQ(0, compiledCode.size());
}

TEST(TestRST, RST_Valid) {
    GTEST_SKIP() << "Needs implementation";
}

TEST(TestRST, RST_ignoreCase) {
    GTEST_SKIP() << "Needs implementation";
}

TEST(TestRST, RST_Invalid_operand1) {
    GTEST_SKIP() << "Needs implementation";
}

TEST(TestRST, RST_Invalid_operand2) {
    GTEST_SKIP() << "Needs implementation";
}

TEST(TestDB, DB_Valid) {
    GTEST_SKIP() << "Needs implementation";
}

TEST(TestComments, Comments_Valid) {
    std::stringstream testData;
    testData << "INIT: ; Initialize state" << std::endl
             << "   LDA 0xAA ; Load 0xAA into the A register." << std::endl
             << "   STA [variable] ; Store the value in the A register in memory address variable" << std::endl
             << "   OUT [variable] ; load the value in the variable memory address to the output register" << std::endl
             << "   ; OUT 0x23 Commented out" << std::endl
             << "   LDA 23 ; 45" << std::endl
             << " ; Empty line" << std::endl
             << " ;;;; Empty line ;;" << std::endl
             << "variable: DB 0x00 ; variable pointer" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_EQ(5, compiledCode.size());

    ASSERT_EQ(0, compiledCode.at(0).address);
    ASSERT_EQ(2, compiledCode.at(0).instruction);
    ASSERT_EQ(0xAA, compiledCode.at(0).operand);
    ASSERT_EQ("LDA 0xAA ; Load 0xAA into the A register.", compiledCode.at(0).rawCode);

    ASSERT_EQ(2, compiledCode.at(1).address);
    ASSERT_EQ(4, compiledCode.at(1).instruction);
    ASSERT_EQ(8, compiledCode.at(1).operand);
    ASSERT_EQ("STA [variable] ; Store the value in the A register in memory address variable", compiledCode.at(1).rawCode);

    ASSERT_EQ(4, compiledCode.at(2).address);
    ASSERT_EQ(0x17, compiledCode.at(2).instruction);
    ASSERT_EQ(8, compiledCode.at(2).operand);
    ASSERT_EQ("OUT [variable] ; load the value in the variable memory address to the output register", compiledCode.at(2).rawCode);

    ASSERT_EQ(6, compiledCode.at(3).address);
    ASSERT_EQ(2, compiledCode.at(3).instruction);
    ASSERT_EQ(23, compiledCode.at(3).operand);
    ASSERT_EQ("LDA 23 ; 45", compiledCode.at(3).rawCode);
}

TEST(TestComments, CommentedOutCode) {
    std::stringstream testData;
    testData << "INIT: ; Initialize state" << std::endl
             << ";   LDA 0xAA ; Load 0xAA into the A register." << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_EQ(0, compiledCode.size());
}

TEST(TestLabels, MissingLabel) {
    std::stringstream testData;
    testData << "INIT:" << std::endl
             << "   LDA [Unknown]" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_EQ(0, compiledCode.size());
}

TEST(TestLabels, MispelledLabel) {
    std::stringstream testData;
    testData << "INIT:" << std::endl
             << "   LDA [Mispell]" << std::endl
             << "mispell: DB 0" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_EQ(0, compiledCode.size());
}

TEST(TestLabels, BadFormatLabel) {
    std::stringstream testData;
    testData << "INIT:" << std::endl
             << "   LDA [Mispell]" << std::endl
             << "mis:pell: DB 0" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_EQ(0, compiledCode.size());
}

TEST(TestCombinations, TestCombination1) {
    std::stringstream testData;
    testData << "INIT:" << std::endl
             << "   LDA 0xAA" << std::endl
             << "   STA [variable]" << std::endl
             << "   OUT [variable]" << std::endl
             << "variable: DB 0x00" << std::endl;
    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_EQ(4, compiledCode.size());
    ASSERT_EQ(0, compiledCode.at(0).address);
    ASSERT_EQ(2, compiledCode.at(0).instruction);
    ASSERT_EQ(0xAA, compiledCode.at(0).operand);
    ASSERT_EQ("LDA 0xAA", compiledCode.at(0).rawCode);

    ASSERT_EQ(2, compiledCode.at(1).address);
    ASSERT_EQ(4, compiledCode.at(1).instruction);
    ASSERT_EQ(6, compiledCode.at(1).operand);
    ASSERT_EQ("STA [variable]", compiledCode.at(1).rawCode);

    ASSERT_EQ(4, compiledCode.at(2).address);
    ASSERT_EQ(0x17, compiledCode.at(2).instruction);
    ASSERT_EQ(6, compiledCode.at(2).operand);
    ASSERT_EQ("OUT [variable]", compiledCode.at(2).rawCode);

    ASSERT_EQ(6, compiledCode.at(3).address);
    ASSERT_EQ("variable: DB 0x00", compiledCode.at(3).rawCode);
}

TEST(TestCombinations, TestCombination2) {
    std::stringstream testData;
    testData << "INIT:" << std::endl
             << "    LDA 00" << std::endl
             << "    STA [N1]" << std::endl
             << "    OUT [N1]" << std::endl
             << "    LDA 01" << std::endl
             << "    STA [N2]" << std::endl
             << " " << std::endl
             << "START:" << std::endl
             << "    OUT [N2]" << std::endl
             << "    LDA [N1]" << std::endl
             << "    ADD [N2]" << std::endl
             << "    STB [N1]" << std::endl
             << "    STA [N2]" << std::endl
             << "    JPC [INIT]" << std::endl
             << "    JMP [START]" << std::endl
             << "END:" << std::endl
             << "    HLT" << std::endl
             << " " << std::endl
             << "N1: DB 00" << std::endl
             << "N2: DB 00" << std::endl;

    std::vector<CompiledLine_t> compiledCode = assemble(testData);
    ASSERT_EQ(15, compiledCode.size());

    ASSERT_EQ(0, compiledCode.at(0).address);
    ASSERT_EQ(2, compiledCode.at(0).instruction);
    ASSERT_EQ(0, compiledCode.at(0).operand);
    ASSERT_EQ("LDA 00", compiledCode.at(0).rawCode);

    ASSERT_EQ(2, compiledCode.at(1).address);
    ASSERT_EQ(4, compiledCode.at(1).instruction);
    ASSERT_EQ(25, compiledCode.at(1).operand);
    ASSERT_EQ("STA [N1]", compiledCode.at(1).rawCode);

    ASSERT_EQ(4, compiledCode.at(2).address);
    ASSERT_EQ(0x17, compiledCode.at(2).instruction);
    ASSERT_EQ(25, compiledCode.at(2).operand);
    ASSERT_EQ("OUT [N1]", compiledCode.at(2).rawCode);

    ASSERT_EQ(6, compiledCode.at(3).address);
    ASSERT_EQ(2, compiledCode.at(3).instruction);
    ASSERT_EQ(1, compiledCode.at(3).operand);
    ASSERT_EQ("LDA 01", compiledCode.at(3).rawCode);

    ASSERT_EQ(8, compiledCode.at(4).address);
    ASSERT_EQ(4, compiledCode.at(4).instruction);
    ASSERT_EQ(26, compiledCode.at(4).operand);
    ASSERT_EQ("STA [N2]", compiledCode.at(4).rawCode);

    ASSERT_EQ(10, compiledCode.at(5).address);
    ASSERT_EQ(0x17, compiledCode.at(5).instruction);
    ASSERT_EQ(26, compiledCode.at(5).operand);
    ASSERT_EQ("OUT [N2]", compiledCode.at(5).rawCode);

    ASSERT_EQ(12, compiledCode.at(6).address);
    ASSERT_EQ(3, compiledCode.at(6).instruction);
    ASSERT_EQ(25, compiledCode.at(6).operand);
    ASSERT_EQ("LDA [N1]", compiledCode.at(6).rawCode);

    ASSERT_EQ(14, compiledCode.at(7).address);
    ASSERT_EQ(9, compiledCode.at(7).instruction);
    ASSERT_EQ(26, compiledCode.at(7).operand);
    ASSERT_EQ("ADD [N2]", compiledCode.at(7).rawCode);

    ASSERT_EQ(16, compiledCode.at(8).address);
    ASSERT_EQ(7, compiledCode.at(8).instruction);
    ASSERT_EQ(25, compiledCode.at(8).operand);
    ASSERT_EQ("STB [N1]", compiledCode.at(8).rawCode);

    ASSERT_EQ(18, compiledCode.at(9).address);
    ASSERT_EQ(4, compiledCode.at(9).instruction);
    ASSERT_EQ(26, compiledCode.at(9).operand);
    ASSERT_EQ("STA [N2]", compiledCode.at(9).rawCode);

    ASSERT_EQ(20, compiledCode.at(10).address);
    ASSERT_EQ(0x1A, compiledCode.at(10).instruction);
    ASSERT_EQ(0, compiledCode.at(10).operand);
    ASSERT_EQ("JPC [INIT]", compiledCode.at(10).rawCode);

    ASSERT_EQ(22, compiledCode.at(11).address);
    ASSERT_EQ(0x18, compiledCode.at(11).instruction);
    ASSERT_EQ(0xA, compiledCode.at(11).operand);
    ASSERT_EQ("JMP [START]", compiledCode.at(11).rawCode);

    ASSERT_EQ(24, compiledCode.at(12).address);
    ASSERT_EQ(1, compiledCode.at(12).instruction);
    ASSERT_EQ("HLT", compiledCode.at(12).rawCode);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}