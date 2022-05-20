//
//    FILE: CRC12.cpp
//  AUTHOR: Rob Tillaart
// PURPOSE: Arduino class for CRC12
//     URL: https://github.com/RobTillaart/CRC


#include "CRC12.h"


CRC12::CRC12()
{
  reset();
}


CRC12::CRC12(uint16_t polynome, uint16_t XORstart, uint16_t XORend, bool reverseIn, bool reverseOut)
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


void CRC12::reset()
{
  _polynome   = CRC12_DEFAULT_POLYNOME;
  _startMask  = 0;
  _endMask    = 0;
  _crc        = 0;
  _reverseIn  = false;
  _reverseOut = false;
  _started    = false;
  _count      = 0;
  _canYield   = true;
}


void CRC12::restart()
{
  _started = true;
  _crc     = _startMask;
  _count   = 0;
}


void CRC12::add(uint8_t value)
{
  _count++;
  if (_canYield && ((_count & 0xFF) == 0)) yield();
  _update(value);
}


void CRC12::add(const uint8_t * array, uint16_t length)
{
  while (length--)
  {
    add(*array++);
  }
}


uint16_t CRC12::getCRC()
{
  uint16_t rv = _crc;
  if (_reverseOut) rv = _reverse(rv);
  rv ^= _endMask;
  return rv & 0x0FFF;
}


void CRC12::_update(uint8_t value)
{
  if (!_started) restart();
  if (_reverseIn) value = _reverse8(value);
  _crc ^= ((uint16_t)value) << 4;
  for (uint8_t i = 8; i; i--) 
  {
    if (_crc & (1 << 11))
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


uint16_t CRC12::_reverse(uint16_t in)
{
  // return reverse16(in) >> 4;
  uint16_t x = in;
  x = (((x & 0XAAAA) >> 1) | ((x & 0X5555) << 1));
  x = (((x & 0xCCCC) >> 2) | ((x & 0X3333) << 2));
  x = (((x & 0xF0F0) >> 4) | ((x & 0X0F0F) << 4));
  x = (( x >> 8) | (x << 8));
  return x >> 4;
}


uint8_t CRC12::_reverse8(uint8_t in)
{
  uint8_t x = in;
  x = (((x & 0xAA) >> 1) | ((x & 0x55) << 1));
  x = (((x & 0xCC) >> 2) | ((x & 0x33) << 2));
  x =          ((x >> 4) | (x << 4));
  return x;
}


// -- END OF FILE --

