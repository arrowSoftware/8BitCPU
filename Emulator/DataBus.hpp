#ifndef __DataBus_H__
#define __DataBus_H__

#include <stdint.h>

template <class T>
class DataBus
{
    public:
        DataBus(void) {
            _size = sizeof(_size) * 8;
        }
        ~DataBus(void) {}

        void load(T data) {
            _data = data;
        }

        T read(void) {
            return _data;
        }

        uint8_t size(void) {
            return _size;
        }
    protected:
    private:
        uint8_t _size;
        T _data;
};
#endif // __DataBus_H__