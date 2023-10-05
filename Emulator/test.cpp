#include "Clock.h"
#include "LogicGate.h"
#include "HalfAdder.h"
#include "FullAdder.h"
#include "EightBitAdder.h"
#include "DLatch.h"
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
        LogicANDGate gate(testData[i], testData[i+1]);
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
        LogicORGate gate(testData[i], testData[i+1]);
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
        LogicXORGate gate(testData[i], testData[i+1]);
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
        LogicNOTGate gate(testData[i]);
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
        LogicNANDGate gate(testData[i], testData[i+1]);
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
        LogicNORGate gate(testData[i], testData[i+1]);
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
        LogicXNORGate gate(testData[i], testData[i+1]);
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
        HalfAdder ha(testData[i], testData[i+1]);
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
        FullAdder fa(testData[i], testData[i+1], testData[i+2]);
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

void testEightBitAdder()
{
    printf("Testing Eight Bit Adder\n");
    for (int i = 0; i < 255; i++)
    {
        for (int j = 0; j < 255; j++)
        {
            EightBitData A; A.set(i);
            EightBitData B; B.set(j);
            EightBitAdder eba(A, B, 0);
            eba.process();
            if (eba.sum().data.byte == (A.data.byte + B.data.byte) || 
               (((A.data.byte + B.data.byte) > 0xFF) && eba.carry()))
            {
            }
            else
            {
                printf("Inputs: A %d B %d Ci %d\n", A.data.byte, B.data.byte, 0);
                printf("FAIL expected S %d C %d V %d actual S %d C %d V %d\n",
                A.data.byte + B.data.byte,
                0,
                0,
                eba.sum(),
                eba.carry(),
                eba.overflow());
            }
        }
    }
}

void testDLatch(void)
{
    bool testData[] = {
        // enable A Q ~Q
        false, false, false, true,
        false, true, false, true,
        true, false, false, true,
        true, true, true, false,
        false, false, true, false
    };
    DLatch dlatch(false, false);
    dlatch.process();

    for (int i = 0; i < 20; i+=4)
    {
        dlatch.update(testData[i], testData[i+1]);
        dlatch.process();
        printf("enable: %d A: %d ", testData[i], testData[i+1]);
        if (dlatch.Q() == testData[i+2] && dlatch.QB() == testData[i+3])
        {
            printf("PASS\n");
        }
        else
        {
            printf("FAIL expected: Q: %d QB: %d actual Q: %d QB: %d \n", testData[i+2], testData[i+3], dlatch.Q(), dlatch.QB());
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
    testEightBitAdder();

    testDLatch();
}