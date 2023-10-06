#include "Clock.h"
#include "LogicGate.h"
#include "HalfAdder.h"
#include "FullAdder.h"
#include "EightBitAdder.h"
#include "DLatch.h"
#include "DFlipFlop.h"

#include <stdio.h>

#include <gtest/gtest.h>

TEST(testLogicAND, FullCircuit)
{
    bool testData[12] = {
        false, false, false,
        false, true, false,
        true, false, false,
        true, true, true
    };

    for (int i = 0; i < 12; i+=3)
    {
        LogicANDGate gate(testData[i], testData[i+1]);
        ASSERT_EQ(gate.process(), testData[i+2]);
    }
}

TEST(testLogicOR, FullCircuit)
{
    bool testData[12] = {
        false, false, false,
        false, true, true,
        true, false, true,
        true, true, true
    };

    for (int i = 0; i < 12; i+=3)
    {
        LogicORGate gate(testData[i], testData[i+1]);
        ASSERT_EQ(gate.process(), testData[i+2]);
    }
}

TEST(testLogicXOR, FullCircuit)
{
    bool testData[12] = {
        false, false, false,
        false, true, true,
        true, false, true,
        true, true, false
    };

    for (int i = 0; i < 12; i+=3)
    {
        LogicXORGate gate(testData[i], testData[i+1]);
        ASSERT_EQ(gate.process(), testData[i+2]);
    }
}

TEST(testLogicNOT, FullCircuit)
{
    bool testData[4] = {
        false, true,
        true, false
    };

    for (int i = 0; i < 4; i+=2)
    {
        LogicNOTGate gate(testData[i]);
        ASSERT_EQ(gate.process(), testData[i+1]);
    }
}

TEST(testLogicNAND, FullCircuit)
{
    bool testData[12] = {
        false, false, true,
        false, true, true,
        true, false, true,
        true, true, false
    };

    for (int i = 0; i < 12; i+=3)
    {
        LogicNANDGate gate(testData[i], testData[i+1]);
        ASSERT_EQ(gate.process(), testData[i+2]);
    }
}

TEST(testLogicNOR, FullCircuit)
{
    bool testData[12] = {
        false, false, true,
        false, true, false,
        true, false, false,
        true, true, false
    };

    for (int i = 0; i < 12; i+=3)
    {
        LogicNORGate gate(testData[i], testData[i+1]);
        ASSERT_EQ(gate.process(), testData[i+2]);
    }
}

TEST(testLogicXNOR, FullCircuit)
{
    bool testData[12] = {
        false, false, true,
        false, true, false,
        true, false, false,
        true, true, true
    };

    for (int i = 0; i < 12; i+=3)
    {
        LogicXNORGate gate(testData[i], testData[i+1]);
        ASSERT_EQ(gate.process(), testData[i+2]);
    }
}

TEST(testHalfAdder, FullCircuit)
{
    bool testData[] = {
        //A    B      Sum    Carry
        false, false, false, false,
        false, true, true, false,
        true, false, true, false,
        true, true, false, true
    };

    for (int i = 0; i < 16; i+=4)
    {
        HalfAdder ha(testData[i], testData[i+1]);
        ha.process();
        ASSERT_EQ(ha.sum(), testData[i+2]);
        ASSERT_EQ(ha.carry(), testData[i+3]);
    }
}

TEST(testFullAdder, FullCircuit)
{
    bool testData[] = {
        //A    B      Ci     Sum    Carry
        false, false, false, false, false,
        false, false, true, true, false,
        false, true, false, true, false,
        false, true, true, false, true,
        true, false, false, true, false,
        true, false, true, false, true,
        true, true, false, false, true,
        true, true, true, true, true,
    };

    for (int i = 0; i < 40; i+=5)
    {
        FullAdder fa(testData[i], testData[i+1], testData[i+2]);
        fa.process();
        ASSERT_EQ(fa.sum(), testData[i+3]);
        ASSERT_EQ(fa.carry(), testData[i+4]);
    }
}

TEST(testEightBitAdder, FullCircuit)
{
    for (int i = 0; i < 255; i++)
    {
        for (int j = 0; j < 255; j++)
        {
            EightBitData A; A.set(i);
            EightBitData B; B.set(j);
            EightBitAdder eba(A, B, 0);
            eba.process();
            ASSERT_TRUE( ((eba.sum().data.byte == (A.data.byte + B.data.byte)) || (((A.data.byte + B.data.byte) > 0xFF) && eba.carry())) );
        }
    }
}

TEST(DLatchTest, FullCircuit)
{
    DLatch dlatch(false, false);

    dlatch.process();
    ASSERT_EQ(false, dlatch.Q());
    ASSERT_EQ(true, dlatch.QB());

    dlatch.update(false, true);
    dlatch.process();
    ASSERT_EQ(false, dlatch.Q());
    ASSERT_EQ(true, dlatch.QB());

    dlatch.update(true, false);
    dlatch.process();
    ASSERT_EQ(false, dlatch.Q());
    ASSERT_EQ(true, dlatch.QB());

    dlatch.update(true, true);
    dlatch.process();
    ASSERT_EQ(true, dlatch.Q());
    ASSERT_EQ(false, dlatch.QB());

    dlatch.update(false, false);
    dlatch.process();
    ASSERT_EQ(true, dlatch.Q());
    ASSERT_EQ(false, dlatch.QB());
}

TEST(DFlipFlopTest, FullCircuit)
{
    // https://github.com/GIBIS-UNIFESP/wiRedPanda/blob/351d47990e14f8e105cac3a0e5481c1840cfcaaa/test/testlogicelements.cpp#L159
    bool testData[] = {
      /* L D  C  p  c  Q ~Q */
        0, 0, 1, 1, 1, 0, 1, /* Clk up and D = 0 */
        0, 1, 1, 1, 1, 1, 0, /* Clk up and D = 1 */

        0, 0, 0, 0, 1, 1, 0, /* Preset = false */
        0, 0, 1, 1, 0, 0, 1, /* Clear = false */
        0, 0, 1, 0, 0, 1, 1, /* Clear and Preset = false */

        1, 0, 0, 1, 1, 1, 0, /* Clk dwn and D = 0 (must maintain current state)*/
        1, 1, 0, 1, 1, 1, 0, /* Clk dwn and D = 1 (must maintain current state)*/
    };

    DFlipFlop flipflop(false, false, false, false);
    for (int i = 0; i < 49; i+=7)
    {
        flipflop.update(testData[i], testData[i+1], false, false);
        flipflop.process();

        flipflop.setQ(testData[i]);
        flipflop.setQB(!testData[i]);

        flipflop.update(testData[i+2], testData[i+1], testData[i+3], testData[i+4]);
        flipflop.process();

        ASSERT_EQ(testData[i+5], flipflop.Q());
        ASSERT_EQ(testData[i+6], flipflop.QB());
    }
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}