// 
//    FILE: StopWatch.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.03
// PURPOSE: Simple StopWatch library for Arduino
//
// The library is based upon millis() and therefore
// has the same restrictions as millis() has wrt overflow.
//
// HISTORY: 
// 0.1.00 - 2011-01-04 initial version
// 0.1.01 - 2011-01-04 Added better state
// 0.1.02 - 2011-06-15 Added state() + #defines + lib version
// 0.1.03 - 2012-01-22 Added several improvements
//             By mromani & Rob Tillaart
// 
// Released to the public domain
//

#include "StopWatch.h"

StopWatch::StopWatch(enum Resolution res)
{
    _res = res;
    switch(_res) {
        case MICROS:
            _gettime = micros;
            break;
        case MILLIS:
            _gettime = millis;
            break;
        case SECONDS:
            _gettime = seconds;
            break;
        default:  
            _gettime = millis;
            break;
    }
    reset();
}

void StopWatch::reset()
{
    _state = StopWatch::RESET;
    _starttime = _stoptime = 0;
}

void StopWatch::start()
{
    if (_state == StopWatch::RESET || _state == StopWatch::STOPPED)
    {
        _state = StopWatch::RUNNING;
        unsigned long t = _gettime();
        _starttime += t - _stoptime;
        _stoptime = t;
    }
}

unsigned long StopWatch::value()
{
    if (_state == StopWatch::RUNNING) _stoptime = _gettime();
    return _stoptime - _starttime;
}

void StopWatch::stop()
{
    if (_state == StopWatch::RUNNING)
    {
        _state = StopWatch::STOPPED;
        _stoptime = _gettime();
    }
}

bool StopWatch::isRunning()
{
    return (_state == StopWatch::RUNNING);
}

enum StopWatch::State StopWatch::state()
{
    return _state;
}
// END OF FILE