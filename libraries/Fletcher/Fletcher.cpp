//
//    FILE: Fletcher.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.4
//    DATE: 2022-01-25
// PURPOSE: Arduino Library for calculating Fletcher's checksum
//     URL: https://github.com/RobTillaart/Fletcher
//          https://en.wikipedia.org/wiki/Fletcher%27s_checksum
//
//  HISTORY
//  0.1.0   2022-01-25   initial version, straightforward implementation
//  0.1.1   2022-01-26   optimize % math  variation based upon to Anastase Nakassis (wikipedia)
//  0.1.2   2022-01-26   add class implementation e.g. for streaming
//  0.1.3   2022-04-15   fix #4 split .h in .h and .cpp
//  0.1.4   2022-09-08   performance optimization (Kudos to Daniel Mohr).
//                       affects SAMD, ESP32 and ESP8266
//                       fix FLETCHER_LIB_VERSION


#include "Fletcher.h"


//
//  straightforward implementation.
//  max length buffer 65534.
//  Wikipedia shows optimizations.
//
uint16_t fletcher16(uint8_t *data, uint16_t length)
{
  uint32_t s1 = 0;
  uint32_t s2 = 0;
  for (uint16_t i = 0; i < length;)
  {
    // if S2 is halfway it is time to do modulo
    while ((i < length) && (s2 < 2147483648ULL))
    {
      s1 += data[i++];
      s2 += s1;
    }
    s1 %= FLETCHER_16;
    //  does not work due to the above "32-bit" loop.
    // s1 = (s1 & 255) + (s1 >> 8);   
    s2 %= FLETCHER_16;
    // s2 = (s2 & 255) + (s2 >> 8);
  }
  return (s2 << 8) | s1;
}


uint32_t fletcher32(uint16_t *data, uint16_t length)
{
  uint32_t s1 = 0;
  uint32_t s2 = 0;
  for (uint16_t i = 0; i < length;)
  {
    // if S2 is halfway it is time to do modulo
    while ((i < length) && (s2 < 2147483648ULL))
    {
      s1 += data[i++];
      s2 += s1;
    }
    // s1 %= FLETCHER_32;
    s1 = (s1 & 65535UL) + (s1 >> 16);
    
    // s2 %= FLETCHER_32;
    s2 = (s2 & 65535UL) + (s2 >> 16);
  }
  return (s2 << 16) | s1;
}


uint64_t fletcher64(uint32_t *data, uint16_t length)
{
  uint64_t s1 = 0;
  uint64_t s2 = 0;
  for (uint16_t i = 0; i < length;)
  {
    // if S2 is halfway it is time to do modulo
    while ((i < length) && (s2 < 9223372036854775808ULL))
    {
      s1 += data[i++];
      s2 += s1;
    }
    // s1 %= FLETCHER_64;
    s1 = (s1 & ((((uint64_t) 1) << 32) - 1)) + (s1 >> 32);
    // s2 %= FLETCHER_64;
    s2 = (s2 & ((((uint64_t) 1) << 32) - 1)) + (s2 >> 32);
  }
  return (s2 << 32) | s1;
}


// -- END OF FILE -- 


