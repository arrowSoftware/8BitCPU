#include "HalfAdder.h"

#include "LogicGate.h"
#include <stdio.h>
HalfAdder::HalfAdder(bool A, bool B) :
    Circuit(),
    _A(A),
    _B(B),
    _sum(false),
    _carry(false)
{}

HalfAdder::~HalfAdder(void)
{}

bool HalfAdder::process(void)
{
    // A ----- XOR --- SUM
    // B -|-|- XOR
    // A  | -- AND --- Carry
    // B  ---- AND
    LogicXORGate XOR(_A, _B);
    _sum = XOR.process();
    LogicANDGate AND(_A, _B);
    _carry = AND.process();

    return true;
}