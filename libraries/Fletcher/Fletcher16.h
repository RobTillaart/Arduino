#pragma once
//
//    FILE: Fletcher16.h
//  AUTHOR: Rob Tillaart
// PURPOSE: Arduino class for Fletcher16
//     URL: https://github.com/RobTillaart/Fletcher


#include "Arduino.h"


class Fletcher16
{
public:
  Fletcher16();

  // set parameters to default
  void     begin(uint8_t s1 = 0, uint8_t s2 = 0);

  void     add(uint8_t value);
  void     add(const uint8_t * array, uint16_t length);

  uint16_t getFletcher() { return (_s2 << 8) | _s1; };
  uint32_t count()       { return _count; };

private:
  uint16_t _s1;
  uint16_t _s2;
  uint32_t _count;
};


// -- END OF FILE --

