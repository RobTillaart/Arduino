//
//    FILE: CRC16.cpp
//  AUTHOR: Rob Tillaart
// PURPOSE: Arduino class for CRC16
//     URL: https://github.com/RobTillaart/CRC


#include "CRC16.h"


CRC16::CRC16()
{
  reset();
}


void CRC16::reset()
{
  _polynome   = CRC16_DEFAULT_POLYNOME;
  _startMask  = 0;
  _endMask    = 0;
  _crc        = 0;
  _reverseIn  = false;
  _reverseOut = false;
  _started    = false;
  _count      = 0;
}


void CRC16::restart()
{
  _started = true;
  _crc     = _startMask;
  _count   = 0;
}


void CRC16::add(uint8_t value)
{
  _count++;
  _update(value);
}


void CRC16::add(uint8_t * array, uint32_t length)
{
  _count += length;
  while (length--)
  {
    yield();
    uint8_t data = *array++;
    _update(data);
  }
}


uint16_t CRC16::getCRC()
{
  uint16_t rv = _crc;
  if (_reverseOut) rv = _reverse(rv);
  rv ^= _endMask;
  return rv;
}


void CRC16::_update(uint8_t value)
{
  if (!_started) restart();
  if (_reverseIn) value = _reverse(value);
  _crc ^= ((uint16_t)value) << 8;;
  for (uint8_t i = 8; i; i--) 
  {
    if (_crc & (1UL << 15))
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


uint16_t CRC16::_reverse(uint16_t in)
{
  uint16_t x = in;
  x = (((x & 0XAAAA) >> 1) | ((x & 0X5555) << 1));
  x = (((x & 0xCCCC) >> 2) | ((x & 0X3333) << 2));
  x = (((x & 0xF0F0) >> 4) | ((x & 0X0F0F) << 4));
  x = (( x >> 8) | (x << 8));
  return x;
}

// -- END OF FILE --