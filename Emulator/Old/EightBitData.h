#ifndef __EightBitData_H__
#define __EightBitData_H__

struct EightBits
{
    bool B0:1;
    bool B1:1;
    bool B2:1;
    bool B3:1;
    bool B4:1;
    bool B5:1;
    bool B6:1;
    bool B7:1;
};

union EightBit
{
    unsigned char byte;
    EightBits bits;
};

struct EightBitData
{
    EightBitData()
    {
        data.byte = 0;
    }

    void set(unsigned char argData)
    {
        data.byte = argData;
    }
    unsigned char byte()
    {
        return data.byte;
    }
    
    EightBit data;
};

#endif // __EightBitData_H__