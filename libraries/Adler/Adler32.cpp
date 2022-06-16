//
//    FILE: Adler32.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.0
//    DATE: 2022-01-27
// PURPOSE: Arduino Library for calculating Adler-32 checksum
//     URL: https://github.com/RobTillaart/Adler
//          https://en.wikipedia.org/wiki/Adler-32
//
// HISTORY: see CHANGELOG.md



#include "Adler32.h"


Adler32::Adler32()
{
  begin(1, 0);
}


void Adler32::begin(uint32_t s1, uint32_t s2)
{
  _s1 = s1;
  _s2 = s2;
  _count = 0;
}


//  reference implementation
// void Adler32::add(uint8_t value)
// {
  // _count++;
  // _s1 += value;
   // if (_s1 >= ADLER32_MOD_PRIME) _s1 -= ADLER32_MOD_PRIME;
  // _s2 += _s1;
   // if (_s2 >= ADLER32_MOD_PRIME) _s2 -= ADLER32_MOD_PRIME;
// }


//  optimized version (~10% faster)
void Adler32::add(uint8_t value)
{
  _count++;
  _s1 += value;
  _s2 += _s1;
  if (_s2 >= ADLER32_MOD_PRIME)
  {
    _s2 -= ADLER32_MOD_PRIME;
    if (_s1 >= ADLER32_MOD_PRIME) _s1 -= ADLER32_MOD_PRIME;
  }
}


//  straightforward going through the array.
//  small footprint.
void Adler32::add(uint8_t * array, uint16_t length)
{
  while (length--)
  {
    add(*array++);
  }
  return;
}


//  Optimized version
//  S1 grows linear
//  S2 grows quadratic
//  only do modulo when S2 reaches halfway uint32_t
//                      and at the end of the loop.
void Adler32::addFast(uint8_t * array, uint16_t length)
{
  _count += length;
  uint32_t s1 = _s1;
  uint32_t s2 = _s2;
  for (uint16_t i = 0; i < length;)
  {
    // if S2 is halfway it is time to do modulo
    while ((i < length) && (s2 < 2147483648ULL))
    {
      s1 += array[i++];
      s2 += s1;
    }
    if (s2 >= ADLER32_MOD_PRIME)
    {
      s2 %= ADLER32_MOD_PRIME;
      if (s1 >= ADLER32_MOD_PRIME) s1 %= ADLER32_MOD_PRIME;
    }
  }
  _s1 = s1;
  _s2 = s2;
}


uint32_t Adler32::getAdler()
{
  return (_s2 << 16) | _s1;
};



//////////////////////////////////////////////////////////////
//
//  wrappers for strings.
//
void Adler32::add(char value)
{
  add((uint8_t) value);
}


void Adler32::add(char * array, uint16_t length)
{
  add((uint8_t *) array, length);
}


void Adler32::addFast(char * array, uint16_t length)
{
  addFast((uint8_t *) array, length);
}


// -- END OF FILE --

