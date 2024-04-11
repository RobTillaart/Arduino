//
//    FILE: CRC16.cpp
//  AUTHOR: Rob Tillaart
// PURPOSE: Arduino class for CRC16
//     URL: https://github.com/RobTillaart/CRC


#include "CRC16.h"
#include "CrcFastReverse.h"


CRC16::CRC16(uint16_t polynome,
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

void CRC16::reset(uint16_t polynome,
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

void CRC16::restart()
{
  _crc = _initial;
  _count = 0u;
}

uint16_t CRC16::calc() const
{
  uint16_t rv = _crc;
  if (_reverseOut) rv = reverse16bits(rv);
  rv ^= _xorOut;
  return rv;
}

crc_size_t CRC16::count() const
{
  return _count;
}

void CRC16::add(uint8_t value)
{
  _count++;
  _add(value);
}

void CRC16::add(const uint8_t *array, crc_size_t length)
{
  _count += length;
  while (length--)
  {
    _add(*array++);
  }
}

void CRC16::add(const uint8_t *array, crc_size_t length, crc_size_t yieldPeriod)
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

void CRC16::_add(uint8_t value)
{
  if (_reverseIn) value = reverse8bits(value);
  _crc ^= ((uint16_t)value) << 8;
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

uint16_t CRC16::getCRC() const
{
  return calc();
}


//  -- END OF FILE --

