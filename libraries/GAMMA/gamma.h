#pragma once
//
//    FILE: gamma.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
//    DATE: 2020-08-08
// PURPOSE: Arduino Library to efficiently hold a gamma lookup table

//  0.1.0   2020-08-08  initial release
//  0.1.1   2020-12-24  arduino-ci + unit test 


#include "Arduino.h"

#define GAMMA_LIB_VERSION         (F("0.1.1"))


#if defined(ESP8266) || defined(ESP32)
#include "types.h"
#endif

class GAMMA
{

public:

  GAMMA(uint16_t size = 32)
  {
    _shift = 7;
    // force power of 2; get shift & mask right
    for (uint16_t s = 2; s < 512; s <<= 1)
    {
      if (size <= s)
      {
        _size = s;
        break;
      }
      _shift--;
    }
    _mask = (1 << _shift) - 1;
    _interval = 256 / _size;
    _table = (uint8_t *)malloc(_size + 1);
    setGamma(2.8);
  }

  ~GAMMA()
  {
    if (_table) free(_table);
  }

  void setGamma(float gamma)
  {
    if (_gamma != gamma)
    {
      yield();  // keep ESP happy
      _gamma = gamma;
      for (uint16_t i = 0; i < _size; i++)
      {
        _table[i] = pow(i * _interval * (1.0 / 255), _gamma) * 255 + 0.5;
      }
      _table[_size] = 255;  // anchor for interpolation..
    }
  }

  float getGamma()
  {
    return _gamma;
  };

  uint8_t operator[] (uint8_t idx)
  {
    if (_interval == 1) return _table[idx];
    // else interpolate
    uint8_t  i = idx >> _shift;
    uint8_t  m = idx & _mask;
    // exact element shortcut
    if ( m == 0 ) return _table[i];
    // interpolation
    uint16_t delta = _table[i+1] - _table[i];
    delta = (delta * m + _interval/2) >> _shift;  //  == /_interval;
    return _table[i] + delta;
  }

  uint16_t size()
  {
    return _size + 1;
  };

  int distinct()
  {
    int last = _table[0];
    int cnt = 1;
    for (uint16_t i = 1; i < _size; i++)
    {
      if (_table[i] == last) continue;
      last = _table[i];
      cnt++;
    }
    return cnt;
  }

  void dump()
  {
    for (uint16_t i = 0; i < _size; i++)
    {
      Serial.println(_table[i]);
    }
  }


private:
  uint8_t   _shift    = 0;
  uint8_t   _mask     = 0;
  uint16_t  _size     = 0;
  uint8_t   _interval = 0;
  float     _gamma    = 0;
  uint8_t * _table;

};

// -- END OF FILE --
