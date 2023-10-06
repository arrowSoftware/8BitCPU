#ifndef __CounterRegister_H__
#define __CounterRegister_H__

#include "DataBus.hpp"

template <class T>
class CounterRegister
{
    public:
        CounterRegister(DataBus<T> *dataBus) : _dataBus(dataBus), _clock(false), _data(0)  {}

        ~CounterRegister(void) {}

        void clock(bool high) {
            _clock = high;
        }

        void load(void) {
            if (_clock) {
                _data = _dataBus->read();
            }
        }

        void reset(void) {
            _data = 0;
        }

        void enable(void) {
            if (_clock) {
                _data += 1;
            }
        }

        void output(void) {
            _dataBus->load(_data);
        }

        T peak(void) {
            return _data;
        }

    protected:
    private:
        DataBus<T> *_dataBus;
        bool _clock;
        T _data;
};

#endif // __CounterRegister_H__