//
//    FILE: CRC64.cpp
//  AUTHOR: Rob Tillaart
// PURPOSE: Arduino class for CRC64;
//     URL: https://github.com/RobTillaart/CRC


#include "CRC64.h"
#include "CrcFastReverse.h"


CRC64::CRC64(uint64_t polynome,
             uint64_t initial,
             uint64_t xorOut,
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

void CRC64::reset(uint64_t polynome,
                  uint64_t initial,
                  uint64_t xorOut,
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

void CRC64::restart()
{
  _crc = _initial;
  _count = 0u;
}

uint64_t CRC64::calc() const
{
  uint64_t rv = _crc;
  if (_reverseOut) rv = reverse64bits(rv);
  rv ^= _xorOut;
  return rv;
}

crc_size_t CRC64::count() const
{
  return _count;
}

void CRC64::add(uint8_t value)
{
  _count++;
  _add(value);
}

void CRC64::add(const uint8_t *array, crc_size_t length)
{
  _count += length;
  while (length--)
  {
    _add(*array++);
  }
}

void CRC64::add(const uint8_t *array, crc_size_t length, crc_size_t yieldPeriod)
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

void CRC64::_add(uint8_t value)
{
  if (_reverseIn) value = reverse8bits(value);
  _crc ^= ((uint64_t)value) << 56;
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

uint64_t CRC64::getCRC() const
{
  return calc();
}


//  -- END OF FILE --

