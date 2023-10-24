//
//    FILE: DEVRANDOM.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.2
// PURPOSE: Arduino library for a /dev/random stream - useful for testing
//     URL: https://github.com/RobTillaart/DEVRANDOM


#include "DEVRANDOM.h"


DEVRANDOM::DEVRANDOM()
{
  _next = _rnd();
};


DEVRANDOM::DEVRANDOM(const char * str)
{
  this->print(str);
  _next = _rnd();
};


DEVRANDOM::DEVRANDOM(const uint32_t value)
{
   this->print(value);
  _next = _rnd();
};


DEVRANDOM::DEVRANDOM(const float value)
{
  this->print(value, 6);
  _next = _rnd();
};


int DEVRANDOM::available()
{
  return 1;
};


int DEVRANDOM::peek()
{
  return _next;
};


int DEVRANDOM::read()
{
  uint8_t x = _next;
  _next = _rnd();
  return x;
};


//  keep CI happy as parent class flush is virtual.
void DEVRANDOM::flush()
{
};


size_t DEVRANDOM::write(const uint8_t data)
{
  return write(&data, 1);
};


size_t DEVRANDOM::write(const uint8_t * buffer, size_t size)
{
  uint32_t tmp = _seed;
  for (size_t i = 0; i < size; i++)
  {
    _seed = _seed * (_seed << 8) + buffer[i];
  }
  if (_mode == 0)
  {
    randomSeed(_seed);
  }
  if (_mode == 3)
  {
    _m_z = (_seed == 0) ? 1 : _seed;
    _m_w = ( tmp  == 0) ? 2 : tmp;
  }
  return size;
};


void DEVRANDOM::useMarsaglia()
{
  _mode = 3;
};


void DEVRANDOM::useAnalogRead(uint8_t pin)
{
  _mode = 2;
  _pin = pin;
};


void DEVRANDOM::useDigitalRead(uint8_t pin)
{
  _mode = 1;
  _pin = pin;
  pinMode(_pin, INPUT);
};


void DEVRANDOM::useRandom()
{
  _mode = 0;
};


uint8_t DEVRANDOM::getMode()
{
  return _mode;
};


int DEVRANDOM::_rnd()
{
  if (_mode == 0 ) return random(256);
  if (_mode == 1 ) return _digitalRead();
  if (_mode == 2 ) return _analogRead();
  if (_mode == 3 ) return _marsaglia();
  return 0;
}


int DEVRANDOM::_digitalRead()
{
  uint8_t value = 0;
  for (uint8_t i = 0; i < 8; i++)
  {
    value <<= 1;
    if (digitalRead(_pin)) value++;
  }
  return value ^ _seed;
}


int DEVRANDOM::_analogRead()
{
  uint8_t value = 0;
  for (uint8_t i = 0; i < 8; i++)
  {
    value <<= 1;
    if (analogRead(_pin) & 1) value++;
  }
  return value ^ _seed;
}


//  An example of a simple pseudo-random number generator is the
//  Multiply-with-carry method invented by George Marsaglia.
//  two initializers (not null)
uint32_t DEVRANDOM::_marsaglia()
{
  _m_z = 36969L * (_m_z & 65535L) + (_m_z >> 16);
  _m_w = 18000L * (_m_w & 65535L) + (_m_w >> 16);
  return (_m_z << 16) + _m_w;  /* 32-bit result */
}


//  -- END OF FILE --

