#ifndef __EightBitAdder_H__
#define __EightBitAdder_H__

#include "Circuit.h"
#include "EightBitData.h"

class EightBitAdder : public Circuit
{
    public:
        EightBitAdder(EightBitData A, EightBitData B, bool Ci);
        ~EightBitAdder(void);

        inline EightBitData sum() { return _sum; }
        inline bool carry() { return _carry; }
        inline bool overflow() { return _overflow; }

        bool process(void);

    protected:
        EightBitData _A;
        EightBitData _B;
        bool _Ci;

        EightBitData _sum;
        bool _carry;
        bool _overflow;
};

#endif // __EightBitAdder_H__