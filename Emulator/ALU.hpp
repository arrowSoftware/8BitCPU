#ifndef __ALU_H__
#define __ALU_H__

#include "DataBus.hpp"
#include "Register.hpp"

template <class T>
class ALU
{
    public:
        ALU(DataBus<T> *dataBus, Register<T> *aRegister, Register<T> *bRegister) :
            _dataBus(dataBus),
            _aRegister(aRegister),
            _bRegister(bRegister),
            _aluSelect1(0),
            _aluSelect2(0),
            _aluSelect3(0),
            _Ci(0) {

        }
        ~ALU(void) {

        }

        void SEL1(int sel) { _aluSelect1 = sel; }
        void SEL2(int sel) { _aluSelect2 = sel; }
        void SEL3(int sel) { _aluSelect3 = sel; }
        void CI(bool enable) { _Ci = enable; }

        void OR(void) {
            _data = _aRegister->peak() | _bRegister->peak();
        }
        void AND(void) {
            _data = _aRegister->peak() & _bRegister->peak();
        }
        void XOR(void) {
            _data = _aRegister->peak() ^ _bRegister->peak();
        }
        void ADD(void) {
            _data = _aRegister->peak() + _bRegister->peak();
        }
        void SUB(void) {
            _data = _aRegister->peak() - _bRegister->peak();
        }
        void NOTA(void) {
            _data = ~_aRegister->peak();
        }

        void enable(void) {
            int aluSelect = _aluSelect1 | _aluSelect2 | _aluSelect3;
            switch (aluSelect) {
                case 0: { OR(); break; }
                case 1: { NOTA(); break; }
                case 2: { /* A + NOT B + Ci */ break; }
                case 3: { SUB(); break; }
                case 4: { XOR(); break;}
                case 5: { AND(); break;}
                case 6: { /* A - 1 + Ci */ break; }
                default: { break; }
            }

            _data = _aRegister->peak() + _bRegister->peak();
        }

        void output(void) {
            _dataBus->load(_data);
        }

        T peak(void) {
            return _data;
        }
    protected:
    private:
        DataBus<T> *_dataBus;
        T _data;
        Register<T> *_aRegister;
        Register<T> *_bRegister;
        int _aluSelect1;
        int _aluSelect2;
        int _aluSelect3;
        int _Ci;
};

#endif // __ALU_H__