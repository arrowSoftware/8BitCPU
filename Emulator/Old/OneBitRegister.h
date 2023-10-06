#ifndef __OneBitRegister_H__
#define __OneBitRegister_H__

#include "Circuit.h"

class OneBitRegister : public Circuit
{
    public:
        OneBitRegister();
        ~OneBitRegister();

        bool process();
    protected:
        bool _enable;
        bool _load;
        bool _data;
        bool _set;
        bool _reset;
        bool _Q;
        bool _QB;
};

#endif // __OneBitRegister_H__