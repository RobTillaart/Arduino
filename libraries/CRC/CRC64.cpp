//
//    FILE: CRC64.cpp
//  AUTHOR: Rob Tillaart
// PURPOSE: Arduino class for CRC64;
//     URL: https://github.com/RobTillaart/CRC


#include "CRC64.h"


CRC64::CRC64()
{
  reset();
}


void CRC64::reset()
{
  _polynome   = CRC64_DEFAULT_POLYNOME;
  _startMask  = 0;
  _endMask    = 0;
  _crc        = 0;
  _reverseIn  = false;
  _reverseOut = false;
  _started    = false;
  _count      = 0;
}


void CRC64::restart()
{
  _started = true;
  _crc     = _startMask;
  _count   = 0;
}


void CRC64::add(uint8_t value)
{
  _count++;
  _update(value);
}


void CRC64::add(uint8_t * array, uint32_t length)
{
  _count += length;
  while (length--)
  {
    yield();
    _update(*array++);
  }
}


uint64_t CRC64::getCRC()
{
  uint64_t rv = _crc;
  if (_reverseOut) rv = _reverse(rv);
  rv ^=_endMask;
  return rv;
}


void CRC64::_update(uint8_t value)
{
  if (!_started) restart();
  if (_reverseIn) value = _reverse(value);
  _crc ^= ((uint64_t)value) << 56;;
  for (uint8_t i = 8; i; i--) 
  {
    if (_crc & (1ULL << 63))
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


uint64_t CRC64::_reverse(uint64_t in)
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

// -- END OF FILE --