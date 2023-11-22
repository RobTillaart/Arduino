//
//    FILE: StopWatch.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.5
//    DATE: 2011-01-04
// PURPOSE: Arduino Library implementing a stopwatch including seconds, milliseconds microseconds
//     URL: https://github.com/RobTillaart/StopWatch_RT
//
//  The library is based upon millis() and therefore
//  has the same restrictions as millis() has with respect to overflow.


#include "StopWatch.h"


StopWatch::StopWatch(const enum Resolution resolution)
{
  reset();
  setResolution(resolution);
}


void StopWatch::start()
{
  if ((_state == StopWatch::RESET) || (_state == StopWatch::STOPPED))
  {
    _state = StopWatch::RUNNING;
    uint32_t t = _gettime();
    _startTime += t - _stopTime;
    _stopTime = t;
  }
}


void StopWatch::stop()
{
  if (_state == StopWatch::RUNNING)
  {
    _stopTime = _gettime();
    _state = StopWatch::STOPPED;
  }
}


void StopWatch::reset()
{
  _state      = StopWatch::RESET;
  _startTime  = _stopTime = 0;
}


//  made const as printTo expect a const object.
uint32_t StopWatch::elapsed() const
{
  if (_state == StopWatch::RUNNING)
  {
    return _gettime() - _startTime;
  }
  return _stopTime - _startTime;
}


char StopWatch::getUnits()
{
  return _resolution;
}


bool StopWatch::isRunning()
{
  return _state == StopWatch::RUNNING;
}


bool StopWatch::isStopped()
{
  return _state == StopWatch::STOPPED;
}


bool StopWatch::isReset()
{
  return _state == StopWatch::RESET;
}


void StopWatch::setResolution(const enum Resolution resolution)
{
  reset();
  _resolution = resolution;
  switch(_resolution)
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
    _resolution = MILLIS;      //  for default!
    break;
  }
}


////////////////////////////////////////////////
//
//  PRINTABLE
//
size_t StopWatch::printTo(Print& p) const
{
  uint32_t ti = StopWatch::elapsed();
  size_t n = p.print(ti);
  switch(_resolution)
  {
    case MICROS:   n += p.print(" us"); break;
    case MILLIS:   n += p.print(" ms"); break;
    case SECONDS:  n += p.print(" s");  break;
    case MINUTES:  n += p.print(" m."); break;
  }
  return n;
}


////////////////////////////////////////////////
//
//  PRIVATE
//


//  -- END OF FILE --

