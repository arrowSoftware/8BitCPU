#include "EightBitAdder.h"
#include "FullAdder.h"
#include "LogicGate.h"

EightBitAdder::EightBitAdder(EightBitData A, EightBitData B, bool Ci) :
    Circuit(),
    _A(A),
    _B(B),
    _Ci(Ci),
    _sum(EightBitData()),
    _carry(false)
{}

EightBitAdder::~EightBitAdder(void)
{}

bool EightBitAdder::process(void)
{
    FullAdder fa1(_A.data.bits.B0, _B.data.bits.B0, _Ci);
    fa1.process();
    _sum.data.bits.B0 = fa1.sum();
    FullAdder fa2(_A.data.bits.B1, _B.data.bits.B1, fa1.carry());
    fa2.process();
    _sum.data.bits.B1 = fa2.sum();
    FullAdder fa3(_A.data.bits.B2, _B.data.bits.B2, fa2.carry());
    fa3.process();
    _sum.data.bits.B2 = fa3.sum();
    FullAdder fa4(_A.data.bits.B3, _B.data.bits.B3, fa3.carry());
    fa4.process();
    _sum.data.bits.B3 = fa4.sum();
    FullAdder fa5(_A.data.bits.B4, _B.data.bits.B4, fa4.carry());
    fa5.process();
    _sum.data.bits.B4 = fa5.sum();
    FullAdder fa6(_A.data.bits.B5, _B.data.bits.B5, fa5.carry());
    fa6.process();
    _sum.data.bits.B5 = fa6.sum();
    FullAdder fa7(_A.data.bits.B6, _B.data.bits.B6, fa6.carry());
    fa7.process();
    _sum.data.bits.B6 = fa7.sum();
    FullAdder fa8(_A.data.bits.B7, _B.data.bits.B7, fa7.carry());
    fa8.process();
    _sum.data.bits.B7 = fa8.sum();

    _carry = fa8.carry();
    LogicXORGate XOR(_carry, fa7.carry());
    _overflow = XOR.process();

    return true;
}