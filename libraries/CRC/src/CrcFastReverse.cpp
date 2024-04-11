//
//    FILE: CrcFastReverse.cpp
//  AUTHOR: vovagorodok
// PURPOSE: Arduino class for CRC
//     URL: https://github.com/RobTillaart/CRC


#include "CrcFastReverse.h"


uint8_t reverse8bits(uint8_t in)
{
  uint8_t x = in;
  x = (((x & 0xAA) >> 1) | ((x & 0x55) << 1));
  x = (((x & 0xCC) >> 2) | ((x & 0x33) << 2));
  x =          ((x >> 4) | (x << 4));
  return x;
}

uint16_t reverse16bits(uint16_t in)
{
  uint16_t x = in;
  x = (((x & 0XAAAA) >> 1) | ((x & 0X5555) << 1));
  x = (((x & 0xCCCC) >> 2) | ((x & 0X3333) << 2));
  x = (((x & 0xF0F0) >> 4) | ((x & 0X0F0F) << 4));
  x = (( x >> 8) | (x << 8));
  return x;
}

uint16_t reverse12bits(uint16_t in)
{
  return reverse16bits(in) >> 4;
}

uint32_t reverse32bits(uint32_t in)
{
  uint32_t x = in;
  x = (((x & 0xAAAAAAAA) >> 1)  | ((x & 0x55555555) << 1));
  x = (((x & 0xCCCCCCCC) >> 2)  | ((x & 0x33333333) << 2));
  x = (((x & 0xF0F0F0F0) >> 4)  | ((x & 0x0F0F0F0F) << 4));
  x = (((x & 0xFF00FF00) >> 8)  | ((x & 0x00FF00FF) << 8));
  x = (x >> 16) | (x << 16);
  return x;
}

uint64_t reverse64bits(uint64_t in)
{
  uint64_t x = in;
  x = (((x & 0xAAAAAAAAAAAAAAAA) >> 1)  | ((x & 0x5555555555555555) << 1));
  x = (((x & 0xCCCCCCCCCCCCCCCC) >> 2)  | ((x & 0x3333333333333333) << 2));
  x = (((x & 0xF0F0F0F0F0F0F0F0) >> 4)  | ((x & 0x0F0F0F0F0F0F0F0F) << 4));
  x = (((x & 0xFF00FF00FF00FF00) >> 8)  | ((x & 0x00FF00FF00FF00FF) << 8));
  x = (((x & 0xFFFF0000FFFF0000) >> 16) | ((x & 0x0000FFFF0000FFFF) << 16));
  x = (x >> 32) | (x << 32);
  return x;
}


uint8_t reverse8(uint8_t in)
{
  return reverse8bits(in);
}

uint16_t reverse12(uint16_t in)
{
  return reverse12bits(in);
}

uint16_t reverse16(uint16_t in)
{
  return reverse16bits(in);
}

uint32_t reverse32(uint32_t in)
{
  return reverse32bits(in);
}

uint64_t reverse64(uint64_t in)
{
  return reverse64bits(in);
}

