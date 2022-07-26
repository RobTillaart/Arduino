//
//    FILE: gamma.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.0
//    DATE: 2020-08-08
// PURPOSE: Arduino Library to efficiently hold a gamma lookup table

//  0.1.0   2020-08-08  initial release
//  0.1.1   2020-12-24  Arduino-CI + unit test
//
//  0.2.0   2021-11-02  update build-CI, badges
//                      add begin() - fixes ESP32 crash.
//  0.2.1   2021-12-18  update library.json, license, 
//                      add constants, minor edits.
//  0.2.2   2022-07-25  split in .h and .cpp
//                      add Stream parameter to dump()
//                      add dumpArray(Stream)
//                      fix distinct()
//
//  0.3.0   2022-07-26  change return type begin() + setGamma()
//                      add test gamma <=0 in setGamma()
//                      add _table == NULL tests
//                      fixed type of index in [] operator.
//                      adjust rounding in setGamma() to minimize errors.
//                      update build-CI


#include "gamma.h"


GAMMA::GAMMA(uint16_t size)
{
  _shift = 7;
  // force power of 2; get shift & mask right
  for (uint16_t s = 2; s <= GAMMA_MAX_SIZE; s <<= 1)
  {
    if (size <= s)
    {
      _size = s;
      break;
    }
    _shift--;
  }
  _mask = (1 << _shift) - 1;
  _interval = GAMMA_MAX_SIZE / _size;
};


GAMMA::~GAMMA()
{
  if (_table) free(_table);
};


bool GAMMA::begin()
{
  if (_table == NULL)
  {
    _table = (uint8_t *)malloc(_size + 1);
  }
  if (_table == NULL) return false;
  setGamma(2.8);
  return true;
};


bool GAMMA::setGamma(float gamma)
{
  if (_table == NULL) return false;
  if (gamma <= 0) return false;
  if (_gamma != gamma)
  {
    yield();  // try to keep ESP happy
    _gamma = gamma;
    //  marginally faster
    // uint16_t iv = _interval;
    // _table[0] = 0;
    // for (uint16_t i = 1; i < _size; i++)
    // {
      // float x = log(i * iv) + log(1.0 / 255);
      // _table[i] = exp(x * _gamma) * 255 + 0.5;
    // }
    //  REFERENCE
    //  rounding factor 0.444 optimized with error example.
    for (uint16_t i = 1; i < _size; i++)
    {
      _table[i] = pow(i * _interval * (1.0/ 255.0), _gamma) * 255 + 0.444;
    }
    _table[0] = 0;
    _table[_size] = 255;  // anchor for interpolation.
  }
  return true;
};


float GAMMA::getGamma()
{
  return _gamma;
};


uint8_t GAMMA::operator[] (uint8_t index)
{
  //  0.3.0 _table test slows performance ~0.4 us.
  if (_table == NULL) return 0;
  if (_interval == 1) return _table[index];
  // else interpolate
  uint8_t  i = index >> _shift;
  uint8_t  m = index & _mask;
  // exact element shortcut
  if ( m == 0 ) return _table[i];
  //  interpolation
  //  delta must be uint16_t to prevent overflow. (small tables)
  //        delta * m can be > 8 bit.
  uint16_t delta = _table[i+1] - _table[i];
  delta = (delta * m + _interval/2) >> _shift;  //  == /_interval;
  return _table[i] + delta;
};


uint16_t GAMMA::size()
{
  return _size + 1;
};


uint16_t GAMMA::distinct()
{
  uint8_t  last  = _table[0];
  uint16_t count = 1;
  for (uint16_t i = 1; i <= _size; i++)
  {
    if (_table[i] == last) continue;
    last = _table[i];
    count++;
  }
  return count;
};


bool GAMMA::dump(Stream *str)
{
  if (_table == NULL) return false;
  for (uint16_t i = 0; i <= _size; i++)
  {
    str->println(_table[i]);
  }
  return true;
};


bool GAMMA::dumpArray(Stream *str)
{
  if (_table == NULL) return false;
  str->println();
  str->print("uint8_t gamma[");
  str->print(_size + 1);
  str->print("] = {");
  
  for (uint16_t i = 0; i <= _size; i++)
  {
    if (i % 8 == 0) str->print("\n  ");
    str->print(_table[i]);
    if (i < _size) str->print(", ");
  }
  str->print("\n  };\n\n");
  return true;
};


//  performance investigation
//  https://stackoverflow.com/questions/43429238/using-boost-cpp-int-for-functions-like-pow-and-rand
inline float GAMMA::fastPow(float a, float b)
{
  //  reference
  return pow(a, b);
}


// -- END OF FILE --

