//
//    FILE: Multiplex.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.7
// PURPOSE: Arduino library to multiplex streams
//    DATE: 2021-01-09
//     URL: https://github.com/RobTillaart/Multiplex


#include "Multiplex.h"


Multiplex::Multiplex()
{
  //  malloc ?
  _size = MAX_MULTIPLEX;
  reset();
}


Multiplex::~Multiplex()
{
  //  free ?
}


void Multiplex::reset()
{
  for (uint8_t i = 0; i < _size; i++)
  {
    _enabled[i] = false;
  }
  _count = 0;
  _outputCount = 0;
}


bool Multiplex::add(Print * stream)
{
  if (_count >= _size) return false;
  if (index(stream) != 0xFF) return false;

  _enabled[_count]  = true;
  _stream[_count++] = stream;
  return true;
};


bool Multiplex::remove(Print * stream)
{
  uint8_t idx = index(stream);
  if (idx >= _count) return false;
  return remove(idx);
};


bool Multiplex::remove(uint8_t idx)
{
  if (idx >= _count) return false;
  _count--;
  while (idx < _count)
  {
    _stream[idx]  = _stream[idx + 1];
    _enabled[idx] = _enabled[idx + 1];
    idx++;
  }
  return true;
};


///////////////////////////////////////////
//
//  WRITE - the core
//
size_t Multiplex::write(uint8_t c)
{
  size_t n = 0;
  for (uint8_t i = 0; i < _count; i++)
  {
    if (_enabled[i])
    {
      n += _stream[i]->write(c);
    }
  }
  _outputCount += n;
  return n;
}


size_t Multiplex::write(const uint8_t *buffer, size_t size)
{
  size_t n = 0;
  for (uint8_t i = 0; i < _count; i++)
  {
    if (_enabled[i])
    {
      n += _stream[i]->write(buffer, size);
    }
  }
  _outputCount += n;
  return n;
}


void Multiplex::flush()  //  see issue #13
{
  for (uint8_t i = 0; i < _count; i++)
  {
    if (_enabled[i])
    {
      _stream[i]->flush();
    }
  }
}


uint8_t Multiplex::index(Print *stream)
{
  for (uint8_t i = 0; i < _count; i++)
  {
    if (stream == _stream[i])
    {
      return i;
    }
  }
  return 0xFF;
}


Print * Multiplex::stream(uint8_t n)
{
  if (n >= _count) return NULL;
  return _stream[n];
}


bool Multiplex::enable(uint8_t n)
{
  if (n >= _count) return false;
  _enabled[n] = true;
  return true;
}


bool Multiplex::enableStream(Print *stream)
{
  return enable(index(stream));
}


bool Multiplex::disable(uint8_t n)
{
  if (n >= _count) return false;
  _enabled[n] = false;
  return true;
}


bool Multiplex::disableStream(Print *stream)
{
  return disable(index(stream));
}


bool Multiplex::isEnabled(uint8_t n)
{
  if (n >= _count) return false;
  return _enabled[n];
}


bool Multiplex::isEnabledAny()
{
  for (uint8_t i = 0; i < _count; i++)
  {
    if (_enabled[i]) return true;
  }
  return false;
}


bool Multiplex::isEnabledStream(Print *stream)
{
  return isEnabled(index(stream));
}


//  -- END OF FILE --

