#ifndef __OneBitRegister_H__
#define __OneBitRegister_H__

#include "Circuit.h"

class OneBitRegister : public Circuit
{
    public:
        OneBitRegister();
        ~OneBitRegister();
    
        bool process();
};

#endif // __OneBitRegister_H__