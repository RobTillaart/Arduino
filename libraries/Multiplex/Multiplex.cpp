//
//    FILE: Multiplex.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.3
// PURPOSE: Arduino library to multiplex streams
//    DATE: 2021-01-09
//     URL: https://github.com/RobTillaart/Multiplex
//
//  HISTORY:
//  0.1.0   2021-01-09  initial version
//  0.2.0   2021-08-09  See issues #2 and #3
//  0.2.1   2021-09-12  made index(Stream) public; added stream(index)
//                      enable() / disable() return true on success
//                      added free() function
//                      minor refactor.
//  0.2.2   2021-09-12  add remove(Stream) + remove(index);
//  0.2.3   2021-12-22  update library.json, readme, license, minor edits



#include "Multiplex.h"


Multiplex::Multiplex()
{
  // malloc ?
  _size = MAX_MULTIPLEX;
  reset();
}


Multiplex::~Multiplex()
{
  // free ?
}


void Multiplex::reset()
{
  for (uint8_t i = 0; i < _size; i++)
  {
    _enabled[i] = false;
  }
  _count = 0;
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
  if (idx == 0xFF) return false;
  return remove(idx);
};


bool Multiplex::remove(uint8_t idx)
{
  if (idx >= _count) return false;
  _count--;
  if (idx != _count)
  {
    _stream[idx]  = _stream[_count];
    _enabled[idx] = _enabled[_count];
  }
  return true;
};


///////////////////////////////////////////
//
// WRITE - the core
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
  return n;
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


bool Multiplex::isEnabledStream(Print *stream)
{
  return isEnabled(index(stream));
}


// -- END OF FILE --

