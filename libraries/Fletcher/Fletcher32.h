#pragma once
//
//    FILE: Fletcher32.h
//  AUTHOR: Rob Tillaart
// PURPOSE: Arduino class for Fletcher32
//     URL: https://github.com/RobTillaart/Fletcher


#include "Arduino.h"


class Fletcher32
{
public:
  Fletcher32();

  //  set parameters to default
  void     begin(uint16_t s1 = 0, uint16_t s2 = 0);

  void     add(uint16_t value);
  void     add(const uint16_t * array, uint16_t length);

  uint32_t getFletcher();
  uint32_t count();

private:
#ifdef ARDUINO_ARCH_AVR
  uint16_t _s1;
  uint16_t _s2;
#else
  uint32_t _s1;
  uint32_t _s2;
#endif
  uint32_t _count;
};


//  -- END OF FILE --

