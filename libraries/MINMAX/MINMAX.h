#pragma once
//
//    FILE: MINMAX.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2021-10-14
// PURPOSE: MINMAX library - simple peak finder
//
//  HISTORY:
//  0.1.0  2021-10-14  initial version


#include "Arduino.h"

#define MINMAX_LIB_VERSION        (F("0.1.0"))


class MINMAX
{
  public:

    MINMAX()
    {
      reset();
      _resetCount = 0;
    }


    uint8_t add(float f)
    {
      uint8_t rv = 0;
      if ((_resetCount != 0) && (_resetCount == _count))
      {
        reset();
        rv |= 0x80;
      }
      if ((f < _minimum) || (_count == 0))
      {
        _minimum = f;
        rv |= 0x01;
      }
      if ((f > _maximum) || (_count == 0))
      {
        _maximum = f;
        rv |= 0x02;
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


    void autoReset(uint32_t cnt) { _resetCount = cnt; };


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
