#include "Clock.h"
#include "LogicGate.h"
#include "HalfAdder.h"
#include "FullAdder.h"
#include <stdio.h>

void testLogicAND()
{
    printf("Testing Logical AND\n");
    bool testData[12] = {
        false, false, false,
        false, true, false,
        true, false, false,
        true, true, true
    };

    for (int i = 0; i < 12; i+=3)
    {
        LogicANDGate gate = LogicANDGate(testData[i], testData[i+1]);
        printf("A %d B %d ", testData[i], testData[i+1]);
        if (gate.process() == testData[i+2])
        {
            printf("PASS\n");
        }
        else
        {
            printf("FAIL actual: %d\n", gate.process());
        }
    }
}

void testLogicOR()
{
    printf("Testing Logical OR\n");
    bool testData[12] = {
        false, false, false,
        false, true, true,
        true, false, true,
        true, true, true
    };

    for (int i = 0; i < 12; i+=3)
    {
        LogicORGate gate = LogicORGate(testData[i], testData[i+1]);
        printf("A %d B %d ", testData[i], testData[i+1]);
        if (gate.process() == testData[i+2])
        {
            printf("PASS\n");
        }
        else
        {
            printf("FAIL actual: %d\n", gate.process());
        }
    }
}

void testLogicXOR()
{
    printf("Testing Logical XOR\n");
    bool testData[12] = {
        false, false, false,
        false, true, true,
        true, false, true,
        true, true, false
    };

    for (int i = 0; i < 12; i+=3)
    {
        LogicXORGate gate = LogicXORGate(testData[i], testData[i+1]);
        printf("A %d B %d ", testData[i], testData[i+1]);
        if (gate.process() == testData[i+2])
        {
            printf("PASS [%d]\n", testData[i+2]);
        }
        else
        {
            printf("FAIL actual: %d\n", gate.process());
        }
    }
}

void testLogicNOT()
{
    printf("Testing Logical NOT\n");
    bool testData[4] = {
        false, true,
        true, false
    };

    for (int i = 0; i < 4; i+=2)
    {
        LogicNOTGate gate = LogicNOTGate(testData[i]);
        printf("A %d ", testData[i]);
        if (gate.process() == testData[i+1])
        {
            printf("PASS\n");
        }
        else
        {
            printf("FAIL actual: %d\n", gate.process());
        }
    }
}

void testLogicNAND()
{
    printf("Testing Logical NAND\n");
    bool testData[12] = {
        false, false, true,
        false, true, true,
        true, false, true,
        true, true, false
    };

    for (int i = 0; i < 12; i+=3)
    {
        LogicNANDGate gate = LogicNANDGate(testData[i], testData[i+1]);
        printf("A %d B %d ", testData[i], testData[i+1]);
        if (gate.process() == testData[i+2])
        {
            printf("PASS\n");
        }
        else
        {
            printf("FAIL actual: %d\n", gate.process());
        }
    }
}

void testLogicNOR()
{
    printf("Testing Logical NOR\n");
    bool testData[12] = {
        false, false, true,
        false, true, false,
        true, false, false,
        true, true, false
    };

    for (int i = 0; i < 12; i+=3)
    {
        LogicNORGate gate = LogicNORGate(testData[i], testData[i+1]);
        printf("A %d B %d ", testData[i], testData[i+1]);
        if (gate.process() == testData[i+2])
        {
            printf("PASS\n");
        }
        else
        {
            printf("FAIL actual: %d\n", gate.process());
        }
    }
}

void testLogicXNOR()
{
    printf("Testing Logical XNOR\n");
    bool testData[12] = {
        false, false, true,
        false, true, false,
        true, false, false,
        true, true, true
    };

    for (int i = 0; i < 12; i+=3)
    {
        LogicXNORGate gate = LogicXNORGate(testData[i], testData[i+1]);
        printf("A %d B %d ", testData[i], testData[i+1]);
        if (gate.process() == testData[i+2])
        {
            printf("PASS\n");
        }
        else
        {
            printf("FAIL actual: %d\n", gate.process());
        }
    }
}

void testHalfAdder(void)
{
    printf("Testing Half Adder\n");

    bool testData[] = {
        //A    B      Sum    Carry
        false, false, false, false,
        false, true, true, false,
        true, false, true, false,
        true, true, false, true
    };

    for (int i = 0; i < 16; i+=4)
    {
        HalfAdder ha = HalfAdder(testData[i], testData[i+1]);
        printf("A %d B %d ", testData[i], testData[i+1]);
        ha.process();
        if ((ha.sum() == testData[i+2]) &&
            (ha.carry() == testData[i+3]))
        {
            printf("PASS\n");
        }
        else
        {
            printf("FAIL expected Sum[%d] Carry[%d] actual Sum[%d] Carry[%d]\n",
            testData[i+2],
            testData[i+3],
            ha.sum(),
            ha.carry());
        }
    }
}

void testFullAdder(void)
{
    printf("Testing Full Adder\n");

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
        FullAdder fa = FullAdder(testData[i], testData[i+1], testData[i+2]);
        printf("A %d B %d Ci: %d ", testData[i], testData[i+1], testData[i+2]);
        fa.process();
        if ((fa.sum() == testData[i+3]) &&
            (fa.carry() == testData[i+4]))
        {
            printf("PASS\n");
        }
        else
        {
            printf("FAIL expected Sum[%d] Carry[%d] actual Sum[%d] Carry[%d]\n",
            testData[i+3],
            testData[i+4],
            fa.sum(),
            fa.carry());
        }
    }
}

int main()
{
    Clock clock;
    clock.step();

    testLogicAND();
    testLogicOR();
    testLogicXOR();
    testLogicNOT();
    testLogicNAND();
    testLogicNOR();
    testLogicXNOR();

    testHalfAdder();
    testFullAdder();
}