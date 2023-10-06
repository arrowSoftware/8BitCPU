#ifndef __HalfAdder_H__
#define __HalfAdder_H__

#include "Circuit.h"

class HalfAdder : public Circuit
{
    public:
        HalfAdder(bool A, bool B);
        ~HalfAdder(void);

        inline bool sum() { return _sum; }
        inline bool carry() { return _carry; }

        bool process(void);

    protected:
        bool _A;
        bool _B;

        bool _sum;
        bool _carry;
};

#endif // __HalfAdder_H__