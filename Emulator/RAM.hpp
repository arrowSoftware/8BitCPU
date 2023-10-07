#ifndef __RAM_H__
#define __RAM_H__

#include "DataBus.hpp"
#include "Register.hpp"

template <class T>
class RAM
{
    public:
        RAM(DataBus<T> *dataBus, Register<T> *memoryRegister) : 
            _dataBus(dataBus), 
            _clock(false),
            _memoryRegister(memoryRegister) {
            memset(_data, 0x0, 256);
        }

        ~RAM(void) {}

        void clock(bool high) {
            _clock = high;
        }

        void reset() {
            memset(_data, 0x0, 256);
        }

        void write(void) {
            // read data from the data bus and store it into the ram and the current address.
            int address = _memoryRegister->peak();
            if (address < 256) {
                _data[address] = _dataBus->read();
            }
        }

        T read(void) {
            int address = _memoryRegister->peak();
            // write data to the data bus from ram
            if (address < 256) {
                _dataBus->load(_data[address]);
            }

        }
    protected:
    private:
        DataBus<T> *_dataBus;
        Register<T> *_memoryRegister;
        T _data[256];
        bool _clock;
};

#endif // __RAM_H__