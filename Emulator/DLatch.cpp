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
    printf("NOT A = %d\n", NOT.process());
    LogicANDGate AND1(NOT.process(), _enable);
    LogicANDGate AND2(_A, _enable);
    printf("AND1 = %d\n", AND1.process());
    printf("AND2 = %d\n", AND2.process());
    printf("Q = %d\n", _Q);
    printf("QB = %d\n", _QB);
    LogicNORGate NOR1(AND1.process(), !_QB);
    LogicNORGate NOR2(AND2.process(), !_Q);
    // try while loop, holding 1 active for few iterations
    _Q = NOR1.process();
    _QB = NOR2.process();

    printf("Q = %d\n", _Q);
    printf("QB = %d\n", _QB);
    return true;
}