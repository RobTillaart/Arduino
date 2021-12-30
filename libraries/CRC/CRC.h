#pragma once
//
//    FILE: CRC.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.4
// PURPOSE: Arduino library fir CRC8, CRC16, CRC16-CCITT, CRC32
//     URL: https://github.com/RobTillaart/CRC
//


#include "Arduino.h"


#define CRC_LIB_VERSION       (F("0.1.4"))


////////////////////////////////////////////////////////////////
//
// fast reverse from bitHelper library
//

uint8_t reverse8(uint8_t in)
{
  uint8_t x = in;
  x = (((x & 0xAA) >> 1) | ((x & 0x55) << 1));
  x = (((x & 0xCC) >> 2) | ((x & 0x33) << 2));
  x =          ((x >> 4) | (x << 4));
  return x;
}


uint16_t reverse16(uint16_t in)
{
  uint16_t x = in;
  x = (((x & 0XAAAA) >> 1) | ((x & 0X5555) << 1));
  x = (((x & 0xCCCC) >> 2) | ((x & 0X3333) << 2));
  x = (((x & 0xF0F0) >> 4) | ((x & 0X0F0F) << 4));
  x = (( x >> 8) | (x << 8));
  return x;
}


uint32_t reverse32(uint32_t in)
{
  uint32_t x = in;
  x = (((x & 0xAAAAAAAA) >> 1)  | ((x & 0x55555555) << 1));
  x = (((x & 0xCCCCCCCC) >> 2)  | ((x & 0x33333333) << 2));
  x = (((x & 0xF0F0F0F0) >> 4)  | ((x & 0x0F0F0F0F) << 4));
  x = (((x & 0xFF00FF00) >> 8)  | ((x & 0x00FF00FF) << 8));
  x = (x >> 16) | (x << 16);
  return x;
}


uint64_t reverse64(uint64_t in)
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


///////////////////////////////////////////////////////////////////////////////////

// CRC POLYNOME = x8 + x5 + x4 + 1 = 1001 1000 = 0x8C
uint8_t crc8(const uint8_t *array, uint8_t length, const uint8_t polynome = 0xD5, const uint8_t startmask = 0x00, const uint8_t endmask = 0x00, const bool reverseIn = false, const bool reverseOut = false)
{
  uint8_t crc = startmask;
  while (length--) 
  {
    uint8_t data = *array++;
    if (reverseIn) data = reverse8(data);
    crc ^= data;
    for (uint8_t i = 8; i; i--) 
    {
      if (crc & 0x80)
      {
        crc <<= 1;
        crc ^= polynome;
      }
      else
      {
        crc <<= 1;
      }
    }
  }
  crc ^= endmask;
  if (reverseOut) crc = reverse8(crc);
  return crc;
}


// CRC POLYNOME = x15 + 1 =  1000 0000 0000 0001 = 0x8001
uint16_t crc16(const uint8_t *array, uint8_t length, const uint16_t polynome = 0x8001, const uint16_t startmask = 0x0000, const uint16_t endmask = 0x0000, const bool reverseIn = false, const bool reverseOut = false)
{
  uint16_t crc = startmask;
  while (length--) 
  {
    uint8_t data = *array++;
    if (reverseIn) data = reverse8(data);
    crc ^= ((uint16_t)data) << 8;
    for (uint8_t i = 8; i; i--) 
    {
      if (crc & (1 << 15))
      {
        crc <<= 1;
        crc ^= polynome;
      }
      else
      {
        crc <<= 1;
      }
    }
  }
  if (reverseOut) crc = reverse16(crc);
  crc ^= endmask;
  return crc;
}


// CRC-CCITT POLYNOME = x13 + X5 + 1 =  0001 0000 0010 0001 = 0x1021
uint16_t crc16_CCITT(uint8_t *array, uint8_t length)
{
  return crc16(array, length, 0x1021, 0xFFFF);
}


// CRC-32 POLYNOME =  x32 + ..... + 1
uint32_t crc32(const uint8_t *array, uint8_t length, const uint32_t polynome = 0x04C11DB7, const uint32_t startmask = 0, const uint32_t endmask = 0, const bool reverseIn = false, const bool reverseOut = false)
{
  uint32_t crc = startmask;
  while (length--) 
  {
    uint8_t data = *array++;
    if (reverseIn) data = reverse8(data);
    crc ^= ((uint32_t) data) << 24;
    for (uint8_t i = 8; i; i--) 
    {
      if (crc & (1UL << 31))
      {
        crc <<= 1;
        crc ^= polynome;
      }
      else
      {
        crc <<= 1;
      }
    }
  }
  crc ^= endmask;
  if (reverseOut) crc = reverse32(crc);
  return crc;
}


// CRC-CCITT POLYNOME =  x64 + ..... + 1
uint64_t crc64(const uint8_t *array, uint8_t length, const uint64_t polynome, const uint64_t startmask, const uint64_t endmask, const bool reverseIn, const bool reverseOut)
{
  uint64_t crc = startmask;
  while (length--) 
  {
    uint8_t data = *array++;
    if (reverseIn) data = reverse8(data);
    crc ^= ((uint64_t) data) << 56;
    for (uint8_t i = 8; i; i--) 
    {
      if (crc & (1ULL << 63))
      {
        crc <<= 1;
        crc ^= polynome;
      }
      else
      {
        crc <<= 1;
      }
    }
  }
  crc ^= endmask;
  if (reverseOut) crc = reverse64(crc);
  return crc;
}


// -- END OF FILE --

