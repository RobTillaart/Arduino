#pragma once
//
//    FILE: Adler.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
//    DATE: 2022-01-27
// PURPOSE: Arduino Library for calculating Adler-32 checksum
//     URL: https://github.com/RobTillaart/Adler
//          https://en.wikipedia.org/wiki/Adler-32


#include "Arduino.h"


#define ADLER_LIB_VERSION              (F("0.1.1"))

const uint16_t ADLER_MOD_PRIME = 65521;


/////////////////////////////////////////////////
//
//  STATIC FUNCTION
//
uint32_t adler32(uint8_t *data, uint16_t length);



/////////////////////////////////////////////////
//
//  CLASS VERSION
//
class Adler32
{
public:
  Adler32()
  {
    begin(1, 0);
  }

  void begin(uint32_t s1 = 1, uint32_t s2 = 0)
  {
    _s1 = s1;
    _s2 = s2;
    _count = 0;
  }

  void add(uint8_t value)
  {
    _count++;
    _s1 += value;
     if (_s1 >= ADLER_MOD_PRIME) _s1 -= ADLER_MOD_PRIME;
    _s2 += _s1;
     if (_s2 >= ADLER_MOD_PRIME) _s2 -= ADLER_MOD_PRIME;
  }

  void add(uint8_t * array, uint16_t length)
  {
    while (length--)
    {
      add(*array++);
    }
  }

  uint32_t getAdler() { return (_s2 << 16) | _s1; };
  uint32_t count()    { return _count; };

private:
  uint32_t _s1;
  uint32_t _s2;
  uint32_t _count;
};


// -- END OF FILE -- 


