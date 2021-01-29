#pragma once
//
//    FILE: randomHelpers.h
//  AUTHOR: Rob dot Tillaart at gmail dot com
// VERSION: 0.2.1
// PURPOSE: Arduino library with helper function for faster random bits
//     URL: https://github.com/RobTillaart/randomHelpers
//
//  HISTORY:
//  0.2.1   2021-01-07  Arduino-CI
//  0.2.0   2020-07-01  rewrite.
//  0.1.01  2015-08-18  bug fixes and further optimizations.
//  0.1.00  2015-08-17  initial version.



#include "Arduino.h"

#define RANDOM_HELPERS_VERSION       (F("0.2.1"))

// the idea is to have one buffer ( __randomBuffer) which holds 32 random bits. 
// Every call fetches bits from that buffer and if it does not hold enough 
// bits anymore it fills the buffer first. This way the relative expensive 
// calls to random() which produces a 32 bit number are minimized in an
// effcient way.
//
// TBD: put it in a class ?

uint32_t  __randomBuffer = 0;
uint8_t   __randomIdx = 0;


///////////////////////////////////////////////////////////////////////////
//
// An example of a simple pseudo-random number generator is the 
// Multiply-with-carry method invented by George Marsaglia.
// it has two initializers (not zero) which can be changed 
// to seed the generator.
//
uint32_t m_w = 1;
uint32_t m_z = 2; 

uint32_t Marsaglia()
{
    m_z = 36969L * (m_z & 65535L) + (m_z >> 16);
    m_w = 18000L * (m_w & 65535L) + (m_w >> 16);
    return (m_z << 16) + m_w;  /* 32-bit result */
} 


uint32_t getRandom32()
{
  // return random(0xFFFFFFFF);  // use the built in
  return Marsaglia();
}


bool getRandom1()
{
  if (__randomIdx < 1)
  {
    __randomBuffer = getRandom32();
    __randomIdx = 32;
  }
  bool rv = __randomBuffer & 0x01;
  __randomBuffer >>= 1;
  __randomIdx--;
  return rv;
}

// typical use 
bool inline flipCoin()
{ 
  return getRandom1();
};


uint8_t getRandom4()
{
  if (__randomIdx < 4)
  {
    __randomBuffer = getRandom32();
    __randomIdx = 32;
  }
  uint8_t rv = __randomBuffer & 0x0F;
  __randomBuffer >>= 4;
  __randomIdx -= 4;
  return rv;
}


uint8_t getRandom5()
{
  if (__randomIdx < 5)
  {
    __randomBuffer = getRandom32();
    __randomIdx = 32;
  }
  uint8_t rv = __randomBuffer & 0x1F;
  __randomBuffer >>= 5;
  __randomIdx -= 5;
  return rv;
}


uint8_t getRandom6()
{
  if (__randomIdx < 6)
  {
    __randomBuffer = getRandom32();
    __randomIdx = 32;
  }
  uint8_t rv = __randomBuffer & 0x3F;
  __randomBuffer >>= 6;
  __randomIdx -= 6;
  return rv;
}


// typical use
uint8_t inline throwDice() 
{
  uint8_t rv = 0;
  uint8_t x = getRandom5();
  for (uint8_t i = 0; i < 6 ; i++)
  {
    if (x & 1) rv++;
    x >>= 1;
  }
  return rv;
}


uint8_t getRandom8()
{
  if (__randomIdx < 8)
  {
    __randomBuffer = getRandom32();
    __randomIdx = 32;
  }
  uint8_t rv = __randomBuffer & 0xFF;
  __randomBuffer >>= 8;
  __randomIdx -= 8;
  return rv;
}


uint16_t getRandom16()
{
  if (__randomIdx < 16)
  {
    __randomBuffer = getRandom32();
    __randomIdx = 32;
  }
  uint16_t rv = __randomBuffer & 0xFFFF;
  __randomBuffer >>= 16;
  __randomIdx -= 16;
  return rv;
}


uint32_t getRandom24()
{
  return getRandom32() & 0xFFFFFF;
}

uint64_t getRandom64()
{
  uint64_t rv = getRandom32();
  rv <<= 32;
  rv |= getRandom32();
  return rv;
}

/*
// works well for 1..16; but above it is worse
uint32_t getRandomBits(uint8_t n)
{
  if (__randomIdx < n)
  {
    __randomBuffer = getRandom32();
    __randomIdx = 32;
  }
  uint32_t rv = __randomBuffer & ((1UL << n) - 1);
  __randomBuffer >>= n;
  __randomIdx -= n;
  return rv;
}
*/


// n = 1..31
// TODO: performance gain too low for n > 16
uint32_t getRandomBits(uint8_t n) 
{
  uint32_t rv = 0;

  // for large values of n the more straightforward approach is faster (UNO).
  if (n > 32) n = 32;
  if (n >= 20) return getRandom32() >> (32 - n);

  if (n >= __randomIdx)
  {
    if (__randomIdx > 0)
    {
      n -= __randomIdx;
      rv = __randomBuffer << n;
    }
    __randomBuffer = getRandom32();
    __randomIdx = 32;
  }
  if (n > 0)  // more bits needed?
  {
    rv |= __randomBuffer & ((1UL << n) - 1);
    __randomBuffer >>= n;
    __randomIdx -= n;
  }
  return rv;
}

// -- END OF FILE --
