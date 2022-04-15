#pragma once
//
//    FILE: Adler.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
//    DATE: 2022-01-27
// PURPOSE: Arduino Library for calculating Adler-32 checksum
//     URL: https://github.com/RobTillaart/Adler
//          https://en.wikipedia.org/wiki/Adler-32
//
//  HISTORY
//  0.1.0   2022-01-27   initial version
//  0.1.1   2022-04-15   split of .cpp file


#include "Adler.h"


/////////////////////////////////////////////////
//
//  STATIC FUNCTION
//
uint32_t adler32(uint8_t *data, uint16_t length)
{
  uint32_t s1 = 1;
  uint32_t s2 = 0;
  for (uint16_t i = 0; i < length;)
  {
    // if S2 is halfway it is time to do modulo
    while ((i < length) && (s2 < 2147483648ULL))
    {
      s1 += data[i++];
      s2 += s1;
    }
    s1 %= ADLER_MOD_PRIME;
    s2 %= ADLER_MOD_PRIME;
  }
  return (s2 << 16) | s1;
}


// -- END OF FILE -- 

