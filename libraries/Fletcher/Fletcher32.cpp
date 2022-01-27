//
//    FILE: Fletcher32.cpp
//  AUTHOR: Rob Tillaart
// PURPOSE: Arduino class for Fletcher32
//     URL: https://github.com/RobTillaart/Fletcher


#include "Fletcher32.h"

#define FLETCHER_32                       65535UL



Fletcher32::Fletcher32()
{
  begin();
}


void Fletcher32::begin(uint16_t s1, uint16_t s2)
{
  _s1    = s1;
  _s2    = s2;
  _count = 0;
}


void Fletcher32::add(uint16_t value)
{
  _count++;
  _s1 += value;
   if (_s1 >= FLETCHER_32) _s1 -= FLETCHER_32;
  _s2 += _s1;
   if (_s2 >= FLETCHER_32) _s2 -= FLETCHER_32;
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


// -- END OF FILE --

