#include "DLatch.h"
#include "LogicGate.h"
#include <stdio.h>

DLatch::DLatch(bool enable, bool A) : _enable(enable), _A(A), _Q(false), _QB(true)
{}

DLatch::~DLatch()
{}

void DLatch::update(bool enable, bool A)
{
    _enable = enable;
    _A = A;
}

bool DLatch::process()
{
    LogicNOTGate NOT(_A);
    LogicANDGate AND1(NOT.process(), _enable);
    LogicANDGate AND2(_A, _enable);
    LogicNORGate NOR1(AND1.process(), _QB);
    LogicNORGate NOR2(AND2.process(), _Q);

    // Only process second set of gates if the enable is set.
    if (_enable == true)
    {
        _Q = NOR1.process();
        _QB = NOR2.process();
        // Run the NOR process twice to simulate a clock high signal.  This is to avoid the race condition of Q and ~Q
        NOR1.update(AND1.process(), _QB);
        NOR2.update(AND2.process(), _Q);
        _Q = NOR1.process();
        _QB = NOR2.process();
    }
    return true;
}