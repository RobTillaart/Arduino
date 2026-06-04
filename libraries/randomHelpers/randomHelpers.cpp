//
//    FILE: randomHelpers.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.9
// PURPOSE: Arduino library with helper function for faster random bits
//     URL: https://github.com/RobTillaart/randomHelpers



#include "randomHelpers.h"


//  the idea is to have one buffer ( __randomBuffer) which holds 32 random bits.
//  Every call fetches bits from that buffer and if it does not hold enough
//  bits any more it fills the buffer first. This way the relative expensive
//  calls to random() which produces a 32 bit number are minimized in an
//  efficient way.
//
//  TBD: put it in a class ?


uint32_t  __randomBuffer   = 0;
uint8_t   __randomBitsLeft = 0;


///////////////////////////////////////////////////////////////////////////
//
//  An example of a simple pseudo-random number generator is the
//  Multiply-with-carry method invented by George Marsaglia.
//  it has two initializers (not zero) which can be changed
//  to seed the generator.
//
uint32_t m_w = 1;
uint32_t m_z = 2;


uint32_t Marsaglia()
{
  m_z = 36969L * (m_z & 65535L) + (m_z >> 16);
  m_w = 18000L * (m_w & 65535L) + (m_w >> 16);
  return (m_z << 16) + m_w;  /* 32-bit result */
}

bool seedMarsaglia(uint32_t a, uint32_t b)
{
  if (a == 0 || b == 0)
  {
    //  fill a and b with built-in generator?
    return false;
  }
  m_w = a;
  m_z = b;
  return true;
}


//////////////////////////////////////////////////////////
//
//  getRandom N bits
//
bool getRandom1()
{
  if (__randomBitsLeft < 1)
  {
    __randomBuffer = getRandom32();
    __randomBitsLeft = 32;
  }
  bool rv = __randomBuffer & 0x01;
  __randomBuffer >>= 1;
  __randomBitsLeft--;
  return rv;
}

uint8_t getRandom2()
{
  if (__randomBitsLeft < 2)
  {
    __randomBuffer = getRandom32();
    __randomBitsLeft = 32;
  }
  uint8_t rv = __randomBuffer & 0x03;
  __randomBuffer >>= 2;
  __randomBitsLeft -= 2;
  return rv;
}

uint8_t getRandom3()
{
  if (__randomBitsLeft < 3)
  {
    __randomBuffer = getRandom32();
    __randomBitsLeft = 32;
  }
  uint8_t rv = __randomBuffer & 0x07;
  __randomBuffer >>= 3;
  __randomBitsLeft -= 3;
  return rv;
}

uint8_t getRandom4()
{
  if (__randomBitsLeft < 4)
  {
    __randomBuffer = getRandom32();
    __randomBitsLeft = 32;
  }
  uint8_t rv = __randomBuffer & 0x0F;
  __randomBuffer >>= 4;
  __randomBitsLeft -= 4;
  return rv;
}

uint8_t getRandom5()
{
  if (__randomBitsLeft < 5)
  {
    __randomBuffer = getRandom32();
    __randomBitsLeft = 32;
  }
  uint8_t rv = __randomBuffer & 0x1F;
  __randomBuffer >>= 5;
  __randomBitsLeft -= 5;
  return rv;
}

uint8_t getRandom6()
{
  if (__randomBitsLeft < 6)
  {
    __randomBuffer = getRandom32();
    __randomBitsLeft = 32;
  }
  uint8_t rv = __randomBuffer & 0x3F;
  __randomBuffer >>= 6;
  __randomBitsLeft -= 6;
  return rv;
}

uint8_t getRandom7()
{
  if (__randomBitsLeft < 7)
  {
    __randomBuffer = getRandom32();
    __randomBitsLeft = 32;
  }
  uint8_t rv = __randomBuffer & 0x7F;
  __randomBuffer >>= 7;
  __randomBitsLeft -= 7;
  return rv;
}

