#include "Clock.h"
#include <stdio.h>

Clock::Clock()
{

}

Clock::~Clock()
{

}

void Clock::step()
{
    this->rise();
    this->high();
    this->fall();
    this->low();
}

void Clock::autoStep()
{

}

void Clock::rise()
{
    printf("Clock rise\n");
    this->currentClockState = CLOCK_RISE;
}

void Clock::high()
{
    printf("Clock high\n");
    this->currentClockState = CLOCK_HIGH;
    // remain high for pulse width
}

void Clock::fall()
{
    printf("Clock fall\n");
    this->currentClockState = CLOCK_FALL;
}

void Clock::low()
{
    printf("Clock low\n");
    this->currentClockState = CLOCK_LOW;
    // remain low for pulse width
}

int main()
{
    Clock clock;
    clock.step();
}