#pragma once
//
//    FILE: MINMAX.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.2
//    DATE: 2021-10-14
// PURPOSE: MINMAX library - simple peak finder
//
//  HISTORY:
//  0.1.0  2021-10-14  initial version
//  0.1.1  2021-11-09  update readme, parameters
//                     add getAutoResetCount()
//                     rename setAutoResetCount()
//  0.1.2  2021-12-21  update library.json, license, minor edits
//                     defined constants


#include "Arduino.h"

#define MINMAX_LIB_VERSION                  (F("0.1.2"))

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
  }


  uint8_t add(const float value)
  {
    uint8_t rv = MINMAX_NO_CHANGE;
    if ((_resetCount != 0) && (_resetCount == _count))
    {
      reset();
      rv |= MINMAX_RESET_DONE;
    }
    if ((value < _minimum) || (_count == 0))
    {
      _minimum = value;
      rv |= MINMAX_MIN_CHANGED;
    }
    if ((value > _maximum) || (_count == 0))
    {
      _maximum = value;
      rv |= MINMAX_MAX_CHANGED;
    }
    _count++;
    return rv;
  }


  void reset()
  {
    _minimum = 0;
    _maximum = 0;
    _count   = 0;
  }


  void autoReset(uint32_t count)  // obsolete 0.2.0
  {
    _resetCount = count;
  };


  void setAutoResetCount(uint32_t count)
  {
    _resetCount = count;
  };


  uint32_t getAutoResetCount()
  {
    return _resetCount;
  };


  float    minimum() { return _minimum; };
  float    maximum() { return _maximum; };
  uint32_t count()   { return _count; };


private:
  float    _minimum;
  float    _maximum;
  uint32_t _count;
  uint32_t _resetCount;

};


// -- END OF FILE --

