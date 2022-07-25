//
//    FILE: gamma.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.2
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


void GAMMA::begin()
{
  if (_table == NULL)
  {
    _table = (uint8_t *)malloc(_size + 1);
  }
  setGamma(2.8);
};


void GAMMA::setGamma(float gamma)
{
  if (_gamma != gamma)
  {
    yield();  // keep ESP happy
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
    for (uint16_t i = 0; i < _size; i++)
    {
      _table[i] = pow(i * _interval * (1.0/ 255.0), _gamma) * 255 + 0.5;
    }
    _table[_size] = 255;  // anchor for interpolation..
  }
};


float GAMMA::getGamma()
{
  return _gamma;
};


uint8_t GAMMA::operator[] (uint8_t index)
{
  if (_interval == 1) return _table[index];
  // else interpolate
  uint8_t  i = index >> _shift;
  uint8_t  m = index & _mask;
  // exact element shortcut
  if ( m == 0 ) return _table[i];
  // interpolation
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


void GAMMA::dump(Stream *str)
{
  for (uint16_t i = 0; i <= _size; i++)
  {
    str->println(_table[i]);
  }
};


void GAMMA::dumpArray(Stream *str)
{
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
};


// -- END OF FILE --

