//
//    FILE: Adler.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.0
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


uint16_t adler16(uint8_t * array, uint16_t length)
{
  uint16_t s1 = 1;
  uint16_t s2 = 0;
  for (uint16_t i = 0; i < length;)
  {
    // if S2 is halfway it is time to do modulo
    while ((i < length) && (s2 < 32768))
    {
      s1 += array[i++];
      s2 += s1;
    }
    s1 %= ADLER16_MOD_PRIME;
    s2 %= ADLER16_MOD_PRIME;
  }
  return (s2 << 8) | s1;
}


// -- END OF FILE -- 

