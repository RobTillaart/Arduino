#pragma once
//
//    FILE: bitHelpers.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.2
//    DATE: 2015-11-07
// PURPOSE: Arduino library with functions on bit level
//     URL: https://github.com/RobTillaart/bitHelpers
//
// 0.0.1    2015-11-07  initial version
// 0.1.0    2020-07-29  intial release
// 0.1.1    2020-08-10  added BitsNeeded, bitSet64 family
// 0.1.2    2020-12-14  add Adruino-ci + unit tests 

#include "Arduino.h"

#define BH_BIG_NR        1000000000

////////////////////////////////////////////////
//
// BIT COUNT TEST
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
};

uint8_t bitCountKR(uint32_t value)
{
  // Kerningham & Ritchie
  uint32_t v = value;
  uint8_t count = 0;
  while (v)
  {
    count++;
    v &= (v -1);
  }
  return count;
};

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
};

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
};

////////////////////////////////////////////////
//
// BIT COUNT
//
uint8_t bitCount(uint8_t value)
{
  //  parallel adding in a register SWAG algorithm
  uint8_t v = value;
  v = v - ((v >> 1) & 0x55);
  v = (v & 0x33) + ((v >> 2) & 0x33);
  v = (v + (v >> 4)) & 0x0F;
  return v;
};

uint8_t bitCount(uint16_t value)
{
  //  parallel adding in a register SWAG algorithm
  uint16_t v = value;
  v = v - ((v >> 1) & 0x5555);
  v = (v & 0x3333) + ((v >> 2) & 0x3333);
  v = (v + (v >> 4)) & 0x0F0F;
  v = v + (v >> 8);
  return v & 0xFF;
};

uint8_t bitCount(uint32_t value)
{
  //  parallel adding in a register SWAG algorithm
  uint32_t v = value;
  v = v - ((v >> 1) & 0x55555555);
  v = (v & 0x33333333) + ((v >> 2) & 0x33333333);
  v = (v + (v >> 4)) & 0x0F0F0F0F;
  v = v + (v >> 8);
  v = v + (v >> 16);
  return v & 0xFF;
};

uint8_t bitCount(uint64_t value)
{
  //  parallel adding in a register SWAG algorithm
  uint64_t v = value;
  v = v - ((v >> 1) & 0x5555555555555555);
  v = (v & 0x3333333333333333) + ((v >> 2) & 0x3333333333333333);
  v = (v + (v >> 4)) & 0x0F0F0F0F0F0F0F0F;
  v = v + (v >> 8);
  v = v + (v >> 16);
  v = v + (v >> 32);
  return v & 0x7F;
};

////////////////////////////////////////////////
//
// BIT REVERSE
//
uint8_t bitReverse(uint8_t val)
{
  uint8_t x = val;
  x = (((x & 0xAA) >> 1) | ((x & 0x55) << 1));
  x = (((x & 0xCC) >> 2) | ((x & 0x33) << 2));
  x = (x >> 4) | (x << 4);
  return x;
}

uint16_t bitReverse(uint16_t val)
{
  uint16_t x = val;
  x = (((x & 0xAAAA) >> 1) | ((x & 0x5555) << 1));
  x = (((x & 0xCCCC) >> 2) | ((x & 0x3333) << 2));
  x = (((x & 0xF0F0) >> 4) | ((x & 0x0F0F) << 4));
  x = (x >> 8) | (x << 8);
  return x;
}

uint32_t bitReverse(uint32_t val)
{
  uint32_t x = val;
  x = (((x & 0xAAAAAAAA) >> 1)  | ((x & 0x55555555) << 1));
  x = (((x & 0xCCCCCCCC) >> 2)  | ((x & 0x33333333) << 2));
  x = (((x & 0xF0F0F0F0) >> 4)  | ((x & 0x0F0F0F0F) << 4));
  x = (((x & 0xFF00FF00) >> 8)  | ((x & 0x00FF00FF) << 8));
  x = (x >> 16) | (x << 16);
  return x;
}

