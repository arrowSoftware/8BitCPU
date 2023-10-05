#ifndef __FullAdder_H__
#define __FullAdder_H__

#include "Circuit.h"

class FullAdder : public Circuit
{
    public:
        FullAdder(bool A, bool B, bool Ci);
        ~FullAdder(void);

        inline bool sum() { return _sum; }
        inline bool carry() { return _carry; }

        bool process(void);

    protected:
        bool _A;
        bool _B;
        bool _Ci;

        bool _sum;
        bool _carry;
};

#endif // __FullAdder_H__