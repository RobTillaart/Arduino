//
//    FILE: StopWatch.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.2
//    DATE: 2011-01-04
// PURPOSE: Arduino Library implementing a stopwatch including seconds, milliseconds microseconds
//     URL: https://github.com/RobTillaart/StopWatch_RT
//
// The library is based upon millis() and therefore
// has the same restrictions as millis() has wrt overflow.
//
// HISTORY:
// 0.1.00 2011-01-04 initial version
// 0.1.01 2011-01-04 Added better state
// 0.1.02 2011-06-15 Added state() + #defines + lib version
// 0.1.03 2012-01-22 Added several improvements
//             By mromani & Rob Tillaart
// 0.1.4  2017-07-16 refactored
// 0.1.5  2017-09-13 removed const from functions
// 0.2.0  2020-05-07 updated metadata, removed pre 1.0 support; setResolution added, minutes added
// 0.2.1  2020-06-19 fix library.json
// 0.2.2  2020-07-14 fix #3 ESP support
//

#include "StopWatch.h"

StopWatch::StopWatch(const enum Resolution res)
{
  setResolution(res);
}

void StopWatch::setResolution(const enum Resolution res)
{
  reset();
  _res = res;
  switch(_res)
  {
  case MICROS:
    _gettime = _micros;
    break;

  case SECONDS:
    _gettime = seconds;
    break;

  case MINUTES:
    _gettime = minutes;
    break;

  case MILLIS:
  default:
    _gettime = _millis;
    _res = MILLIS;      // for default!
    break;
  }
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
    uint32_t t = _gettime();
    _starttime += t - _stoptime;
    _stoptime = t;
  }
}

uint32_t StopWatch::elapsed()
{
  if (_state == StopWatch::RUNNING)
  {
    _stoptime = _gettime();
  }
  return _stoptime - _starttime;
}

void StopWatch::stop()
{
  if (_state == StopWatch::RUNNING)
  {
    _stoptime = _gettime();
    _state = StopWatch::STOPPED;
  }
}

// -- END OF FILE --
