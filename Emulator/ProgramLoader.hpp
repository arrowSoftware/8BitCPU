#ifndef __ProgramLoader_H__
#define __ProgramLoader_H__

#include "CounterRegister.hpp"
#include "ROM.hpp"
#include "DataBus.hpp"

#include <stdio.h>

template <class T>
class ProgramLoader
{
    public:
        ProgramLoader(DataBus<T> *dataBus, ROM<T> *rom) : 
            _rom(rom),
            _counter(dataBus), 
            _dataBus(dataBus), 
            _addressWrite(true), 
            _dataWrite(false),
            _firstEnable(true),
            _clock(false),
            _reset(false) {

        }

        ~ProgramLoader(void) {}         

        void enable() {
            if (_firstEnable) {
                _firstEnable = false;
                // send the current counter values to the data bus.
                _dataBus->load(_counter.peak());
            }
        }
        
        void reset() {
            _counter.reset();
            _clock = false;
            // maybe use a clock class pointer that all uses.
            // reset turns the clock off. TODO
            _reset = true;
        }

        void clock(bool high) {
            _clock = high;
            _counter.clock(high);

            if (_clock) {   
                _addressWrite = !_addressWrite;
                _dataWrite = !_dataWrite;
            }

            if (_addressWrite && _clock) {
                // Dont incremenet the counter if we just reset, we need to consume the 0 count.
                if (!_reset) {
                    _counter.enable();
                }
                _dataBus->load(_counter.peak());
            } else if (_dataWrite && _clock) {
                // Get the count from the counter and write it to the data bus.
                _dataBus->load(_rom->read(_counter.peak()));
            }

            if (_clock) {
                _reset = false;
            }
        }

    protected:
    private:
        ROM<T> *_rom;
        CounterRegister<T> _counter;
        DataBus<T> *_dataBus;
        bool _addressWrite;
        bool _dataWrite;
        bool _firstEnable;
        bool _clock;
        bool _reset;
};

#endif // __ProgramLoader_H__                                   