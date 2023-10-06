#include "DFlipFlop.h"
#include "LogicGate.h"
#include <stdio.h>

DFlipFlop::DFlipFlop(bool enable, bool A, bool S, bool R) :
    _enable(enable), _A(A), _S(S), _R(R), _Q(false), _QB(true), _lastEnable(false), _lastA(false)
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
    if (_enable && !_lastEnable)
    {
        _Q = _lastA;
        _QB = !_lastA;
    }

    if (!_S || !_R)
    {
        _Q = !_S;
        _QB = !_R;
    }

    _lastEnable = _enable;
    _lastA = _A;

    return true;
}