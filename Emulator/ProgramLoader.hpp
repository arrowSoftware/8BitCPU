#ifndef __ProgramLoader_H__
#define __ProgramLoader_H__

#include "CounterRegister.hpp"
#include "ROM.hpp"
#include "DataBus.hpp"

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
            _firstEnable(true) {

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
        }

        void clock(bool high) {
            _counter.clock(high);

            if (high) {   
                _addressWrite = !_addressWrite;
                _dataWrite = !_dataWrite;
            }

            if (_addressWrite && high) {
                _counter.enable();
                _dataBus->load(_counter.peak());
            } else if (_dataWrite && high) {
                // Get the count from the counter and write it to the data bus.
                _dataBus->load(_rom->read(_counter.peak()));
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
};

#endif // __ProgramLoader_H__                                   