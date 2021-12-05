//
//    FILE: map2colour.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
// PURPOSE: Arduino library for mapping a float to colour spectrum
//     URL: https://github.com/RobTillaart/map2colour
//
//  HISTORY:
//  0.1.0  2021-12-04  initial version
//  0.1.1  2021-12-05  add user defined colour-map
//                     add unit tests, update readme.md

#include "map2colour.h"


map2colour::map2colour()
{
}


bool map2colour::begin(float * values, uint32_t * colourMap)
{
  _values = values;
  if (colourMap != NULL)
  {
    for (int i = 0; i < 7; i++)
    {
      uint32_t val = colourMap[i];
      _Blue[i]  = val & 0xFF;
      val >>= 8;
      _Green[i] = val & 0xFF;
      val >>= 8;
      _Red[i]   = val & 0xFF;
    }
  }
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

