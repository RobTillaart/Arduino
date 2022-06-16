//
//    FILE: UUID.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.3
//    DATE: 2022-06-14
// PURPOSE: Arduino Library for generating UUID's
//     URL: https://github.com/RobTillaart/UUID
//          https://en.wikipedia.org/wiki/Universally_unique_identifier
//
//  HISTORY
//  0.1.0   2022-06-14   initial version
//  0.1.1   2022-06-15   improve performance generate()
//                       minor edits in readme.md
//                       fix bug in generator
//                       define UUID_MODE_VARIANT4
//                       define UUID_MODE_RANDOM
//  0.1.2   2022-06-15   fix version number
//                       improve performance generate()
//  0.1.3   2022-06-16   improve performance generate() again


#include "UUID.h"


UUID::UUID()
{
  seed(1, 2);
  setVariant4Mode();
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


//  check version 0.1.1 for more readable code
void UUID::generate()
{
  uint32_t _ar[4];
  for (uint8_t i = 0; i < 4; i++)
  {
    _ar[i] = _random();
  }
  
  //  patch bits for version 1 and variant 4 here
  if (_mode == UUID_MODE_VARIANT4)
  {
    _ar[1] &= 0xFFF0FFFF;   //  remove 4 bits.
    _ar[1] |= 0x00040000;   //  variant 4
    _ar[2] &= 0xFFFFFFF3;   //  remove 2 bits
    _ar[2] |= 0x00000008;   //  version 1
  }

  //  store globally ?

  //  process 16 bytes build up the char array.
  for (uint8_t i = 0, j = 0; i < 16; i++)
  {
    //  multiples of 4 between 8 and 20 get a -.
    //  but note we are doing 2 digits in one loop.
    if ((i & 0x1) == 0)
    {
      if ((4 <= i) && (i <= 10))  _buffer[j++] = '-';
    }

    //  process one byte at the time instead of a nibble
    uint8_t nr   = i / 4;
    uint8_t xx   = _ar[nr];
    uint8_t ch   = xx & 0xF;
    _buffer[j++]   = (ch < 10) ? '0' + ch : ('a' - 10) + ch;
    
    ch   = (xx >> 4) & 0xF;
    _ar[nr] >>= 8;
    _buffer[j++]   = (ch < 10) ? '0' + ch : ('a' - 10) + ch;
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