uint8_t getRandom8()
{
  if (__randomBitsLeft < 8)
  {
    __randomBuffer = getRandom32();
    __randomBitsLeft = 32;
  }
  uint8_t rv = __randomBuffer & 0xFF;
  __randomBuffer >>= 8;
  __randomBitsLeft -= 8;
  return rv;
}

uint16_t getRandom9()
{
  if (__randomBitsLeft < 9)
  {
    __randomBuffer = getRandom32();
    __randomBitsLeft = 32;
  }
  uint16_t rv = __randomBuffer & 0x01FF;
  __randomBuffer >>= 9;
  __randomBitsLeft -= 9;
  return rv;
}

uint16_t getRandom10()
{
  if (__randomBitsLeft < 10)
  {
    __randomBuffer = getRandom32();
    __randomBitsLeft = 32;
  }
  uint16_t rv = __randomBuffer & 0x03FF;
  __randomBuffer >>= 10;
  __randomBitsLeft -= 10;
  return rv;
}

uint16_t getRandom16()
{
  if (__randomBitsLeft < 16)
  {
    __randomBuffer = getRandom32();
    __randomBitsLeft = 32;
  }
  uint16_t rv = __randomBuffer & 0xFFFF;
  __randomBuffer >>= 16;
  __randomBitsLeft -= 16;
  return rv;
}

uint32_t getRandom24()
{
  return getRandom32() & 0xFFFFFF;
}

uint32_t getRandom32()
{
  //  return random(0xFFFFFFFF);  //  use the built in
  return Marsaglia();
}

uint64_t getRandom64()
{
  uint64_t rv = getRandom32();
  rv <<= 32;
  rv |= getRandom32();
  return rv;
}


/////////////////////////////////////////////////
//
//  TYPICAL USES
//
bool inline flipCoin()
{
  return getRandom1();
}

//  div3() derived from divmod3() from fast_math.h
//
uint32_t div3(uint32_t in)
{
    uint32_t q = (in >> 1) + (in >> 3);
    q = q + (q >> 4);
    q = q + (q >> 8);
    q = q + (q >> 16);
    q = q >> 1;
    uint32_t r = in - q * 3;
    q = q + (r * 86 >> 8);
    return q;
}

uint8_t throwDice()
{
  if (__randomBitsLeft < 16)
  {
    __randomBuffer = getRandom32();
    __randomBitsLeft = 32;
  }
  uint32_t tmp = div3(__randomBuffer) >> 1;    //  divide by 6
  uint8_t rv = __randomBuffer - tmp * 6 + 1;   //  remainder + 1
  __randomBuffer >>= 3;
  __randomBitsLeft -= 3;
  return rv;
  //  previous.
  // uint8_t rv = __randomBuffer % 6 + 1;     //  remainder + 1
  // __randomBuffer >>= 3;
  // __randomBitsLeft -= 3;
  // return rv;
}

/*
//  works well for 1..16; but above it is worse
uint32_t getRandomBits(uint8_t n)
{
  if (__randomBitsLeft < n)
  {
    __randomBuffer = getRandom32();
    __randomBitsLeft = 32;
  }
  uint32_t rv = __randomBuffer & ((1UL << n) - 1);
  __randomBuffer >>= n;
  __randomBitsLeft -= n;
  return rv;
}
*/

//  n = 1..31
//  TODO: performance gain too low for n > 16
uint32_t getRandomBits(uint8_t n)
{
  uint32_t rv = 0;

  //  for large values of n the more straightforward approach is faster (UNO).
  if (n > 32) n = 32;
  if (n >= 20) return getRandom32() >> (32 - n);

  if (n >= __randomBitsLeft)
  {
    if (__randomBitsLeft > 0)
    {
      n -= __randomBitsLeft;
      rv = __randomBuffer << n;
    }
    __randomBuffer = getRandom32();
    __randomBitsLeft = 32;
  }
  if (n > 0)  //  more bits needed?
  {
    rv |= __randomBuffer & ((1UL << n) - 1);
    __randomBuffer >>= n;
    __randomBitsLeft -= n;
  }
  return rv;
}


//  -- END OF FILE --

