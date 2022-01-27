#pragma once
//
//    FILE: Fletcher64.h
//  AUTHOR: Rob Tillaart
// PURPOSE: Arduino class for Fletcher64
//     URL: https://github.com/RobTillaart/Fletcher


#include "Arduino.h"


class Fletcher64
{
public:
  Fletcher64();

  // set parameters to default
  void     begin(uint32_t s1 = 0, uint32_t s2 = 0);

  void     add(uint32_t value);
  void     add(const uint32_t * array, uint16_t length);

  uint64_t getFletcher() { return (_s2 << 32) | _s1; };
  uint32_t count()       { return _count; };

private:
  uint64_t _s1;
  uint64_t _s2;
  uint32_t _count;
};


// -- END OF FILE --

