//
//    FILE: CRC32.cpp
//  AUTHOR: Rob Tillaart
// PURPOSE: Arduino class for CRC32;
//     URL: https://github.com/RobTillaart/CRC


#include "CRC32.h"


CRC32::CRC32()
{
  reset();
}


CRC32::CRC32(uint32_t polynome, uint32_t XORstart, uint32_t XORend, bool reverseIn, bool reverseOut)
{
  _polynome   = polynome;
  _startMask  = XORstart;
  _endMask    = XORend;
  _reverseIn  = reverseIn;
  _reverseOut = reverseOut;
  _crc        = 0;
  _started    = false;
  _count      = 0;
  _canYield   = true;
}


void CRC32::reset()
{
  _polynome   = CRC32_DEFAULT_POLYNOME;
  _startMask  = 0;
  _endMask    = 0;
  _crc        = 0;
  _reverseIn  = false;
  _reverseOut = false;
  _started    = false;
  _count      = 0;
  _canYield   = true;
}


void CRC32::restart()
{
  _started = true;
  _crc     = _startMask;
  _count   = 0;
}


void CRC32::add(uint8_t value)
{
  _count++;
  if (_canYield && ((_count & 0xFF) == 0)) yield();
  _update(value);
}


void CRC32::add(const uint8_t * array, uint16_t length)
{
  while (length--)
  {
    add(*array++);
  }
}


uint32_t CRC32::getCRC()
{
  uint32_t rv = _crc;
  if (_reverseOut) rv = _reverse(rv);
  rv ^=_endMask;
  return rv;
}


void CRC32::_update(uint8_t value)
{
  if (!_started) restart();
  if (_reverseIn) value = _reverse8(value);
  _crc ^= ((uint32_t)value) << 24;
  for (uint8_t i = 8; i; i--) 
  {
    if (_crc & (1UL << 31))
    {
      _crc <<= 1;
      _crc ^= _polynome;
    }
    else
    {
      _crc <<= 1;
    }
  }
}


uint32_t CRC32::_reverse(uint32_t in)
{
  uint32_t x = in;
  x = (((x & 0xAAAAAAAA) >> 1)  | ((x & 0x55555555) << 1));
  x = (((x & 0xCCCCCCCC) >> 2)  | ((x & 0x33333333) << 2));
  x = (((x & 0xF0F0F0F0) >> 4)  | ((x & 0x0F0F0F0F) << 4));
  x = (((x & 0xFF00FF00) >> 8)  | ((x & 0x00FF00FF) << 8));
  x = (x >> 16) | (x << 16);
  return x;
}


uint8_t CRC32::_reverse8(uint8_t in)
{
  uint8_t x = in;
  x = (((x & 0xAA) >> 1) | ((x & 0x55) << 1));
  x = (((x & 0xCC) >> 2) | ((x & 0x33) << 2));
  x =          ((x >> 4) | (x << 4));
  return x;
}


// -- END OF FILE --

