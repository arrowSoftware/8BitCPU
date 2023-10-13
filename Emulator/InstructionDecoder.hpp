#ifndef __InstructionDecoder_H__
#define __InstructionDecoder_H__

#include "DataBus.hpp"

template <class T>
class InstructionDecoder
{
    public:
        InstructionDecoder(DataBus<T> *dataBus) : 
        _dataBus(dataBus),
        _clock(false) {
        }
        ~InstructionDecoder(void);

        bool clock(bool high) {
            _clock = high;
        }

        void reset(void) {

        }

    protected:
    private:
        // 8 columns of 6 bytes each
        static const int INSTRUCTION_SET_MAP_COLUMNS = 8;
        static const int CONTROL_FLAG_SIZE_BYES = 6;
        static const int INSTRUCTION_SET_SIZE = INSTRUCTION_SET_MAP_COLUMNS*CONTROL_FLAG_SIZE_BYES;
        controlFlags controlFlagROM[512];
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