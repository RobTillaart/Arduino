#pragma once
//
//    FILE: Kelvin2RGB.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
//    DATE: 2018-01-31
// PURPOSE: Arduino library for converting temperature to RGB values
//     URL: https://github.com/RobTillaart/Kelvin2RGB
//
// Based upon article Tanner Helland  and Neil Bartlett
// http://www.tannerhelland.com/4435/convert-temperature-rgb-algorithm-code/
// http://www.zombieprototypes.com/?p=210  
// https://en.wikipedia.org/wiki/Color_temperature#Categorizing_different_lighting

#define KELVIN2RGB_LIB_VERSION "0.1.1"

#include "Arduino.h"

// based on https://en.wikipedia.org/wiki/Color_temperature#Categorizing_different_lighting
// TODO a memory efficient storage -> uint8_t 17 .. 255 (factor 100)
//      how? hash function? parameter settings  convert(dayLightSetting)
// enum DLS ?

/*
    NAME              TEMPERATURE
    =============================
    dark            = 0;
    match           = 1700;
    sodiumLamp      = 1700;
    candleFlame     = 1850;
    sunrise         = 1850;
    sunset          = 1850;
    bulb            = 2400;
    bulbSoftWhite   = 2550;
    LEDlamp         = 2700;
    warmWhite       = 3000;
    studioLight     = 3200;
    studioCPlight   = 3350;
    daylightHorizon = 5000;
    flashLight      = 5700;
    xenonLight      = 6200;
    dayLightBright  = 6500;
    normal          = 6500;
    screenlow       = 6500;
    screenMed       = 8000;
    screenHigh      = 9500;
    polewardSky0    = 15000;
    polewardSky1    = 19000;
    polewardSky2    = 23000;
    polewardSky3    = 27000;
*/

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
  void begin();
  
  // temp = 0..65500   brightness = 0.0 .. 100.0%
  void convert_TH(float temperature, float brightness = 100);
  void convert_NB(float temperature, float brightness = 100);

  float    temperature() { return _temperature; };
  float    brightness()  { return _brightness;  };
  inline float red()     { return _red;   };
  inline float green()   { return _green; };
  inline float blue()    { return _blue;  };
  uint32_t RGB()         { return _rgb; }

  
private:
  float    _temperature;
  float    _brightness;
  float    _red;
  float    _green;
  float    _blue;
  uint32_t _rgb;
};

// -- END OF FILE --
