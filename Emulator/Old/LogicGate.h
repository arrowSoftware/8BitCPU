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
        void update(bool A, bool B);
};

class LogicORGate : public LogicGate
{
    public:
        LogicORGate(bool A, bool B);
        ~LogicORGate(void);

        bool process();
        void update(bool A, bool B);
};

class LogicXORGate : public LogicGate
{
    public:
        LogicXORGate(bool A, bool B);
        ~LogicXORGate(void);

        bool process();
        void update(bool A, bool B);
};

class LogicNOTGate : public LogicGate
{
    public:
        LogicNOTGate(bool A);
        ~LogicNOTGate(void);

        bool process();
        void update(bool A);
};

class LogicNANDGate : public LogicGate
{
    public:
        LogicNANDGate(bool A, bool B);
        ~LogicNANDGate(void);

        bool process();
        void update(bool A, bool B);
};

class LogicNANDGate3 : public LogicGate
{
    public:
        LogicNANDGate3(bool A, bool B, bool C);
        ~LogicNANDGate3(void);

        bool process();
        void update(bool A, bool B, bool C);
    protected:
        bool _C;
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
        void update(bool A, bool B);
};
#endif // __LogicGate_H__