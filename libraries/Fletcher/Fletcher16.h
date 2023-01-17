#pragma once
//
//    FILE: Fletcher16.h
//  AUTHOR: Rob Tillaart, Daniel Mohr
// PURPOSE: Arduino class for Fletcher16
//     URL: https://github.com/RobTillaart/Fletcher


#include "Arduino.h"


class Fletcher16
{
public:
  Fletcher16();

  //  set parameters to default
  void     begin(uint8_t s1 = 0, uint8_t s2 = 0);

  void     add(uint8_t value);
  void     add(const uint8_t * array, uint16_t length);

  uint16_t getFletcher();
  uint32_t count();

private:
#ifdef ARDUINO_ARCH_AVR
  uint8_t _s1;
  uint8_t _s2;
#else
  uint16_t _s1;
  uint16_t _s2;
#endif
  uint32_t _count;
};


//  -- END OF FILE --

