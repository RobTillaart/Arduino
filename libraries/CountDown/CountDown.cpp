//
//    FILE: CountDown.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.3
// PURPOSE: CountDown library for Arduino
//     URL: https://github.com/RobTillaart/CountDown


#include "CountDown.h"


CountDown::CountDown(const enum Resolution res)
{
  _state = CountDown::STOPPED;
  _remaining = 0;
  _startTime = 0;
  //  _res = MILLIS;  //  set in setResolution
  //  _ticks = 0;     //  set in setResolution
  setResolution(res);
  stop();
}


void CountDown::setResolution(const enum Resolution res)
{
  _res = res;
  _ticks = 0;
}


char CountDown::getUnits()
{
  return _res;
}


bool CountDown::start(uint32_t ticks)
{
  _ticks = ticks;
  _state = CountDown::RUNNING;
  if (_res == MICROS)
  {
    _startTime = micros();
  }
  else
  {
    _startTime = millis();
  }
  return true;  //  can not overflow
}


bool CountDown::start(uint8_t days, uint16_t hours, uint32_t minutes, uint32_t seconds)
{
  float _days = seconds / 86400.0 + minutes / 1440.0 + hours / 24.0 + days;
  bool rv = (_days < 49.7102696);

  uint32_t ticks = 86400UL * days + 3600UL * hours + 60UL * minutes + seconds;
  //  prevent underlying millis() overflow
  //  4294967 = number of SECONDS in 2^32 milliseconds
  if (ticks > 4294967) ticks = 4294967;
  setResolution(SECONDS);
  start(ticks);

  return rv;
}


bool CountDown::start(uint8_t days, uint16_t hours, uint32_t minutes)
{
  float _days = minutes / 1440.0 + hours / 24.0 + days;
  bool rv = (_days < 49.7102696);

  uint32_t ticks = 1440UL * days + 60UL * hours + minutes;
  //  prevent underlying millis() overflow
  //  71582 = number of MINUTES in 2^32 milliseconds
  if (ticks > 71582) ticks = 71582;
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


void CountDown::restart()
{
  start(_ticks);
}


uint32_t CountDown::remaining()
{
  calcRemaining();
  if (_remaining == 0) _state = CountDown::STOPPED;
  return _remaining;
}


bool CountDown::isRunning()
{
  calcRemaining();
  return (_state == CountDown::RUNNING);
}


bool CountDown::isStopped()
{
  calcRemaining();
  return (_state == CountDown::STOPPED);
}


//////////////////////////////////////////////////
//
//  PRIVATE
//
void CountDown::calcRemaining()
{
  uint32_t t = 0;
  if (_state == CountDown::RUNNING)
  {
    switch(_res)
    {
      case MINUTES:
        t = (millis() - _startTime) / 60000UL;
        break;
      case SECONDS:
        t = (millis() - _startTime) / 1000UL;;
        break;
      case MICROS:
        t = micros() - _startTime;
        break;
      case MILLIS:
      default:
        t = millis() - _startTime;
        break;
    }
    _remaining = _ticks > t ? _ticks - t : 0;
    if (_remaining == 0)
    {
      _state = CountDown::STOPPED;
    }
    return;
  }
}


//  -- END OF FILE --

