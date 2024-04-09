//
//    FILE: bitHelpers.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.12
//    DATE: 2015-11-07
// PURPOSE: Arduino library with functions on bit level
//     URL: https://github.com/RobTillaart/bitHelpers


#include "bitHelpers.h"


////////////////////////////////////////////////
//
//  BIT COUNT TEST
//
uint8_t bitCountReference(uint32_t value)
{
  uint32_t v = value;
  uint8_t count = 0;
  while (v > 0)
  {
    if (v & 1) count++;
    v >>= 1;
  }
  return count;
}


uint8_t bitCountKR(uint32_t value)
{
  //  Kerningham & Ritchie
  uint32_t v = value;
  uint8_t count = 0;
  while (v)
  {
    count++;
    v &= (v - 1);
  }
  return count;
}


uint8_t bitCountArray(uint32_t value)
{
  uint8_t ar[] = {0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4};
  uint32_t v = value;
  uint8_t count = 0;
  while (v)
  {
    count += ar[v & 0x0F];
    v >>= 4;
  }
  return count;
}


uint8_t bitCountF1(uint32_t value)
{
  //  parallel adding in a register SWAG algorithm
  uint32_t v = value;
  v = v - ((v >> 1) & 0x55555555);
  v = (v & 0x33333333) + ((v >> 2) & 0x33333333);
  v = (v + (v >> 4)) & 0x0F0F0F0F;
  v = v + (v >> 8);
  v = v + (v >> 16);
  return v & 0x0000003F;
};


uint8_t bitCountF2(uint32_t value)
{
  //  parallel adding in a register SWAG algorithm
  uint32_t v = value;
  v = v - ((v >> 1) & 0x55555555);
  v = (v & 0x33333333) + ((v >> 2) & 0x33333333);
  v = ((v + (v >> 4)) & 0x0F0F0F0F);
  return ( v * 0x01010101) >> 24;
}


////////////////////////////////////////////////
//
//  BIT COUNT
//
uint8_t bitCount(uint8_t value)
{
  //  parallel adding in a register SWAG algorithm
  uint8_t v = value;
  v = v - ((v >> 1) & 0x55);
  v = (v & 0x33) + ((v >> 2) & 0x33);
  v = (v + (v >> 4)) & 0x0F;
  return v;
}


uint8_t bitCount(uint16_t value)
{
  //  parallel adding in a register SWAG algorithm
  uint16_t v = value;
  v = v - ((v >> 1) & 0x5555);
  v = (v & 0x3333) + ((v >> 2) & 0x3333);
  v = (v + (v >> 4)) & 0x0F0F;
  v = (v + (v >> 8)) & 0x1F;
  return v;
}


uint8_t bitCount(uint32_t value)
{
  //  parallel adding in a register SWAG algorithm
  uint32_t v = value;
  v = v - ((v >> 1) & 0x55555555);
  v = (v & 0x33333333) + ((v >> 2) & 0x33333333);
  v = (v + (v >> 4)) & 0x0F0F0F0F;
  v =  v + (v >> 8);
  v = (v + (v >> 16)) & 0x3F;
  return v;
}


uint8_t bitCount(uint64_t value)
{
  //  parallel adding in a register SWAG algorithm
  uint64_t v = value;
  v = v - ((v >> 1) & 0x5555555555555555);
  v = (v & 0x3333333333333333) + ((v >> 2) & 0x3333333333333333);
  v = (v + (v >> 4)) & 0x0F0F0F0F0F0F0F0F;
  v =  v + (v >> 8);
  v =  v + (v >> 16);
  v = (v + (v >> 32)) & 0x7F;
  return v;
}


////////////////////////////////////////////////
//
//  BIT REVERSE
//
uint8_t bitReverse(uint8_t value)
{
  uint8_t x = value;
  x = (((x & 0xAA) >> 1) | ((x & 0x55) << 1));
  x = (((x & 0xCC) >> 2) | ((x & 0x33) << 2));
  x = (x >> 4) | (x << 4);
  return x;
}


uint16_t bitReverse(uint16_t value)
{
  uint16_t x = value;
  x = (((x & 0xAAAA) >> 1) | ((x & 0x5555) << 1));
  x = (((x & 0xCCCC) >> 2) | ((x & 0x3333) << 2));
  x = (((x & 0xF0F0) >> 4) | ((x & 0x0F0F) << 4));
  x = (x >> 8) | (x << 8);
  return x;
}


