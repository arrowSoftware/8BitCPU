#ifndef __DLatch_H__
#define __DLatch_H__

#include "Circuit.h"

class DLatch : public Circuit
{
    public:
        DLatch(bool enable, bool A);
        ~DLatch();

        inline bool Q(void) { return _Q; }
        inline bool QB(void) { return _QB; }

        void update(bool enable, bool A);
        bool process(void);
    private:
        bool _enable;
        bool _A;
        bool _Q;
        bool _QB;
};

#endif // __DLatch_H__