#ifndef __Circuit_H__
#define __Circuit_H__

class Circuit
{
    public:
        Circuit(void) {};
        virtual ~Circuit(void) {};

    protected:
        virtual bool process(void) = 0;
};

#endif // __Circuit_H__