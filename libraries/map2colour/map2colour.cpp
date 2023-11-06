//
//    FILE: map2colour.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.1
// PURPOSE: Arduino library for mapping a float to colour spectrum
//     URL: https://github.com/RobTillaart/map2colour


#include "map2colour.h"

#define M2C_MIN_SIZE        7


map2colour::map2colour(uint8_t size)
{
  _size = size;
  if (_size < M2C_MIN_SIZE) _size = M2C_MIN_SIZE;

  _Red   = (uint8_t *)malloc(_size);
  _Green = (uint8_t *)malloc(_size);
  _Blue  = (uint8_t *)malloc(_size);

  // for backwards compatibility
  uint8_t r[7] = { 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0xFF };
  uint8_t g[7] = { 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xFF };
  uint8_t b[7] = { 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF };

  memcpy(_Red,   r, 7);
  memcpy(_Green, g, 7);
  memcpy(_Blue,  b, 7);
}


map2colour::~map2colour()
{
  if (_Red)   free(_Red);
  if (_Green) free(_Green);
  if (_Blue)  free(_Blue);
}


bool map2colour::begin(float * values, uint32_t * colourMap)
{
  if ((_Red == NULL) || (_Green == NULL) || (_Blue == NULL))
  {
    //  need error codes?
    return false;
  }
  //  split colour map in channels to allow interpolation per channel
  if (colourMap != NULL)
  {
    for (int i = 0; i < _size; i++)
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
  for (int index = 1; index < _size; index++)
  {
    float den = _values[index] - _values[index - 1];
    if (den < 0.0) return false;
  }
  return true;
}


uint8_t map2colour::size()
{
  return _size;
}


uint32_t map2colour::map2RGB(float value)
{
  uint8_t index = 1;
  //  default values + out of lower range
  uint8_t R = _Red[0];
  uint8_t G = _Green[0];
  uint8_t B = _Blue[0];

  if (_values[0] < value)
  {
    if (value < _values[_size-1] )
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
      R = _Red[_size-1];
      G = _Green[_size-1];
      B = _Blue[_size-1];
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
  colour |= (RGB & 0x001F);  //  B channel 5 bits
  RGB >>= 2;
  colour |= (RGB & 0x07E0);  //  G channel 6 bits
  RGB >>= 3;
  colour |= (RGB & 0xF800);  //  R channel 5 bits
  return colour;
}


/////////////////////////////////////////////////////////////////////////
//
//  DERIVED CLASS
//
map2colourFast::map2colourFast(uint8_t size) : map2colour(size)
{
  divFactor = (float *) malloc(size * sizeof(float));
}


map2colourFast::~map2colourFast()
{
  if (divFactor) free(divFactor);
}



bool map2colourFast::begin(float * values, uint32_t * colourMap)
{
  //  load the colour-map and check non-decreasing order.
  bool OK = map2colour::begin(values, colourMap);
  //  pre-calculate dividers
  for (int index = 1; index < _size; index++)
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
    if (value < _values[_size-1] )
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
      //  out of upper range
      R = _Red[_size-1];
      G = _Green[_size-1];
      B = _Blue[_size-1];
    }
  }
  uint32_t colour = R;
  colour <<= 8;
  colour |= G;
  colour <<= 8;
  colour |= B;
  return colour;
}


//  could be slightly faster (~0.4 us) for AVR by
//  - split of R = RGB >> 16   (one third could be 16 bit math.
uint16_t map2colourFast::map2_565(float value)
{
  uint32_t RGB = map2RGB(value);
  uint16_t colour = 0x0000;
  RGB >>= 3;
  colour |= (RGB & 0x001F);  //  B channel 5 bits
  RGB >>= 2;
  colour |= (RGB & 0x07E0);  //  G channel 6 bits
  RGB >>= 3;
  colour |= (RGB & 0xF800);  //  R channel 5 bits
  return colour;
}


//  -- END OF FILE --

