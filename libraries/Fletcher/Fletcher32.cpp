//
//    FILE: Fletcher32.cpp
//  AUTHOR: Rob Tillaart, Daniel Mohr
// PURPOSE: Arduino class for Fletcher32
//     URL: https://github.com/RobTillaart/Fletcher


#include "Fletcher32.h"

//  UINT16_MAX = 65535UL = ((((uint32_t) 1) << 16) - 1)
#define FLETCHER_32   UINT16_MAX


Fletcher32::Fletcher32()
{
  begin();
}


void Fletcher32::begin(uint16_t s1, uint16_t s2)
{
  _s1    = (s1 == FLETCHER_32) ? 0 : s1;
  _s2    = (s2 == FLETCHER_32) ? 0 : s2;
  _count = 0;
}


void Fletcher32::add(uint16_t value)
{
  _count++;
#ifdef ARDUINO_ARCH_AVR
  unsigned int t = _s1;
  //   Serial.println("__builtin_uadd_overflow");
  if (__builtin_uadd_overflow(t, value, &t)) {
    t++;
  }
  _s1 = t;
  t = _s2;
  if (__builtin_uadd_overflow(t, _s1, &t)) {
    t++;
  }
  _s2 = t;
#elif defined(ARDUINO_ARCH_SAMD) || defined(ESP32) || defined(ESP8266)
  _s1 += value;
  _s1 = (_s1 & FLETCHER_32) + (_s1 >> 16);
  _s2 += _s1;
  _s2 = (_s2 & FLETCHER_32) + (_s2 >> 16);
#else
  _s1 += value;
  if (_s1 >= FLETCHER_32) _s1 -= FLETCHER_32;
  _s2 += _s1;
  if (_s2 >= FLETCHER_32) _s2 -= FLETCHER_32;
#endif
}

//  NOTE: padding with zero's error
//
void Fletcher32::add(const uint16_t * array, uint16_t length)
{
  while (length--)
  {
    add(*array++);
  }
}

uint32_t Fletcher32::getFletcher()
{
  if (_s1 >= FLETCHER_32) _s1 -= FLETCHER_32;
  if (_s2 >= FLETCHER_32) _s2 -= FLETCHER_32;
  return (((uint32_t)_s2) << 16) | _s1;
};


uint32_t Fletcher32::count()
{
  return _count;
};


//  -- END OF FILE --

