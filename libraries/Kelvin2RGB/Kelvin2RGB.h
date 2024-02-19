#pragma once
//
//    FILE: Kelvin2RGB.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.0
//    DATE: 2018-01-31
// PURPOSE: Arduino library for converting temperature to RGB values
//     URL: https://github.com/RobTillaart/Kelvin2RGB


#define KELVIN2RGB_LIB_VERSION            (F("0.2.0"))

#include "Arduino.h"


//  Library based upon article Tanner Helland and Neil Bartlett
//  http://www.tannerhelland.com/4435/convert-temperature-rgb-algorithm-code/
//  https://en.wikipedia.org/wiki/Color_temperature#Categorizing_different_lighting



//  Values in table below based on 
//  https://en.wikipedia.org/wiki/Color_temperature#Categorizing_different_lighting
//
//             DAY LIGHT SETTING   = TEMPERATURE
//
const uint16_t DLS_dark            =     0;
const uint16_t DLS_match           =  1700;
const uint16_t DLS_sodiumLamp      =  1700;
const uint16_t DLS_candleFlame     =  1850;
const uint16_t DLS_sunrise         =  1850;
const uint16_t DLS_sunset          =  1850;
const uint16_t DLS_bulb            =  2400;
const uint16_t DLS_bulbSoftWhite   =  2550;
const uint16_t DLS_LEDlamp         =  2700;
const uint16_t DLS_warmWhite       =  3000;
const uint16_t DLS_studioLight     =  3200;
const uint16_t DLS_studioCPlight   =  3350;
const uint16_t DLS_daylightHorizon =  5000;
const uint16_t DLS_flashLight      =  5700;
const uint16_t DLS_xenonLight      =  6200;
const uint16_t DLS_dayLightBright  =  6500;
const uint16_t DLS_normal          =  6500;
const uint16_t DLS_screenLow       =  6500;
const uint16_t DLS_screenMed       =  8000;
const uint16_t DLS_screenHigh      =  9500;
const uint16_t DLS_polewardSky0    = 15000;
const uint16_t DLS_polewardSky1    = 19000;
const uint16_t DLS_polewardSky2    = 23000;
const uint16_t DLS_polewardSky3    = 27000;


class Kelvin2RGB
{
public:
  Kelvin2RGB();

  //  resets all variables to zero.
  void begin();
  [[deprecated("Use begin() instead")]]
  void reset() { begin(); };  //  obsolete 0.3.0

  //  temperature = 0..65500   brightness = 0.0 .. 100.0%
  void convert_TH(float temperature, float brightness = 100.0);
  void convert_NB(float temperature, float brightness = 100.0);

  float    temperature();
  float    brightness();

  //  returns 0.0 .. 1.0
  float    red();
  float    green();
  float    blue();

  //  red, green, blue should be in 0 .. 1.0 range
  //  brightness should be in 0..100%,  Default = 100%,
  //  returns RGB.
  uint32_t setRGB(float red, float green, float blue, float brightness = 100.0);

  uint32_t RGB();       //  32 bit colour  (only 3 bytes used)
  uint16_t RGB565();    //  16 bit colour  (2 bytes)
  uint32_t BGR();
  uint32_t CMYK();


private:
  void     _normalize();

  float    _temperature = 0;
  float    _brightness  = 0;
  float    _red   = 0;
  float    _green = 0;
  float    _blue  = 0;
  uint32_t _rgb   = 0;
};


//  -- END OF FILE --

