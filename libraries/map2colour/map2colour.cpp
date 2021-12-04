//
//    FILE: map2colour.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: Arduino library for mapping a float to colour spectrum
//     URL: https://github.com/RobTillaart/map2colour
//
//  HISTORY:
//  0.1.0  2021-12-04  initial version


#include "map2colour.h"


map2colour::map2colour()
{
}


bool map2colour::begin(float * values)
{
  _values = values;
  return true;
}


uint32_t map2colour::map2RGB(float value)
{
  int index = 1;
  float factor = 0;
  uint8_t R = _Red[0];
  uint8_t G = _Green[0];
  uint8_t B = _Blue[0];

  if ( (_values[0] < value) && (value <= _values[6] ))
  {
    while ((index < 7) && (_values[index] < value)) index++;
    factor = 1 - (_values[index] - value) / (_values[index] - _values[index-1]);
    R = _Red[index - 1] + factor * (_Red[index] - _Red[index - 1]);
    G = _Green[index - 1] + factor * (_Green[index] - _Green[index - 1]);
    B = _Blue[index - 1] + factor * (_Blue[index] - _Blue[index - 1]);
  }
  uint32_t colour = R;
  colour <<= 8;
  colour |= G;
  colour <<= 8;
  colour |= B;
  return colour;
}


// -- END OF FILE --

