#include "FullAdder.h"
#include "LogicGate.h"
#include "HalfAdder.h"

FullAdder::FullAdder(bool A, bool B, bool Ci) :
    Circuit(),
    _A(A),
    _B(B),
    _Ci(Ci),
    _sum(false),
    _carry(false)
{}

FullAdder::~FullAdder(void)
{}

bool FullAdder::process(void)
{
    HalfAdder ha1(_A, _B);
    ha1.process();
    HalfAdder ha2(ha1.sum(), _Ci);
    ha2.process();
    LogicORGate OR(ha1.carry(), ha2.carry());
    _sum = ha2.sum();
    _carry = OR.process();
    return true;
}