//
//    FILE: CRC32.cpp
//  AUTHOR: Rob Tillaart
// PURPOSE: Arduino class for CRC32;
//     URL: https://github.com/RobTillaart/CRC


#include "CRC32.h"
#include "CrcFastReverse.h"


CRC32::CRC32(uint32_t polynome,
             uint32_t initial,
             uint32_t xorOut,
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

void CRC32::reset(uint32_t polynome,
                  uint32_t initial,
                  uint32_t xorOut,
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

void CRC32::restart()
{
  _crc = _initial;
  _count = 0u;
}

uint32_t CRC32::calc() const
{
  uint32_t rv = _crc;
  if (_reverseOut) rv = reverse32bits(rv);
  rv ^= _xorOut;
  return rv;
}

crc_size_t CRC32::count() const
{
  return _count;
}

void CRC32::add(uint8_t value)
{
  _count++;
  _add(value);
}

void CRC32::add(const uint8_t *array, crc_size_t length)
{
  _count += length;
  while (length--)
  {
    _add(*array++);
  }
}

void CRC32::add(const uint8_t *array, crc_size_t length, crc_size_t yieldPeriod)
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

void CRC32::_add(uint8_t value)
{
  if (_reverseIn) value = reverse8bits(value);
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

uint32_t CRC32::getCRC() const
{
  return calc();
}


//  -- END OF FILE --