uint32_t bitReverse(uint32_t value)
{
  uint32_t x = value;
  x = (((x & 0xAAAAAAAA) >> 1)  | ((x & 0x55555555) << 1));
  x = (((x & 0xCCCCCCCC) >> 2)  | ((x & 0x33333333) << 2));
  x = (((x & 0xF0F0F0F0) >> 4)  | ((x & 0x0F0F0F0F) << 4));
  x = (((x & 0xFF00FF00) >> 8)  | ((x & 0x00FF00FF) << 8));
  x = (x >> 16) | (x << 16);
  return x;
}


uint64_t bitReverse(uint64_t value)
{
  uint64_t x = value;
  x = (((x & 0xAAAAAAAAAAAAAAAA) >> 1)  | ((x & 0x5555555555555555) << 1));
  x = (((x & 0xCCCCCCCCCCCCCCCC) >> 2)  | ((x & 0x3333333333333333) << 2));
  x = (((x & 0xF0F0F0F0F0F0F0F0) >> 4)  | ((x & 0x0F0F0F0F0F0F0F0F) << 4));
  x = (((x & 0xFF00FF00FF00FF00) >> 8)  | ((x & 0x00FF00FF00FF00FF) << 8));
  x = (((x & 0xFFFF0000FFFF0000) >> 16) | ((x & 0x0000FFFF0000FFFF) << 16));
  x = (x >> 32) | (x << 32);
  return x;
}


////////////////////////////////////////////////
//
//  NYBBLE REVERSE
//
uint8_t nybbleReverse(uint8_t value)
{
  uint8_t x = value;
  x = (x >> 4) | (x << 4);
  return x;
}


uint16_t nybbleReverse(uint16_t value)
{
  uint16_t x = value;
  x = (((x & 0xF0F0) >> 4) | ((x & 0x0F0F) << 4));
  x = (x >> 8) | (x << 8);
  return x;
}


uint32_t nybbleReverse(uint32_t value)
{
  uint32_t x = value;
  x = (((x & 0xF0F0F0F0) >> 4)  | ((x & 0x0F0F0F0F) << 4));
  x = (((x & 0xFF00FF00) >> 8)  | ((x & 0x00FF00FF) << 8));
  x = (x >> 16) | (x << 16);
  return x;
}


uint64_t nybbleReverse(uint64_t value)
{
  uint64_t x = value;
  x = (((x & 0xF0F0F0F0F0F0F0F0) >> 4)  | ((x & 0x0F0F0F0F0F0F0F0F) << 4));
  x = (((x & 0xFF00FF00FF00FF00) >> 8)  | ((x & 0x00FF00FF00FF00FF) << 8));
  x = (((x & 0xFFFF0000FFFF0000) >> 16) | ((x & 0x0000FFFF0000FFFF) << 16));
  x = (x >> 32) | (x << 32);
  return x;
}


////////////////////////////////////////////////
//
//  BYTE REVERSE
//
uint16_t byteReverse(uint16_t value)
{
  uint16_t x = value;
  x = (x >> 8) | (x << 8);
  return x;
}


uint32_t byteReverse(uint32_t value)
{
  uint32_t x = value;
  x = (((x & 0xFF00FF00) >> 8)  | ((x & 0x00FF00FF) << 8));
  x = (x >> 16) | (x << 16);
  return x;
}


uint64_t byteReverse(uint64_t value)
{
  uint64_t x = value;
  x = (((x & 0xFF00FF00FF00FF00) >> 8)  | ((x & 0x00FF00FF00FF00FF) << 8));
  x = (((x & 0xFFFF0000FFFF0000) >> 16) | ((x & 0x0000FFFF0000FFFF) << 16));
  x = (x >> 32) | (x << 32);
  return x;
}


////////////////////////////////////////////////
//
//  WORD REVERSE
//
uint32_t wordReverse(uint32_t value)
{
  uint32_t x = value;
  x = (x >> 16) | (x << 16);
  return x;
}


uint64_t wordReverse(uint64_t value)
{
  uint64_t x = value;
  x = (((x & 0xFFFF0000FFFF0000) >> 16) | ((x & 0x0000FFFF0000FFFF) << 16));
  x = (x >> 32) | (x << 32);
  return x;
}


