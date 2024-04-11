//
//    FILE: CRC12.cpp
//  AUTHOR: Rob Tillaart
// PURPOSE: Arduino class for CRC12
//     URL: https://github.com/RobTillaart/CRC


#include "CRC12.h"
#include "CrcFastReverse.h"


CRC12::CRC12(uint16_t polynome,
             uint16_t initial,
             uint16_t xorOut,
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

void CRC12::reset(uint16_t polynome,
                  uint16_t initial,
                  uint16_t xorOut,
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

void CRC12::restart()
{
  _crc = _initial;
  _count = 0u;
}

uint16_t CRC12::calc() const
{
  uint16_t rv = _crc;
  if (_reverseOut) rv = reverse12bits(rv);
  rv ^= _xorOut;
  return rv & 0x0FFF;
}

crc_size_t CRC12::count() const
{
  return _count;
}

void CRC12::add(uint8_t value)
{
  _count++;
  _add(value);
}

void CRC12::add(const uint8_t *array, crc_size_t length)
{
  _count += length;
  while (length--)
  {
    _add(*array++);
  }
}

void CRC12::add(const uint8_t *array, crc_size_t length, crc_size_t yieldPeriod)
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

void CRC12::_add(uint8_t value)
{
  if (_reverseIn) value = reverse8bits(value);
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

uint16_t CRC12::getCRC() const
{
  return calc();
}


//  -- END OF FILE --

