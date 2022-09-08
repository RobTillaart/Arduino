//
//    FILE: Fletcher16.cpp
//  AUTHOR: Rob Tillaart
// PURPOSE: Arduino class for Fletcher16
//     URL: https://github.com/RobTillaart/Fletcher


#include "Fletcher16.h"

#define FLETCHER_16                       255


Fletcher16::Fletcher16()
{
  begin();
}


void Fletcher16::begin(uint8_t s1, uint8_t s2)
{
  _s1    = s1;
  _s2    = s2;
  _count = 0;
}


void Fletcher16::add(uint8_t value)
{
  _count++;
  _s1 += value;
  _s1 = (_s1 & 255) + (_s1 >> 8);
  _s2 += _s1;
  _s2 = (_s2 & 255) + (_s2 >> 8);
}


void Fletcher16::add(const uint8_t * array, uint16_t length)
{
  while (length--)
  {
    add(*array++);
  }
}


// -- END OF FILE --