////////////////////////////////////////////////
//
//  SWAP HI LO
//
uint8_t swap(uint8_t value)
{
  return (value << 4) | (value >> 4);
}


uint16_t swap(uint16_t value)
{
  return (value << 8) | (value >> 8);
}


uint32_t swap(uint32_t value)
{
  return (value << 16) | (value >> 16);
}


uint64_t swap(uint64_t value)
{
  return (value << 32) | (value >> 32);
}


////////////////////////////////////////////////
//
//  BIT ROTATE LEFT
//
uint8_t bitRotateLeft(uint8_t value, uint8_t position)
{
  if (position == 0) return value;
  if (position > 7) return value;
  return (value << position) | (value >> (8 - position));
}


uint16_t bitRotateLeft(uint16_t value, uint8_t position)
{
  if (position == 0) return value;
  if (position > 15) return value;
  return (value << position) | (value >> (16 - position));
}


uint32_t bitRotateLeft(uint32_t value, uint8_t position)
{
  if (position == 0) return value;
  if (position > 31) return value;
  return (value << position) | (value >> (32 - position));
}


uint64_t bitRotateLeft(uint64_t value, uint8_t position)
{
  if (position == 0) return value;
  if (position > 63) return value;
  return (value << position) | (value >> (64 - position));
}


////////////////////////////////////////////////
//
//  BIT ROTATE RIGHT
//
uint8_t  bitRotateRight(uint8_t value, uint8_t position)
{
  if (position == 0) return value;
  if (position > 7) return value;
  return (value << (8 - position)) | (value >> position);
}


uint16_t bitRotateRight(uint16_t value, uint8_t position)
{
  if (position == 0) return value;
  if (position > 15) return value;
  return (value << (16 - position)) | (value >> position);
}


uint32_t bitRotateRight(uint32_t value, uint8_t position)
{
  if (position == 0) return value;
  if (position > 31) return value;
  return (value << (32 - position)) | (value >> position);
}


uint64_t bitRotateRight(uint64_t value, uint8_t position)
{
  if (position == 0) return value;
  if (position > 63) return value;
  return (value << (64 - position)) | (value >> position);
}


////////////////////////////////////////////////////
//
//  BIT FLIP
//
uint8_t bitFlip(uint8_t value, uint8_t position)
{
  if (position > 7) return value;
  return value ^ (1 << position);
}


uint16_t bitFlip(uint16_t value, uint8_t position)
{
  if (position > 15) return value;
  return value ^ (1 << position);
}


uint32_t bitFlip(uint32_t value, uint8_t position)
{
  if (position > 31) return value;
  return value ^ (1UL << position);
}


uint64_t bitFlip(uint64_t value, uint8_t position)
{
  if (position > 63) return value;
  return value ^ (1ULL << position);
}


////////////////////////////////////////////////////
//
//  BIT ROT
//
uint8_t bitRotRef(uint8_t value, float chance)
{
  if (random(BH_BIG_NR) > chance * BH_BIG_NR) return value;
  return value ^ (1 << random(8));
}


uint16_t bitRotRef(uint16_t value, float chance)
{
  if (random(BH_BIG_NR) > chance * BH_BIG_NR) return value;
  return value ^ (1UL << random(16));
}


uint32_t bitRotRef(uint32_t value, float chance)
{
  if (random(BH_BIG_NR) > chance * BH_BIG_NR) return value;
  return value ^ (1UL << random(32));
}


uint64_t bitRotRef(uint64_t value, float chance)
{
  if (random(BH_BIG_NR) > chance * BH_BIG_NR) return value;
  return value ^ (1ULL << random(64));
}


uint8_t bitRot(uint8_t value, float chance, uint16_t times)
{
  while(times--)
  {
    uint32_t r = random(BH_BIG_NR);
    if ( r < chance * BH_BIG_NR)
    {
      value ^= (1 << (r & 7));
    }
  }
  return value;
}


uint16_t bitRot(uint16_t value, float chance, uint16_t times)
{
  while(times--)
  {
    uint32_t r = random(BH_BIG_NR);
    if ( r < chance * BH_BIG_NR)
    {
      value ^= (1 << (r & 15));
    }
  }
  return value;
};


