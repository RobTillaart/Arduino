//
//    FILE: map2colour.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.5
// PURPOSE: Arduino library for mapping a float to colour spectrum
//     URL: https://github.com/RobTillaart/map2colour
//
//  HISTORY see changelog.md


#include "map2colour.h"


map2colour::map2colour()
{
}


bool map2colour::begin(float * values, uint32_t * colourMap)
{
  //  split colour map in channels
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
  _values = values;
  for (int index = 1; index < 7; index++)
  {
    //  catch non increasing values.
    float den = _values[index] - _values[index - 1];
    if (den <= 0.0) return false;
  }
  return true;
}


uint32_t map2colour::map2RGB(float value)
{
  int index = 1;
  //  default values + out of lower range
  uint8_t R = _Red[0];
  uint8_t G = _Green[0];
  uint8_t B = _Blue[0];

  if (_values[0] < value)
  {
    if (value <= _values[6] )
    {
      //  search the interval
      while (_values[index] < value) index++;

      //  base value
      R = _Red[index];
      G = _Green[index];
      B = _Blue[index];
      //  calculate the interpolation factor
      //  map2colourFast uses pre calculated dividers (costs 24 bytes extra RAM).
      float factor = (_values[index] - value) / (_values[index] - _values[index - 1]);

      //  interpolate only if delta != 0
      int delta = _Red[index] - _Red[index - 1];
      if (delta != 0 ) R -= factor * delta;

      delta = _Green[index] - _Green[index - 1];
      if (delta != 0 ) G -= factor * delta;

      delta = _Blue[index] - _Blue[index - 1];
      if (delta != 0 ) B -= factor * delta;
    }
    else
    {
      // out of upper range
      R = _Red[6];
      G = _Green[6];
      B = _Blue[6];
    }
  }
  uint32_t colour = R;
  colour <<= 8;
  colour |= G;
  colour <<= 8;
  colour |= B;
  return colour;
}


uint16_t map2colour::map2_565(float value)
{
  uint32_t RGB = map2RGB(value);
  uint16_t colour = 0x0000;
  RGB >>= 3;
  colour |= (RGB & 0x001F);  // B channel 5 bits
  RGB >>= 2;
  colour |= (RGB & 0x07E0);  // G channel 6 bits
  RGB >>= 3;
  colour |= (RGB & 0xF800);  // R channel 5 bits
  return colour;
}


/////////////////////////////////////////////////////////////////////////
//
// DERIVED CLASS
//

map2colourFast::map2colourFast() : map2colour()
{
}


bool map2colourFast::begin(float * values, uint32_t * colourMap)
{
  //  load the colour-map and check non-decreasing order.
  bool OK = map2colour::begin(values, colourMap);
  //  pre-calculate dividers
  for (int index = 1; index < 7; index++)
  {
    float divider = _values[index] - _values[index - 1];
    if (divider > 0)
    {
      divFactor[index - 1] = 1.0 / divider;
    }
    else
    {
      divFactor[index - 1] = 0;
    }
  }
  return OK;
}


uint32_t map2colourFast::map2RGB(float value)
{
  int index = 1;
  //  default values + out of lower range
  uint8_t R = _Red[0];
  uint8_t G = _Green[0];
  uint8_t B = _Blue[0];

  if (_values[0] < value)
  {
    if (value <= _values[6] )
    {
      //  search the interval
      while (_values[index] < value) index++;

      //  base value
      R = _Red[index];
      G = _Green[index];
      B = _Blue[index];
      //  calculate the interpolation factor
      float factor = (_values[index] - value) * divFactor[index - 1];

      //  interpolate if delta <> 0
      int delta = _Red[index] - _Red[index - 1];
      if (delta != 0 ) R -= factor * delta;

      delta = _Green[index] - _Green[index - 1];
      if (delta != 0 ) G -= factor * delta;

      delta = _Blue[index] - _Blue[index - 1];
      if (delta != 0 ) B -= factor * delta;
    }
    else
    {
      // out of upper range
      R = _Red[6];
      G = _Green[6];
      B = _Blue[6];
    }
  }
  uint32_t colour = R;
  colour <<= 8;
  colour |= G;
  colour <<= 8;
  colour |= B;
  return colour;
}


uint16_t map2colourFast::map2_565(float value)
{
  uint32_t RGB = map2RGB(value);
  uint16_t colour = 0x0000;
  RGB >>= 3;
  colour |= (RGB & 0x001F);  // B channel 5 bits
  RGB >>= 2;
  colour |= (RGB & 0x07E0);  // G channel 6 bits
  RGB >>= 3;
  colour |= (RGB & 0xF800);  // R channel 5 bits
  return colour;
}


// -- END OF FILE --

