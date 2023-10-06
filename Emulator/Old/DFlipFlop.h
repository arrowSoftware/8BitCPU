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
        inline void setQ(bool Q) {_Q = Q;}
        inline void setQB(bool QB) {_QB = QB;}
        bool process(void);
    private:
        bool _enable; // Edge triggered pulse
        bool _A;
        bool _S;
        bool _R;
        bool _Q;
        bool _QB;
        bool _lastEnable;
        bool _lastA;
};

#endif // __DFlipFlop_H__