#pragma once
//
//    FILE: MINMAX.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.3
//    DATE: 2021-10-14
// PURPOSE: MINMAX library - simple peak finder



#include "Arduino.h"

#define MINMAX_LIB_VERSION                  (F("0.1.3"))

#define MINMAX_NO_CHANGE                    0X00
#define MINMAX_MIN_CHANGED                  0X01
#define MINMAX_MAX_CHANGED                  0X02
#define MINMAX_RESET_DONE                   0X80


class MINMAX
{
public:

  MINMAX()
  {
    reset();
    _resetCount = 0;
    _callback = NULL;
  }


  uint8_t add(const float value)
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


  void reset()
  {
    _lastValue = 0;
    _minimum = 0;
    _maximum = 0;
    _count   = 0;
    _lastMin = 0;
    _lastMax = 0;
  }


  void addCallBack( void (* func)(void) )
  {
    _callback = func;
  };


  void autoReset(uint32_t count)  //  obsolete 0.2.0
  {
    setAutoResetCount(count);
  };


  void setAutoResetCount(uint32_t count)
  {
    _resetCount = count;
  };


  uint32_t getAutoResetCount()
  {
    return _resetCount;
  };


  float    lastValue() { return _lastValue; };
  float    minimum() { return _minimum; };
  float    maximum() { return _maximum; };
  uint32_t count()   { return _count; };
  uint32_t lastMin() { return _lastMin; };
  uint32_t lastMax() { return _lastMax; };


private:
  float    _lastValue;
  float    _minimum;
  float    _maximum;
  uint32_t _count;
  uint32_t _resetCount;
  void     (* _callback)(void);

  uint32_t _lastMin;
  uint32_t _lastMax;

};


// -- END OF FILE --

