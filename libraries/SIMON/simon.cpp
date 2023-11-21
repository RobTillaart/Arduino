//
//    FILE: simon.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2022-05-26
// VERSION: 0.1.3
// PURPOSE: Arduino library for SIMON
//     URL: https://github.com/RobTillaart/SIMON


#include "simon.h"


SIMON::SIMON()
{
  _idx  = 0;
  _size = 0;
}


bool SIMON::setSequence(uint8_t * array, uint8_t length)
{
  if ((length > _maxSize) || (array == NULL))
  {
    _size = 0;
    return false;
  }
  for (uint8_t i = 0; i < length; i++)
  {
    _sequence[i] = array[i];
  }
  _size = length;
  return true;
}


bool SIMON::generateSequence(uint8_t length, uint8_t minimum, uint8_t maximum)
{
  if (length > _maxSize)
  {
    _size = 0;
    return false;
  }
  randomSeed(micros());
  for (uint8_t i = 0; i < length; i++)
  {
    _sequence[i] = random(minimum, maximum + 1);
  }
  _size = length;
  return true;
}


uint8_t SIMON::getSequence(uint8_t * array)
{
  for (uint8_t i = 0; i < _size; i++)
  {
    array[i] = _sequence[i];
  }
  return _size;
}


void SIMON::clear()
{
  _idx = 0;
}


void SIMON::add(uint8_t value)
{
  if (_idx == _maxSize)
  {
    _idx = 0;
  }
  _answer[_idx] = value;
  _idx++;
}


bool SIMON::verify()
{
  return verify(_answer, _idx);
}


bool SIMON::verify(uint8_t * array, uint8_t length)
{
  if (length != _size) return false;
  for (uint8_t i = 0; i < _size; i++)
  {
    if (_sequence[i] != array[i]) return false;
  }
  return true;
}


uint8_t SIMON::length()
{
  return _idx;
}


uint8_t SIMON::size()
{
  return _size;
}


uint8_t SIMON::maxSize()
{
  return _maxSize;
}


//  -- END OF FILE --

