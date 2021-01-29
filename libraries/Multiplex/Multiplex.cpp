//
//    FILE: Multiplex.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: Arduino library to multiplex streams
//    DATE: 2021-01-09
//     URL: https://github.com/RobTillaart/Multiplex
//
//  HISTORY:
//  0.1.0   2021-01-09  initial version


#include "Multiplex.h"


Multiplex::Multiplex()
{
  reset();
}


void Multiplex::reset()
{
  _size = MAX_MULTIPLEX;
  for (int i = 0; i < _size; i++) _enabled[i] = false;
  _count = 0;
}


bool Multiplex::add(Print * stream)
{
  if (_count >= _size) return false;
  _enabled[_count]  = true;
  _stream[_count++] = stream;
  return true;
};


///////////////////////////////////////////
//
// WRITE - the core
//
size_t Multiplex::write(uint8_t c)
{
  uint8_t n = 0;
  for (uint8_t i = 0; i < _count; i++)
  {
    if (_enabled[i])
    {
      n += _stream[i]->write(c);
    }
  }
  return n;
}


void Multiplex::enable(uint8_t n)
{
  if (n < _count) _enabled[n] = true;
}


void Multiplex::disable(uint8_t n)
{
  if (n < _count) _enabled[n] = false;
}


bool Multiplex::isEnabled(uint8_t n)
{
  if (n >= _count) return false;
  return _enabled[n];
}

// -- END OF FILE --
