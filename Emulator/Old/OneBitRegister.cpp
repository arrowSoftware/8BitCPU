#include "OneBitRegister.h"
#include "LogicGate.h"
#include "DFlipFlop.h"

OneBitRegister::OneBitRegister()
{}

OneBitRegister::~OneBitRegister()
{}

bool OneBitRegister::process()
{
    LogicANDGate AND1(false, false);
    LogicANDGate AND2(false, false);
    LogicORGate OR(false, false);
    LogicNOTGate NOT(false);
    DFlipFlop flipflop(false, false, false, false);

    AND1.update(flipflop.Q(), NOT.process());
    AND2.update(_load, _data);
    OR.update(AND1.process(), AND2.process());
    NOT.update(_load);
    flipflop.update(_enable, OR.process(), _set, _reset);
}