#ifndef __ROM_H__
#define __ROM_H__

#include <cstring>

template <class T>
class ROM
{
    public:
        ROM(void) {
            memset(_data, 0x0, 512);
        }

        ~ROM(void) {

        }

        void program(T *programData, int bytes) {
            if (bytes > 512) {
                bytes = 512;
            }
            memcpy(&_data[0], programData, bytes);
        }
        T read(int address) {
            if (address < 512) {
                return _data[address];
            }
            return 0;
        }
    protected:
    private:
        T _data[512];
};

#endif // __ROM_H__