uint64_t bitReverse(uint64_t val)
{
  uint64_t x = val;
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
// NYBBLE REVERSE
//
uint8_t nybbleReverse(uint8_t val)
{
  uint8_t x = val;
  x = (x >> 4) | (x << 4);
  return x;
}

uint16_t nybbleReverse(uint16_t val)
{
  uint16_t x = val;
  x = (((x & 0xF0F0) >> 4) | ((x & 0x0F0F) << 4));
  x = (x >> 8) | (x << 8);
  return x;
}

uint32_t nybbleReverse(uint32_t val)
{
  uint32_t x = val;
  x = (((x & 0xF0F0F0F0) >> 4)  | ((x & 0x0F0F0F0F) << 4));
  x = (((x & 0xFF00FF00) >> 8)  | ((x & 0x00FF00FF) << 8));
  x = (x >> 16) | (x << 16);
  return x;
}

uint64_t nybbleReverse(uint64_t val)
{
  uint64_t x = val;
  x = (((x & 0xF0F0F0F0F0F0F0F0) >> 4)  | ((x & 0x0F0F0F0F0F0F0F0F) << 4));
  x = (((x & 0xFF00FF00FF00FF00) >> 8)  | ((x & 0x00FF00FF00FF00FF) << 8));
  x = (((x & 0xFFFF0000FFFF0000) >> 16) | ((x & 0x0000FFFF0000FFFF) << 16));
  x = (x >> 32) | (x << 32);
  return x;
}

////////////////////////////////////////////////
//
// BYTE REVERSE
//
uint16_t byteReverse(uint16_t val)
{
  uint16_t x = val;
  x = (x >> 8) | (x << 8);
  return x;
}

uint32_t byteReverse(uint32_t val)
{
  uint32_t x = val;
  x = (((x & 0xFF00FF00) >> 8)  | ((x & 0x00FF00FF) << 8));
  x = (x >> 16) | (x << 16);
  return x;
}

uint64_t byteReverse(uint64_t val)
{
  uint64_t x = val;
  x = (((x & 0xFF00FF00FF00FF00) >> 8)  | ((x & 0x00FF00FF00FF00FF) << 8));
  x = (((x & 0xFFFF0000FFFF0000) >> 16) | ((x & 0x0000FFFF0000FFFF) << 16));
  x = (x >> 32) | (x << 32);
  return x;
}

////////////////////////////////////////////////
//
// WORD REVERSE
//
uint32_t wordReverse(uint32_t val)
{
  uint32_t x = val;
  x = (x >> 16) | (x << 16);
  return x;
}

uint64_t wordReverse(uint64_t val)
{
  uint64_t x = val;
  x = (((x & 0xFFFF0000FFFF0000) >> 16) | ((x & 0x0000FFFF0000FFFF) << 16));
  x = (x >> 32) | (x << 32);
  return x;
}

////////////////////////////////////////////////
//
// SWAP HI LO
//
uint8_t swap(uint8_t val)
{
  return (val << 4) | (val >> 4);
}

uint16_t swap(uint16_t val)
{
  return (val << 8) | (val >> 8);
}

uint32_t swap(uint32_t val)
{
  return (val << 16) | (val >> 16);
}

uint64_t swap(uint64_t val)
{
  return (val << 32) | (val >> 32);
}

////////////////////////////////////////////////
//
// BIT ROTATE LEFT
//
uint8_t  bitRotateLeft(uint8_t value, uint8_t pos)
{
  if (pos > 7) return value;
  return (value << pos) | (value >> (8 - pos));
}

uint16_t bitRotateLeft(uint16_t value, uint8_t pos)
{
  if (pos > 15) return value;
  return (value << pos) | (value >> (16 - pos));
}

uint32_t bitRotateLeft(uint32_t value, uint8_t pos)
{
  if (pos > 31) return value;
  return (value << pos) | (value >> (32 - pos));
}

uint64_t bitRotateLeft(uint64_t value, uint8_t pos)
{
  if (pos > 63) return value;
  return (value << pos) | (value >> (64 - pos));
}

////////////////////////////////////////////////
//
// BIT ROTATE RIGHT
//
uint8_t  bitRotateRight(uint8_t value, uint8_t pos)
{
  if (pos > 7) return value;
  return (value << (8 - pos)) | (value >> pos);
}

uint16_t bitRotateRight(uint16_t value, uint8_t pos)
{
  if (pos > 15) return value;
  return (value << (16 - pos)) | (value >> pos);
}

uint32_t bitRotateRight(uint32_t value, uint8_t pos)
{
  if (pos > 31) return value;
  return (value << (32 - pos)) | (value >> pos);
}

uint64_t bitRotateRight(uint64_t value, uint8_t pos)
{
  if (pos > 63) return value;
  return (value << (64 - pos)) | (value >> pos);
}

////////////////////////////////////////////////////
//
// BIT FLIP
//
uint8_t  bitFlip(uint8_t value, uint8_t pos)
{
  if (pos > 7) return value;
  return value ^ (1 << pos);
}

uint16_t  bitFlip(uint16_t value, uint8_t pos)
{
  if (pos > 15) return value;
  return value ^ (1 << pos);
}

uint32_t  bitFlip(uint32_t value, uint8_t pos)
{
  if (pos > 31) return value;
  return value ^ (1UL << pos);
}

uint64_t  bitFlip(uint64_t value, uint8_t pos)
{
  if (pos > 63) return value;
  return value ^ (1ULL << pos);
}

////////////////////////////////////////////////////
//
// BIT ROT
//
uint8_t  bitRot(uint8_t value, float chance = 0.5)
{
  if (random(BH_BIG_NR) > chance * BH_BIG_NR) return value;
  return value ^ (1 << random(8));
}

uint16_t  bitRot(uint16_t value, float chance = 0.5)
{
  if (random(BH_BIG_NR) > chance * BH_BIG_NR) return value;
  return value ^ (1UL << random(16));
}

uint32_t  bitRot(uint32_t value, float chance = 0.5)
{
  if (random(BH_BIG_NR) > chance * BH_BIG_NR) return value;
  return value ^ (1UL << random(32));
}

uint64_t  bitRot(uint64_t value, float chance = 0.5)
{
  if (random(BH_BIG_NR) > chance * BH_BIG_NR) return value;
  return value ^ (1ULL << random(64));
}

////////////////////////////////////////////////////
//
// BIT-SET64 -CLEAR64 -TOGGLE64 -READ64 -WRITE64
//

// MACROS
// only 64 bit datatypes are handled 64 bit.
#define mbitSet64(value, bit)    ((value) |= (sizeof(value)<5?1UL:1ULL) <<(bit))
#define mbitClear64(value, bit)  ((value) &= ~(sizeof(value)<5?1UL:1ULL) <<(bit))
#define mbitToggle64(value, bit) ((value) ^= (sizeof(value)<5?1UL:1ULL) <<(bit))

#define mbitRead64(value, bit) ( ((value) & ((sizeof(value)<5?1UL:1ULL) <<(bit))) ? 1 : 0)
#define mbitWrite64(value, bit, bitvalue) (bitvalue ? mbitSet64(value, bit) : mbitClear64(value, bit))

// FUNCTIONS
#if defined(__AVR__)

void bitSet64(uint64_t & x, uint8_t n)
{
  if (n > 47)      x |= 0x1000000000000 << (n - 48);
  else if (n > 31) x |= 0x100000000 << (n - 32);
  else if (n > 23) x |= 0x1000000 << (n - 24);
  else if (n > 15) x |= 0x10000 << (n - 16);
  else             x |= 0x1 << n;
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

#elif defined(ESP32) || defined(ESP8266)

void bitSet64(uint64_t & x, uint8_t n)
{
  if (n > 31) x |= 0x100000000 << (n - 32);
  else        x |= 0x1 << n;
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

void bitSet64(uint64_t & x, uint8_t bit)
{
  x |= 1ULL << bit;
}

void bitClear64(uint64_t & x, uint8_t bit)
{
  x &= ~(1ULL << bit);
}

void bitToggle64(uint64_t & x, uint8_t bit)
{
  x ^= 1ULL << bit;
}

#endif

uint8_t bitRead64(uint64_t & x, uint8_t bit)
{
  return x & (1ULL << bit);
}

void bitWrite64(uint64_t & x, uint8_t bit, uint8_t value)
{
  if (value) bitSet64(x, bit);
  else bitClear64(x, bit);
}


////////////////////////////////////////////////////
//
// BITS NEEDED
//

// reference
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

// workers
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

////////////////////////////////////////////////////
//
// NEXT
//




// -- END OF FILE --
