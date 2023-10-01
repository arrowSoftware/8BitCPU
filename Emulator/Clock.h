#ifndef __CLOCK_H__
#define __CLOCK_H__

typedef enum ClockState
{
    CLOCK_LOW,
    CLOCK_RISE,
    CLOCK_HIGH,
    CLOCK_FALL
} ClockState_t;

class Clock
{
    public:
        Clock(void);
        ~Clock();
        void step();
        void autoStep();

    private:

        void rise();
        void high();
        void fall();
        void low();

        int period;
        int amplitude;
        int pulseWidth;

        ClockState_t currentClockState;
};

#endif // __CLOCK_H__
