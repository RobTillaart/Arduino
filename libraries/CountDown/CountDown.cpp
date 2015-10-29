//
//    FILE: CountDown.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.00
// PURPOSE: CountDown library for Arduino
//
// The library is based upon millis() and therefore
// has the same restrictions as millis() has wrt overflow.
//
// HISTORY:
// 0.1.00 - 2015-10-27 initial version
//
// Released to the public domain
//

#include "CountDown.h"

CountDown::CountDown(const enum Resolution res)
{
    setResolution(res);
    stop();
}

void CountDown::setResolution(const enum Resolution res)
{
    _res = res;
    switch(_res)
    {
    case MICROS:
        _gettime = micros;
        break;
    case SECONDS:
        _gettime = seconds;
        break;
    case MILLIS:
    default:
        _gettime = millis;
        break;
    }
}

void CountDown::start(uint32_t ticks)
{
    _state = CountDown::RUNNING;
    _starttime = _gettime();
    _ticks = ticks;
}

unsigned long CountDown::remaining()
{
    calcRemaining();
    return _remaining;
}

void CountDown::stop()
{
    calcRemaining();
    _state = CountDown::STOPPED;
}

void CountDown::calcRemaining()
{
    if (_state == CountDown::RUNNING)
    {
        uint32_t t = _gettime() - _starttime;
        _remaining = _ticks > t? _ticks - t: 0;
        if (_remaining == 0)
        {
            _state = CountDown::STOPPED;
        }
    }
}
// END OF FILE