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

void LogicANDGate::update(bool A, bool B)
{
    _A = A;
    _B = B;
}

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

void LogicORGate::update(bool A, bool B)
{
    _A = A;
    _B = B;
}

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

void LogicXORGate::update(bool A, bool B)
{
    _A = A;
    _B = B;
}

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

void LogicNOTGate::update(bool A)
{
    _A = A;
}

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

void LogicNANDGate::update(bool A, bool B)
{
    _A = A;
    _B = B;
}

bool LogicNANDGate::process()
{
    _Q = !(_A & _B);
    return _Q;
}

// NAND 3 input

LogicNANDGate3::LogicNANDGate3(bool A, bool B, bool C) : LogicGate(A, B), _C(C)
{}

LogicNANDGate3::~LogicNANDGate3(void)
{}

void LogicNANDGate3::update(bool A, bool B, bool C)
{
    _A = A;
    _B = B;
    _C = C;
}

bool LogicNANDGate3::process()
{
    _Q = !(_A & _B & _C);
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

void LogicXNORGate::update(bool A, bool B)
{
    _A = A;
    _B = B;
}

bool LogicXNORGate::process()
{
    _Q = (_A == _B);
    return _Q;
}