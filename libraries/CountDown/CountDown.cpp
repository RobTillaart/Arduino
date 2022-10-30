//
//    FILE: CountDown.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.7
// PURPOSE: CountDown library for Arduino
//     URL: https://github.com/RobTillaart/CountDown
//
//  HISTORY: see changelog.md


#include "CountDown.h"


CountDown::CountDown(const enum Resolution res)
{
  setResolution(res);
  stop();
}


void CountDown::setResolution(const enum Resolution res)
{
  _res = res;
  _ticks = 0;
}


bool CountDown::start(uint32_t ticks)
{
  _ticks = ticks;
  _state = CountDown::RUNNING;
  if (_res == MICROS)
  {
    _starttime = micros();
  }
  else 
  {
    _starttime = millis();
  }
  return true;  // can not overflow
}


bool CountDown::start(uint8_t days, uint16_t hours, uint32_t minutes, uint32_t seconds)
{
  float _days = seconds / 86400.0 + minutes / 1440.0 + hours / 24.0 + days; 
  bool rv = (_days < 49.7102696);

  uint32_t ticks = 86400UL * days + 3600UL * hours + 60UL * minutes + seconds;
  if (ticks > 4294967) ticks = 4294967;  // prevent underlying millis() overflow
  setResolution(SECONDS);
  start(ticks);

  return rv;
}


bool CountDown::start(uint8_t days, uint16_t hours, uint32_t minutes)
{
  float _days = minutes / 1440.0 + hours / 24.0 + days; 
  bool rv = (_days < 49.7102696);

  uint32_t ticks = 86400UL * days + 3600UL * hours + 60UL * minutes;
  if (ticks > 4294967) ticks = 4294967;  // prevent underlying millis() overflow
  setResolution(MINUTES);
  start(ticks);

  return rv;
}


void CountDown::stop()
{
  calcRemaining();
  _state = CountDown::STOPPED;
}


void CountDown::cont()
{
  if (_state == CountDown::STOPPED)
  {
    start(_remaining);
  }
}


bool CountDown::isRunning() 
{
  calcRemaining();
  return (_state == CountDown::RUNNING);
}


uint32_t CountDown::remaining()
{
  calcRemaining();
  if (_remaining == 0) _state = CountDown::STOPPED;
  return _remaining;
}


void CountDown::calcRemaining()
{
  uint32_t t = 0;
  if (_state == CountDown::RUNNING)
  {
    switch(_res)
    {
      case MINUTES:
        t = (millis() - _starttime) / 60000UL;
        break;
      case SECONDS:
        t = (millis() - _starttime) / 1000UL;;
        break;
      case MICROS:
        t = micros() - _starttime;
        break;
      case MILLIS:
      default:
        t = millis() - _starttime;
        break;
    }
    _remaining = _ticks > t ? _ticks - t : 0;
    if (_remaining == 0) 
    {
      _state = CountDown::STOPPED;
    }
    return;
  }
  // do not change
}


// -- END OF FILE --
