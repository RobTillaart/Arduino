//
//    FILE: Kelvin2RGB.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.2
//    DATE: 2018-01-31
// PURPOSE: Arduino library for converting temperature to RGB values
//     URL: https://github.com/RobTillaart/Kelvin2RGB

//  HISTORY
//  0.1.0    2018-01-31  initial version
//  0.1.1    2020-12-30  ??
//  0.1.2    2021-06-01  add RGB565() - 16 bit color - output


#include "Kelvin2RGB.h"


#define DIVIDE_255      (0.0039215686274509803921568627451)


Kelvin2RGB::Kelvin2RGB()
{
  _temperature = 0;
  _brightness  = 0;          // default = darkness
  _red   = 0;
  _green = 0;
  _blue  = 0;
}


void Kelvin2RGB::begin()
{
}


// Tanner Helland formulas
void Kelvin2RGB::convert_TH(float temperature, float brightness)
{
  _temperature = constrain(temperature, 0, 65500);
  _brightness = constrain(brightness, 0, 100);

  _red = _green = _blue = 0;  
  float t = _temperature * 0.01;

  if (t <= 66)
  {
    _red = 255;
    _green = (99.4708025861 * log(t)) - 161.1195681661;
    if (t > 19)
    {
      _blue = (138.5177312231 * log(t - 10)) - 305.0447927307;
    }
    else _blue = 0;
  }
  else
  {
    _red   = 329.698727466  * pow(t - 60, -0.1332047592);
    _green = 288.1221695283 * pow(t - 60, -0.0755148492);
    _blue  = 255;
  }

  _normalize();
}


// Neil Bartlett formulas
void Kelvin2RGB::convert_NB(float temperature, float brightness)
{
  _temperature = constrain(temperature, 0, 65500);
  _brightness = constrain(brightness, 0, 100);

  _red = _green = _blue = 0;
  float t = _temperature * 0.01;

  if (t <= 66)
  {
    _red = 255;
    _green = t - 2;
    _green = -155.25485562709179 - 0.44596950469579133 * _green + 104.49216199393888 * log(_green);
    _blue = 0;
    if (t > 20)
    {
      _blue = t - 10;
      _blue = -254.76935184120902 + 0.8274096064007395 * _blue + 115.67994401066147 * log(_blue);
    }
  }
  else
  {
    _red = t - 55.0;
    _red = 351.97690566805693 + 0.114206453784165 * _red - 40.25366309332127 * log(_red);
    _green = t - 50.0;
    _green = 325.4494125711974 + 0.07943456536662342 * _green - 28.0852963507957 * log(_green);
    _blue = 255;
  }

  _normalize();
}


// 16 bit color
uint16_t Kelvin2RGB::RGB565()
{
  uint16_t val = 0;
  val  = uint8_t(_red * 32);
  val <<= 6;
  val |= uint8_t(_green * 64);
  val <<= 5;
  val |= uint8_t(_blue * 32);
  return val; 
}


/////////////////////////////////////////////////////////////
//
// private
//
void Kelvin2RGB::_normalize()
{
  float f = 0.01 * _brightness;

  _red   = constrain(f * _red,   0, 255);
  _green = constrain(f * _green, 0, 255);
  _blue  = constrain(f * _blue,  0, 255);

  _rgb   = round(_red) * 65536UL + round(_green) * 256UL + round(_blue);
  
  // divide by 255 to get factors between 0..1
  _red   *=  DIVIDE_255;
  _green *=  DIVIDE_255;
  _blue  *=  DIVIDE_255;
}


// -- END OF FILE --
