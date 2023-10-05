#ifndef __LogicGate_H__
#define __LogicGate_H__

class LogicGate
{
    public:
        LogicGate(bool A, bool B);
        virtual ~LogicGate(void);

    protected:
        virtual bool process() = 0;

        bool _A;
        bool _B;
        bool _Q;
};

class LogicANDGate : public LogicGate
{
    public:
        LogicANDGate(bool A, bool B);
        ~LogicANDGate(void);

        bool process();
};

class LogicORGate : public LogicGate
{
    public:
        LogicORGate(bool A, bool B);
        ~LogicORGate(void);

        bool process();
};

class LogicXORGate : public LogicGate
{
    public:
        LogicXORGate(bool A, bool B);
        ~LogicXORGate(void);

        bool process();
};

class LogicNOTGate : public LogicGate
{
    public:
        LogicNOTGate(bool A);
        ~LogicNOTGate(void);

        bool process();
};

class LogicNANDGate : public LogicGate
{
    public:
        LogicNANDGate(bool A, bool B);
        ~LogicNANDGate(void);

        bool process();
};

class LogicNORGate : public LogicGate
{
    public:
        LogicNORGate(bool A, bool B);
        ~LogicNORGate(void);

        bool process();
        void update(bool A, bool B);
};

class LogicXNORGate : public LogicGate
{
    public:
        LogicXNORGate(bool A, bool B);
        ~LogicXNORGate(void);

        bool process();
};
#endif // __LogicGate_H__