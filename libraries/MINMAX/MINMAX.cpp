//
//    FILE: MINMAX.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.1
//    DATE: 2021-10-14
// PURPOSE: MINMAX library - simple peak finder
//     URL: https://github.com/RobTillaart/MINMAX



#include "MINMAX.h"

MINMAX::MINMAX()
{
  reset();
  _resetCount = 0;
  _callback = NULL;
}


uint8_t MINMAX::add(const float value)
{
  uint8_t rv = MINMAX_NO_CHANGE;
  _lastValue = value;
  if ((_resetCount != 0) && (_resetCount == _count))
  {
    reset();
    rv |= MINMAX_RESET_DONE;
  }
  if ((value < _minimum) || (_count == 0))
  {
    _minimum = value;
    _lastMin = millis();
    rv |= MINMAX_MIN_CHANGED;
  }
  if ((value > _maximum) || (_count == 0))
  {
    _maximum = value;
    _lastMax = millis();
    rv |= MINMAX_MAX_CHANGED;
  }
  _count++;
  if ((rv != MINMAX_NO_CHANGE) && (_callback != NULL)) _callback();
  return rv;
}


void MINMAX::reset()
{
  _lastValue = 0;
  _minimum   = 0;
  _maximum   = 0;
  _count     = 0;
  _lastMin   = 0;
  _lastMax   = 0;
}


void MINMAX::addCallBack( void (* func)(void) )
{
  _callback = func;
}


void MINMAX::setAutoResetCount(uint32_t count)
{
  _resetCount = count;
}


uint32_t MINMAX::getAutoResetCount()
{
  return _resetCount;
}


float    MINMAX::lastValue()
{
  return _lastValue;
}


float    MINMAX::minimum()
{
  return _minimum;
}


float    MINMAX::maximum()
{
  return _maximum;
}


uint32_t MINMAX::count()
{
  return _count;
}


uint32_t MINMAX::lastMin()
{
  return _lastMin;
}


uint32_t MINMAX::lastMax()
{
  return _lastMax;
}


// -- END OF FILE --

