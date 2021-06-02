#pragma once
//
//    FILE: Kelvin2RGB.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.2
//    DATE: 2018-01-31
// PURPOSE: Arduino library for converting temperature to RGB values
//     URL: https://github.com/RobTillaart/Kelvin2RGB
//


#define KELVIN2RGB_LIB_VERSION        (F("0.1.2"))

#include "Arduino.h"


//
// Based upon article Tanner Helland  and Neil Bartlett
// http://www.tannerhelland.com/4435/convert-temperature-rgb-algorithm-code/
// http://www.zombieprototypes.com/?p=210  
// https://en.wikipedia.org/wiki/Color_temperature#Categorizing_different_lighting
//
//
// based on https://en.wikipedia.org/wiki/Color_temperature#Categorizing_different_lighting
//
//      DAY LIGHT SETTING      TEMPERATURE
//
#define DLS_dark                  0
#define DLS_match              1700
#define DLS_sodiumLamp         1700
#define DLS_candleFlame        1850
#define DLS_sunrise            1850
#define DLS_sunset             1850
#define DLS_bulb               2400
#define DLS_bulbSoftWhite      2550
#define DLS_LEDlamp            2700
#define DLS_warmWhite          3000
#define DLS_studioLight        3200
#define DLS_studioCPlight      3350
#define DLS_daylightHorizon    5000
#define DLS_flashLight         5700
#define DLS_xenonLight         6200
#define DLS_dayLightBright     6500
#define DLS_normal             6500
#define DLS_screenlow          6500
#define DLS_screenMed          8000
#define DLS_screenHigh         9500
#define DLS_polewardSky0      15000
#define DLS_polewardSky1      19000
#define DLS_polewardSky2      23000
#define DLS_polewardSky3      27000



class Kelvin2RGB
{
public:
  Kelvin2RGB();
  void begin();         // empty function - obsolete?
  
  // temp = 0..65500   brightness = 0.0 .. 100.0%
  void convert_TH(float temperature, float brightness = 100);
  void convert_NB(float temperature, float brightness = 100);

  float    temperature() { return _temperature; };
  float    brightness()  { return _brightness;  };

  // returns 0.0 .. 1.0
  float    red()         { return _red;   };
  float    green()       { return _green; };
  float    blue()        { return _blue;  };

  uint32_t RGB()         { return _rgb; };   // 32 bit color
  uint16_t RGB565();                         // 16 bit color

private:
  void  _normalize();

  float    _temperature;
  float    _brightness;
  float    _red;
  float    _green;
  float    _blue;
  uint32_t _rgb;
};

// -- END OF FILE --
