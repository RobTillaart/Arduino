//
//    FILE: CRC8.cpp
//  AUTHOR: Rob Tillaart
// PURPOSE: Arduino class for CRC8;
//     URL: https://github.com/RobTillaart/CRC


#include "CRC8.h"


CRC8::CRC8()
{
  reset();
}


CRC8::CRC8(uint8_t polynome, uint8_t XORstart, uint8_t XORend, bool reverseIn, bool reverseOut)
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


void CRC8::reset()
{
  _polynome   = CRC8_DEFAULT_POLYNOME;
  _startMask  = 0;
  _endMask    = 0;
  _crc        = 0;
  _reverseIn  = false;
  _reverseOut = false;
  _started    = false;
  _count      = 0;
}


void CRC8::restart()
{
  _started = true;
  _crc     = _startMask;
  _count   = 0;
}


void CRC8::add(uint8_t value)
{
  _count++;
  if (_canYield && ((_count & 0xFF) == 0)) yield();
  _update(value);
}


void CRC8::add(const uint8_t * array, uint16_t length)
{
  while (length--)
  {
    add(*array++);
  }
}


uint8_t CRC8::getCRC()
{
  uint8_t rv = _crc;
  if (_reverseOut) rv = _reverse(rv);
  rv ^= _endMask;
  return rv;
}


void CRC8::_update(uint8_t value)
{
  if (!_started) restart();
  if (_reverseIn) value = _reverse(value);
  _crc ^= value;
  for (uint8_t i = 8; i; i--) 
  {
    if (_crc & (1 << 7))
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


uint8_t CRC8::_reverse(uint8_t in)
{
  uint8_t x = in;
  x = (((x & 0xAA) >> 1) | ((x & 0x55) << 1));
  x = (((x & 0xCC) >> 2) | ((x & 0x33) << 2));
  x =          ((x >> 4) | (x << 4));
  return x;
}


// -- END OF FILE --

