//
//    FILE: Fletcher.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.9
//    DATE: 2022-01-25
// PURPOSE: Arduino Library for calculating Fletcher's checksum
//     URL: https://github.com/RobTillaart/Fletcher
//          https://en.wikipedia.org/wiki/Fletcher%27s_checksum


#include "Fletcher.h"


//  straightforward implementation.
//  max length buffer 65534.
//  Wikipedia shows optimizations.
//
uint16_t fletcher16(uint8_t *data, uint16_t length, uint32_t s1, uint32_t s2)
{
  uint32_t _s1 = s1;
  uint32_t _s2 = s2;
  for (uint16_t i = 0; i < length;)
  {
    //  if _s2 is halfway it is time to do modulo
    while ((i < length) && (_s2 < 2147483648ULL))  //  MAGIC NR
    {
      _s1 += data[i++];
      _s2 += _s1;
    }
    //  this optimization does not work due to the above "32-bit" loop.
    //  for all three functions.
    //  _s1 = (_s1 & 255) + (_s1 >> 8);
    _s1 %= FLETCHER_16;
    _s2 %= FLETCHER_16;
  }
  return (_s2 << 8) | _s1;
}


uint32_t fletcher32(uint16_t *data, uint16_t length, uint32_t s1, uint32_t s2)
{
  uint32_t _s1 = s1;
  uint32_t _s2 = s2;
  for (uint16_t i = 0; i < length;)
  {
    //  if _s2 is halfway it is time to do modulo
    while ((i < length) && (_s2 < 2147483648ULL))  //  MAGIC NR
    {
      _s1 += data[i++];
      _s2 += _s1;
    }
    _s1 %= FLETCHER_32;
    _s2 %= FLETCHER_32;
  }
  return (_s2 << 16) | _s1;
}


uint64_t fletcher64(uint32_t *data, uint16_t length, uint64_t s1, uint64_t s2)
{
  uint64_t _s1 = s1;
  uint64_t _s2 = s2;
  for (uint16_t i = 0; i < length;)
  {
    //  if _s2 is halfway it is time to do modulo
    while ((i < length) && (_s2 < 9223372036854775808ULL))  //  MAGIC NR
    {
      _s1 += data[i++];
      _s2 += _s1;
    }
    _s1 %= FLETCHER_64;
    _s2 %= FLETCHER_64;
  }
  return (_s2 << 32) | _s1;
}


//  -- END OF FILE -- 


