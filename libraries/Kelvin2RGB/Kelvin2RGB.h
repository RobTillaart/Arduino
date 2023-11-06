#pragma once
//
//    FILE: Kelvin2RGB.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.7
//    DATE: 2018-01-31
// PURPOSE: Arduino library for converting temperature to RGB values
//     URL: https://github.com/RobTillaart/Kelvin2RGB


#define KELVIN2RGB_LIB_VERSION            (F("0.1.7"))

#include "Arduino.h"


//
//  Based upon article Tanner Helland  and Neil Bartlett
//  http://www.tannerhelland.com/4435/convert-temperature-rgb-algorithm-code/
//  http://www.zombieprototypes.com/?p=210
//  https://en.wikipedia.org/wiki/Color_temperature#Categorizing_different_lighting
//
//
//  based on https://en.wikipedia.org/wiki/Color_temperature#Categorizing_different_lighting
//
//      DAY LIGHT SETTING      TEMPERATURE
//
#define DLS_dark                     0
#define DLS_match                 1700
#define DLS_sodiumLamp            1700
#define DLS_candleFlame           1850
#define DLS_sunrise               1850
#define DLS_sunset                1850
#define DLS_bulb                  2400
#define DLS_bulbSoftWhite         2550
#define DLS_LEDlamp               2700
#define DLS_warmWhite             3000
#define DLS_studioLight           3200
#define DLS_studioCPlight         3350
#define DLS_daylightHorizon       5000
#define DLS_flashLight            5700
#define DLS_xenonLight            6200
#define DLS_dayLightBright        6500
#define DLS_normal                6500
#define DLS_screenlow             6500
#define DLS_screenMed             8000
#define DLS_screenHigh            9500
#define DLS_polewardSky0         15000
#define DLS_polewardSky1         19000
#define DLS_polewardSky2         23000
#define DLS_polewardSky3         27000


class Kelvin2RGB
{
public:
  Kelvin2RGB();

  //  resets all variables to zero.
  void begin();
  [[deprecated("Use begin() instead")]]
  void reset() { begin(); };  // obsolete soon

  //  temperature = 0..65500   brightness = 0.0 .. 100.0%
  void convert_TH(float temperature, float brightness = 100.0);
  void convert_NB(float temperature, float brightness = 100.0);

  float    temperature();
  float    brightness();;

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

  //  Experimental 0.1.3
  uint32_t CMYK();
  uint32_t BGR();


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

