#ifndef __DFlipFlop_H__
#define __DFlipFlop_H__

#include "Circuit.h"

class DFlipFlop : public Circuit
{
    public:
        DFlipFlop(bool enable, bool A, bool S, bool R);
        ~DFlipFlop();

        inline bool Q(void) { return _Q; }
        inline bool QB(void) { return _QB; }

        void update(bool enable, bool A, bool S, bool R);
        bool process(void);
    private:
        bool _enable;
        bool _A;
        bool _S;
        bool _R;
        bool _Q;
        bool _QB;
};

#endif // __DFlipFlop_H__