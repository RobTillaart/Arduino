//
//    FILE: Adler16.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.0
//    DATE: 2022-06-14
// PURPOSE: Arduino Library for calculating Adler-16 checksum
//     URL: https://github.com/RobTillaart/Adler
//          https://en.wikipedia.org/wiki/Adler-32
//          (no Adler16 reference, implementation is experimental)
//
// HISTORY: see CHANGELOG.md



#include "Adler16.h"


Adler16::Adler16()
{
  begin(1, 0);
}


void Adler16::begin(uint16_t s1, uint16_t s2)
{
  _s1 = s1;
  _s2 = s2;
  _count = 0;
}


//  reference implementation
// void Adler16::add(uint8_t value)
// {
  // _count++;
  // _s1 += value;
   // if (_s1 >= ADLER16_MOD_PRIME) _s1 -= ADLER16_MOD_PRIME;
  // _s2 += _s1;
   // if (_s2 >= ADLER16_MOD_PRIME) _s2 -= ADLER16_MOD_PRIME;
// }


//  optimized version (~10% faster)
void Adler16::add(uint8_t value)
{
  _count++;
  _s1 += value;
  _s2 += _s1;
  if (_s2 >= ADLER16_MOD_PRIME)
  {
    _s2 -= ADLER16_MOD_PRIME;
    if (_s1 >= ADLER16_MOD_PRIME) _s1 -= ADLER16_MOD_PRIME;
  }
}


//  straightforward going through the array.
//  small footprint
void Adler16::add(uint8_t * array, uint16_t length)
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
//  only do modulo when S2 reaches halfway uint16_t
//                      and at the end of the loop.
void Adler16::addFast(uint8_t * array, uint16_t length)
{
  _count += length;
  uint16_t s1 = _s1;
  uint16_t s2 = _s2;
  for (uint16_t i = 0; i < length;)
  {
    // if S2 is halfway it is time to do modulo
    while ((i < length) && (s2 < 32768))
    {
      s1 += array[i++];
      s2 += s1;
    }
    if (s2 >= ADLER16_MOD_PRIME)
    {
      s2 %= ADLER16_MOD_PRIME;
      if (s1 >= ADLER16_MOD_PRIME) s1 %= ADLER16_MOD_PRIME;
    }
  }
  _s1 = s1;
  _s2 = s2;
}


uint16_t Adler16::getAdler()
{
  return (_s2 << 8) | _s1;
};


//////////////////////////////////////////////////////////////
//
//  wrappers for strings.
//
void Adler16::add(char value)
{
  add((uint8_t) value);
}


void Adler16::add(char * array, uint16_t length)
{
  add((uint8_t *) array, length);
}


void Adler16::addFast(char * array, uint16_t length)
{
  addFast((uint8_t *) array, length);
}


// -- END OF FILE --

