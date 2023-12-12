//
//    FILE: MINMAX.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.2
//    DATE: 2021-10-14
// PURPOSE: MINMAX library - simple peak finder
//     URL: https://github.com/RobTillaart/MINMAX



#include "MINMAX.h"

MINMAX::MINMAX()
{
  _resetCount     = 0;
  _minimumDefault = 0;
  _maximumDefault = 0;
  _callback       = NULL;
  reset();
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
  //  new run and range not adjusted by setResetDefaults()
  if ((_count == 0) && (_minimum == 0) && (_maximum == 0))
  {
    _minimum = _maximum = value;
    _lastMin = _lastMax = millis();
    rv |= MINMAX_MIN_CHANGED | MINMAX_MAX_CHANGED;
  }
  if (value < _minimum)
  {
    _minimum = value;
    _lastMin = millis();
    rv |= MINMAX_MIN_CHANGED;
  }
  if (value > _maximum)
  {
    _maximum = value;
    _lastMax = millis();
    rv |= MINMAX_MAX_CHANGED;
  }
  _count++;
  if ((rv != MINMAX_NO_CHANGE) && (_callback != NULL))
  {
    _callback();
  }
  return rv;
}


void MINMAX::reset()
{
  _lastValue = 0;
  _minimum   = _minimumDefault;
  _maximum   = _maximumDefault;
  _count     = 0;
  _lastMin   = 0;
  _lastMax   = 0;
}


void MINMAX::setResetDefaults(float minimum, float maximum)
{
  _minimumDefault = minimum;
  _maximumDefault = maximum;
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

