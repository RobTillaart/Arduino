//
//    FILE: Fletcher64.cpp
//  AUTHOR: Rob Tillaart
// PURPOSE: Arduino class for Fletcher32
//     URL: https://github.com/RobTillaart/Fletcher


#include "Fletcher64.h"

//  UINT32_MAX = 4294967295ULL = ((((uint64_t) 1) << 32) - 1)
#define FLETCHER_64   UINT32_MAX

Fletcher64::Fletcher64()
{
  begin();
}


void Fletcher64::begin(uint32_t s1, uint32_t s2)
{
  _s1    = (s1 == FLETCHER_64) ? 0 : s1;
  _s2    = (s2 == FLETCHER_64) ? 0 : s2;
  _count = 0;
}


void Fletcher64::add(uint32_t value)
{
  _count++;
#if defined(ARDUINO_ARCH_AVR)  || defined(ESP32) || defined(ESP8266)
  uint32_t t = 0xFFFFFFFF - value;
  if (t >= _s1) _s1 += value;
  else _s1 = _s1 + value + 1;
  
  t = 0xFFFFFFFF - _s1;
  if (t >= _s2) _s2 += _s1;
  else _s2 = _s2 + _s1 + 1;
#elif defined(ARDUINO_ARCH_SAMD)
  _s1 += value;
  _s1 = (_s1 & FLETCHER_64) + (_s1 >> 32);
  _s2 += _s1;
  _s2 = (_s2 & FLETCHER_64) + (_s2 >> 32);
#else
  _s1 += value;
  if (_s1 >= FLETCHER_64) _s1 -= FLETCHER_64;
  _s2 += _s1;
  if (_s2 >= FLETCHER_64) _s2 -= FLETCHER_64;
#endif
}


void Fletcher64::add(const uint32_t * array, uint16_t length)
{
  while (length--)
  {
    add(*array++);
  }
}


uint64_t Fletcher64::getFletcher() 
{
  if (_s1 >= FLETCHER_64) _s1 -= FLETCHER_64;
  if (_s2 >= FLETCHER_64) _s2 -= FLETCHER_64;
  return (((uint64_t)_s2) << 32) | _s1;
};


uint32_t Fletcher64::count()
{
  return _count;
};


//  -- END OF FILE --

