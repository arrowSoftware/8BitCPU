#include "DFlipFlop.h"
#include "LogicGate.h"
#include <stdio.h>

DFlipFlop::DFlipFlop(bool enable, bool A, bool S, bool R) :
    _enable(enable), _A(A), _S(S), _R(R), _Q(false), _QB(true)
{}

DFlipFlop::~DFlipFlop()
{}

void DFlipFlop::update(bool enable, bool A, bool S, bool R)
{
    _enable = enable;
    _A = A;
    _S = S;
    _R = R;
}

bool DFlipFlop::process()
{
    LogicNANDGate3 NAND1(false, false, false);
    LogicNANDGate3 NAND2(false, false, false);
    LogicNANDGate3 NAND3(false, false, false);
    LogicNANDGate3 NAND4(false, false, false);
    LogicNANDGate3 NAND5(false, false, false);
    LogicNANDGate3 NAND6(false, false, false);
    LogicNOTGate NOT1(_S);
    LogicNOTGate NOT2(_R);

    NAND1.update(NOT1.process(), NAND4.process(), NAND2.process());
    NAND2.update(NAND1.process(), _enable, NOT2.process());
    NAND3.update(NAND2.process(), _enable, NAND4.process());
    NAND4.update(_A, NOT2.process(), NAND3.process());

    printf("1:%d 2:%d 3:%d 4:%d\n", NAND1.process(), NAND2.process(), NAND3.process(), NAND3.process());

    NAND5.update(NOT1.process(), NAND2.process(), NAND6.process());
    NAND5.process();
    NAND6.update(NOT2.process(), NAND3.process(), NAND5.process());
    NAND6.process();
    printf("5:%d 6:%d\n", NAND5.process(), NAND6.process());

    return true;
}