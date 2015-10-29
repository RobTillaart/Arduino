#ifndef CountDown_h
#define CountDown_h
//
//    FILE: CountDown.h
//  AUTHOR: Rob Tillaart
// PURPOSE: CountDown library for Arduino
// HISTORY: See CountDown.cpp
//     URL:
//
// Released to the public domain
//

#define COUNTDOWN_LIB_VERSION "0.1.00"

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class CountDown
{
public:
    enum State { RUNNING, STOPPED };
    enum Resolution { MILLIS, MICROS, SECONDS };

    explicit CountDown(const enum Resolution res = MILLIS);
    void setResolution(const enum Resolution res = MILLIS);

    void start(uint32_t ticks);
    // void start(uint16_t h, uint8_t m, uint8_t s);
    void stop();
    unsigned long remaining();
    bool isRunning() const             { return _state == CountDown::RUNNING; };
    enum Resolution resolution() const { return _res; };

private:
    uint32_t _ticks;
    uint32_t _remaining;
    enum State _state;
    enum Resolution _res;
    unsigned long _starttime;

    void calcRemaining();
    unsigned long (*_gettime)(void);
    static unsigned long seconds() { return millis() / 1000; };
};

#endif
// END OF FILE