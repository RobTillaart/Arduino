//
//    FILE: Adler.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.2
//    DATE: 2022-01-27
// PURPOSE: Arduino Library for calculating Adler-32 checksum
//     URL: https://github.com/RobTillaart/Adler
//          https://en.wikipedia.org/wiki/Adler-32
//
//  HISTORY
//  0.1.0   2022-01-27   initial version
//  0.1.1   2022-04-15   split of .cpp file
//  0.1.2   2022-06-13   split interface and implementation
//                       rename ADLER32_MOD_PRIME
//                       rename ADLER32_LIB_VERSION
//                       add addFast(array, length)
//                       add char interfaces


#include "Adler.h"


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
void Adler32::add(uint8_t value)
{
  _count++;
  _s1 += value;
   if (_s1 >= ADLER32_MOD_PRIME) _s1 -= ADLER32_MOD_PRIME;
  _s2 += _s1;
   if (_s2 >= ADLER32_MOD_PRIME) _s2 -= ADLER32_MOD_PRIME;
}


//  optimized version (~10% gain)
//  void Adler32::add(uint8_t value)
//  {
//    _count++;
//    _s1 += value;
//    _s2 += _s1;
//     if (_s2 >= ADLER32_MOD_PRIME)
//     {
//       _s2 -= ADLER32_MOD_PRIME;
//       if (_s1 >= ADLER32_MOD_PRIME) _s1 -= ADLER32_MOD_PRIME;
//     }
//  }


//  straightforward going through the array.
void Adler32::add(uint8_t * array, uint16_t length)
{
  while (length--)
  {
    add(*array++);
  }
  return;
}


//  optimized version (under test)
//  S1 grows linear
//  S2 grows quadratic
//  as S2 grows faster than S1, S1 needs only to be checked 
//     if S2 hits the ADLER32_MOD_PRIME and probably far less.
//
//  void Adler32::addFast(uint8_t * array, uint16_t length)
//  {
//    _count += length;
//    while (length--)
//    {
//      _s1 += *array++;
//      _s2 += _s1;
//      if (_s2 >= ADLER32_MOD_PRIME)
//      {
//        _s2 -= ADLER32_MOD_PRIME;
//        if (_s1 >= ADLER32_MOD_PRIME)
//        {
//          _s1 -= ADLER32_MOD_PRIME;
//        }
//      }
//    }
//  }


//  further optimized version (under test)
//  S1 grows linear
//  S2 grows quadratic
//  only do modulo when we reach halfway uint32_t
//  or when really needed.
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


//////////////////////////////////////////////////////////////
//
//  wrapper for strings.
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


uint32_t Adler32::getAdler()
{
  return (_s2 << 16) | _s1;
};



//////////////////////////////////////////////////////////////
//
//  STATIC FUNCTION
//
uint32_t adler32(uint8_t * array, uint16_t length)
{
  uint32_t s1 = 1;
  uint32_t s2 = 0;
  for (uint16_t i = 0; i < length;)
  {
    // if S2 is halfway it is time to do modulo
    while ((i < length) && (s2 < 2147483648ULL))
    {
      s1 += array[i++];
      s2 += s1;
    }
    s1 %= ADLER32_MOD_PRIME;
    s2 %= ADLER32_MOD_PRIME;
  }
  return (s2 << 16) | s1;
}


// -- END OF FILE -- 

