//
//    FILE: MINMAX.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.0
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
  _dampening      = 0;
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

  //  dampening - experimental
  if (_dampening > 0)
  {
    if (_minimum + _dampening < _maximum)
    {
      _minimum += _dampening;
    }
    if (_maximum - _dampening > _minimum)
    {
      _maximum -= _dampening;
    }
  }
  //  new run and range not adjusted by setResetDefaults()
  if ((_count == 0) && (_minimum == 0) && (_maximum == 0))
  {
    _minimum = _maximum = value;
    _lastMin = _lastMax = millis();
    rv |= MINMAX_MIN_CHANGED | MINMAX_MAX_CHANGED;
  }
  //  adjust minimum
  if (value < _minimum)
  {
    _minimum = value;
    _lastMin = millis();
    rv |= MINMAX_MIN_CHANGED;
  }
  //  adjust maximum
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

void MINMAX::setDampening(const float value)
{
  _dampening = value;
}


float MINMAX::getDampening()
{
  return _dampening;
}


//  -- END OF FILE --

