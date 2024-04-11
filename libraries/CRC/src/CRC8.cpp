//
//    FILE: CRC8.cpp
//  AUTHOR: Rob Tillaart
// PURPOSE: Arduino class for CRC8;
//     URL: https://github.com/RobTillaart/CRC


#include "CRC8.h"
#include "CrcFastReverse.h"


CRC8::CRC8(uint8_t polynome,
           uint8_t initial,
           uint8_t xorOut,
           bool reverseIn,
           bool reverseOut) :
  _polynome(polynome),
  _initial(initial),
  _xorOut(xorOut),
  _reverseIn(reverseIn),
  _reverseOut(reverseOut),
  _crc(initial),
  _count(0u)
{}

void CRC8::reset(uint8_t polynome,
                 uint8_t initial,
                 uint8_t xorOut,
                 bool reverseIn,
                 bool reverseOut)
{
  _polynome = polynome;
  _initial = initial;
  _xorOut = xorOut;
  _reverseIn = reverseIn;
  _reverseOut = reverseOut;
  restart();
}

void CRC8::restart()
{
  _crc = _initial;
  _count = 0u;
}

uint8_t CRC8::calc() const
{
  uint8_t rv = _crc;
  if (_reverseOut) rv = reverse8bits(rv);
  rv ^= _xorOut;
  return rv;
}

crc_size_t CRC8::count() const
{
  return _count;
}

void CRC8::add(uint8_t value)
{
  _count++;
  _add(value);
}

void CRC8::add(const uint8_t *array, crc_size_t length)
{
  _count += length;
  while (length--)
  {
    _add(*array++);
  }
}

void CRC8::add(const uint8_t *array, crc_size_t length, crc_size_t yieldPeriod)
{
  _count += length;
  crc_size_t period = yieldPeriod;
  while (length--)
  {
    _add(*array++);
    if (--period == 0)
    {
      yield();
      period = yieldPeriod;
    }
  }
}

void CRC8::_add(uint8_t value)
{
  if (_reverseIn) value = reverse8bits(value);
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

uint8_t CRC8::getCRC() const
{
  return calc();
}


//  -- END OF FILE --