uint32_t bitRot(uint32_t value, float chance, uint16_t times)
{
  while(times--)
  {
    uint32_t r = random(BH_BIG_NR);
    if ( r < chance * BH_BIG_NR)
    {
      value ^= (1 << (r & 31));
    }
  }
  return value;
};


uint64_t bitRot(uint64_t value, float chance, uint16_t times)
{
  while(times--)
  {
    uint32_t r = random(BH_BIG_NR);
    if ( r < chance * BH_BIG_NR)
    {
      value ^= (1 << (r & 63));
    }
  }
  return value;
};




////////////////////////////////////////////////////
//
//  BIT-SET64 -CLEAR64 -TOGGLE64 -READ64 -WRITE64
//

//  FUNCTIONS
#if defined(__AVR__)
//  optimized for performance

void bitSet64(uint64_t & x, uint8_t n)
{
  if (n > 47)      x |= (0x1000000000000 << (n - 48));
  else if (n > 31) x |= (0x100000000 << (n - 32));
  else if (n > 23) x |= (0x1000000 << (n - 24));
  else if (n > 15) x |= (0x10000 << (n - 16));
  else             x |= (0x1 << n);
}


void bitClear64(uint64_t & x, uint8_t n)
{
  if (n > 47)      x &= ~(0x1000000000000 << (n - 48));
  else if (n > 31) x &= ~(0x100000000 << (n - 32));
  else if (n > 23) x &= ~(0x1000000 << (n - 24));
  else if (n > 15) x &= ~(0x10000 << (n - 16));
  else             x &= ~(0x1 << n);
}


void bitToggle64(uint64_t & x, uint8_t n)
{
  if (n > 47)      x ^= (0x1000000000000 << (n - 48));
  else if (n > 31) x ^= (0x100000000 << (n - 32));
  else if (n > 23) x ^= (0x1000000 << (n - 24));
  else if (n > 15) x ^= (0x10000 << (n - 16));
  else             x ^= (0x1 << n);
}


#elif defined(ESP32)
//  optimized for performance

void bitSet64(uint64_t & x, uint8_t n)
{
  if (n > 31) x |= (0x100000000 << (n - 32));
  else        x |= (0x1 << n);
}


void bitClear64(uint64_t & x, uint8_t n)
{
  if (n > 31) x &= ~(0x100000000 << (n - 32));
  else        x &= ~(0x1 << n);
}


void bitToggle64(uint64_t & x, uint8_t n)
{
  if (n > 31) x ^= (0x100000000 << (n - 32));
  else        x ^= (0x1 << n);
}


#else
//  slower reference implementation

void bitSet64(uint64_t & x, uint8_t bit)
{
  x |= (1ULL << bit);
}


void bitClear64(uint64_t & x, uint8_t bit)
{
  x &= ~(1ULL << bit);
}


void bitToggle64(uint64_t & x, uint8_t bit)
{
  x ^= (1ULL << bit);
}


#endif


uint8_t bitRead64(uint64_t & x, uint8_t bit)
{
  return ((x & (1ULL << bit)) > 0);
}


void bitWrite64(uint64_t & x, uint8_t bit, uint8_t value)
{
  if (value) bitSet64(x, bit);
  else bitClear64(x, bit);
}


////////////////////////////////////////////////////
//
//  BITS NEEDED
//

//  reference
uint8_t bitsNeededRef(uint64_t x)
{
  uint8_t n = 0;
  while (x)
  {
    x >>= 1;
    n++;
  }
  return n;
}


//  workers
uint8_t bitsNeeded(uint8_t x)
{
  uint8_t n = 0;
  while (x)
  {
    x >>= 1;
    n++;
  }
  return n;
}


uint8_t bitsNeeded(uint16_t x)
{
  uint8_t y = x >> 8;
  if (y != 0) return bitsNeeded(y) + 8;
  return bitsNeeded((uint8_t)x);
}


uint8_t bitsNeeded(uint32_t x)
{
  uint16_t y = x >> 16;
  if (y != 0) return bitsNeeded(y) + 16;
  return bitsNeeded((uint16_t)x);
}


uint8_t bitsNeeded(uint64_t x)
{
  uint32_t y = x >> 32;
  if (x >> 32) return bitsNeeded(y) + 32;
  return bitsNeeded((uint32_t)x);
}


//  -- END OF FILE --

