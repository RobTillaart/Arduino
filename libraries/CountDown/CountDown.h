#pragma once
//
//    FILE: CountDown.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.6
// PURPOSE: CountDown library for Arduino
//     URL: https://github.com/RobTillaart/CountDown
//


#include "Arduino.h"

#define COUNTDOWN_LIB_VERSION               (F("0.2.6"))


class CountDown
{
public:
    enum Resolution { MILLIS, MICROS, SECONDS, MINUTES };

    explicit CountDown(const enum Resolution res = MILLIS);

    void     setResolution(const enum Resolution res = MILLIS);

    bool     start(uint32_t ticks);
             // Implicit set resolution to SECONDS.
    bool     start(uint8_t days, uint16_t hours, uint32_t minutes, uint32_t seconds);
             // Implicit set resolution to MINUTES.
    bool     start(uint8_t days, uint16_t hours, uint32_t minutes);

    void     stop();
    void     cont();

    uint32_t remaining();
    bool     isRunning();
    enum     Resolution resolution() const  { return _res; };

private:
    enum State { RUNNING, STOPPED };

    uint32_t        _ticks;
    uint32_t        _remaining;
    enum State      _state;
    enum Resolution _res;
    uint32_t        _starttime;
    void            calcRemaining();
};


// -- END OF FILE --
