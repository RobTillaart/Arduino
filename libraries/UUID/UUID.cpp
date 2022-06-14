//
//    FILE: UUID.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2022-06-14
// PURPOSE: Arduino Library for generating UUID's
//     URL: https://github.com/RobTillaart/UUID
//          https://en.wikipedia.org/wiki/UUID
//
//  HISTORY
//  0.1.0   2022-06-14   initial version


#include "UUID.h"


UUID::UUID()
{
  seed(1, 2);
  generate();
}


void UUID::seed(uint32_t s1, uint32_t s2)
{
  // set Marsaglia constants, prevent 0 as value
  if (s1 == 0) s1 = 1;
  if (s2 == 0) s2 = 2;
  _m_w = s1;
  _m_z = s2;
}


void UUID::generate()
{
  uint32_t _ar[4];
  for (uint8_t i = 0; i < 4; i++)
  {
    _ar[i] = _random();
  }

  //  TODO improve efficiency
  for (int i = 0, j = 0; i < 32; i++, j++)
  {
    if (i == 8)  _buffer[j++] = '-';
    if (i == 12) _buffer[j++] = '-';
    if (i == 16) _buffer[j++] = '-';
    if (i == 20) _buffer[j++] = '-';

    uint8_t nr   = i / 8;
    uint8_t shft = ((i % 8) * 4);
    uint8_t ch   = (_ar[nr] >> shft ) & 0xF;

    _buffer[j]   = (ch < 10) ? '0' + ch : 'a' - 10 + ch;
  }
  _buffer[36] = 0;
}


char * UUID::toCharArray()
{
  return _buffer;
}


//  PRINTING
size_t UUID::printTo(Print& p) const
{
  return p.print(_buffer);
};


// An example of a simple pseudo-random number generator is the
// Multiply-with-carry method invented by George Marsaglia.
// two initializers (not null)
uint32_t UUID::_random()
{
  _m_z = 36969L * (_m_z & 65535L) + (_m_z >> 16);
  _m_w = 18000L * (_m_w & 65535L) + (_m_w >> 16);
  return (_m_z << 16) + _m_w;  /* 32-bit result */
}


// -- END OF FILE --

