//
//    FILE: Adler.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.3
//    DATE: 2022-01-27
// PURPOSE: Arduino Library for calculating Adler checksum
//     URL: https://github.com/RobTillaart/Adler
//          https://en.wikipedia.org/wiki/Adler-32
//          (no Adler16 reference, implementation is experimental)


#include "Adler.h"


//////////////////////////////////////////////////////////////
//
//  STATIC FUNCTION
//
uint32_t adler32(uint8_t * array, uint16_t length, uint32_t s1, uint32_t s2)
{
  uint32_t _s1 = s1;
  uint32_t _s2 = s2;
  for (uint16_t i = 0; i < length;)
  {
    //  if _s2 is halfway it is time to do modulo
    while ((i < length) && (_s2 < 2147483648ULL))  //  MAGIC NR.
    {
      _s1 += array[i++];
      _s2 += _s1;
    }
    _s1 %= ADLER32_MOD_PRIME;
    _s2 %= ADLER32_MOD_PRIME;
  }
  return (_s2 << 16) | _s1;
}


uint16_t adler16(uint8_t * array, uint16_t length, uint16_t s1, uint16_t s2)
{
  uint16_t _s1 = s1;
  uint16_t _s2 = s2;
  for (uint16_t i = 0; i < length;)
  {
    //  if _s2 is halfway it is time to do modulo
    while ((i < length) && (_s2 < 32768))  //  MAGIC NR.
    {
      _s1 += array[i++];
      _s2 += _s1;
    }
    _s1 %= ADLER16_MOD_PRIME;
    _s2 %= ADLER16_MOD_PRIME;
  }
  return (_s2 << 8) | _s1;
}


//  -- END OF FILE --

