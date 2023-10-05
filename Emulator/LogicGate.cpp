#include "LogicGate.h"
#include <stdio.h>

LogicGate::LogicGate(bool A, bool B) : _A(A), _B(B), _Q(false)
{}

LogicGate::~LogicGate(void)
{}

// AND

LogicANDGate::LogicANDGate(bool A, bool B) : LogicGate(A, B)
{}

LogicANDGate::~LogicANDGate(void)
{}

bool LogicANDGate::process()
{
    _Q = (_A & _B);
    return _Q;
}

// OR

LogicORGate::LogicORGate(bool A, bool B) : LogicGate(A, B)
{}

LogicORGate::~LogicORGate(void)
{}

bool LogicORGate::process()
{
    _Q = (_A | _B);
    return _Q;
}

// XOR

LogicXORGate::LogicXORGate(bool A, bool B) : LogicGate(A, B)
{
}

LogicXORGate::~LogicXORGate(void)
{}

bool LogicXORGate::process()
{
    _Q = (_A ^ _B);

    return _Q;
}

// NOT

LogicNOTGate::LogicNOTGate(bool A) : LogicGate(A, false)
{}

LogicNOTGate::~LogicNOTGate(void)
{}

bool LogicNOTGate::process()
{
    _Q = (!_A);
    return _Q;
}

// NAND

LogicNANDGate::LogicNANDGate(bool A, bool B) : LogicGate(A, B)
{}

LogicNANDGate::~LogicNANDGate(void)
{}

bool LogicNANDGate::process()
{
    _Q = !(_A & _B);
    return _Q;
}

// NOR

LogicNORGate::LogicNORGate(bool A, bool B) : LogicGate(A, B)
{}

LogicNORGate::~LogicNORGate(void)
{}

void LogicNORGate::update(bool A, bool B)
{
    _A = A;
    _B = B;
}

bool LogicNORGate::process()
{
    _Q = !(_A | _B);
    return _Q;
}

// XNOR

LogicXNORGate::LogicXNORGate(bool A, bool B) : LogicGate(A, B)
{}

LogicXNORGate::~LogicXNORGate(void)
{}

bool LogicXNORGate::process()
{
    _Q = (_A == _B);
    return _Q;
}