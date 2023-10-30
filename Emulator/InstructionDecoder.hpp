#ifndef __InstructionDecoder_H__
#define __InstructionDecoder_H__

#include "DataBus.hpp"
#include "Register.hpp"
#include "ALU.hpp"
#include "RAM.hpp"
#include "ROM.hpp"
#include "CounterRegister.hpp"

template <class T>
class InstructionDecoder
{
    public:
        InstructionDecoder(DataBus<T> *dataBus,
            Register<T> *aRegister,
            Register<T> *bRegister,
            Register<T> *memRegister,
            Register<T> *pcRegister,
            Register<T> *outRegister,
            Register<T> *flagsRegister,
            CounterRegister<T> *instructionRegister,
            ALU<T> *alu,
            RAM<T> *ram,
            ROM<T> *rom,
        ) :
        _dataBus(dataBus),
        _aRegister(aRegister),
        _bRegister(bRegister),
        _memRegister(memRegister),
        _pcRegister(pcRegister),
        _outRegister(outRegister),
        _flagsRegister(flagsRegister),
        _instructionRegister(instructionRegister),
        _alu(alu),
        _ram(ram),
        _rom(rom),
        _clock(false) {
        }
        ~InstructionDecoder(void) {}

        bool clock(bool high) {
            _clock = high;
            _outRegister->clock(high);
            _pcRegister->clock(high);
            _instructionRegister->clock(high);
            _memRegister->clock(high);
            _aRegister->clock(high);
            _bRegister->clock(high);
            _flagsRegister->clock(high);
        }

        void reset(void) {

        }

        bool OI(void) {
            _outRegister->load();
        }
        bool JP(void) {
            _pcRegister->load();
        }
        bool CO(void) {
            _pcRegister->output();
        }
        bool CE(void) {
            _pcRegister->enable();
        }
        bool IR(void) {
            _instructionRegister->reset();
        }
        bool II(void) {
            _instructionRegister->load();
        }
        bool RR(void) {
            _ram->read();
        }
        bool RW(void) {
            _ram->write();
        }
        bool MI(void) {
            _memRegister->load();
        }
        bool BO(void) {
            _bRegister->output();
        }
        bool BI(void) {
            _bRegister->load();
        }
        bool CI(void) {
            _pcRegister->load();
        }
        bool EO(void) {
            _alu->output();
        }
        bool SEL1(int en) {
            _alu->SEL1(en);
        }
        bool SEL2(int en) {
            _alu->SEL2(en);
        }
        bool SEL3(int en) {
            alu->SEL3(en);
        }
        bool AO(void) {
            _aRegister->output();
        }
        bool AI(void) {
            _aRegister->load();
        }
        bool HLT(void) {
            // TODO
        }
        bool FI(void) {
            _flagsRegister->load();
        }

    protected:
    private:
        Register<T> *_aRegister;
        Register<T> *_bRegister;
        Register<T> *_memRegister;
        Register<T> *_pcRegister;
        Register<T> *_outRegister;
        Register<T> *_flagsRegister;
        CounterRegister<T> *_instructionRegister;
        ALU<T> *_alu;
        RAM<T> *_ram;
        ROM<T> *_rom;

        // 8 columns of 6 bytes each
        static const int INSTRUCTION_SET_MAP_COLUMNS = 8;
        static const int CONTROL_FLAG_SIZE_BYES = 6;
        static const int INSTRUCTION_SET_SIZE = INSTRUCTION_SET_MAP_COLUMNS*CONTROL_FLAG_SIZE_BYES;
        //controlFlags controlFlagROM[512];
        DataBus<T> *_dataBus;
        bool _clock;
        // inputs
        bool _VF;
        bool _ZF;
        bool _CF;
        bool _OP0;
        bool _OP1;
        bool _OP2;
        bool _OP3;
        bool _OP4;
        bool _PM;
        // outputs
        bool _OI;
        bool _JP;
        bool _CO;
        bool _CE;
        bool _IR;
        bool _II;
        bool _RR;
        bool _RW;
        bool _MI;
        bool _BO;
        bool _BI;
        bool _CI;
        bool _EO;
        bool _SEL1;
        bool _SEL2;
        bool _SEL3;
        bool _AO;
        bool _AI;
        bool _HLT;
        bool _FI;

};

#endif // __InstructionDecoder_H__