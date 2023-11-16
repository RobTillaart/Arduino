#pragma once
//
//    FILE: rain.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.4
//    DATE: 2022-11-23
// PURPOSE: Arduino library for rain sensor (analog).
//     URL: https://github.com/RobTillaart/RAIN
//          https://www.tinytronics.nl/shop/nl/sensoren/vloeistof/regensensor


#include "Arduino.h"


#define RAIN_LIB_VERSION         (F("0.1.4"))


class RAIN
{
public:
  //  powerPin is optional, 255 == not used => see readme.md
  RAIN(uint8_t analogPort, uint8_t powerPin = 255);

  //  set the ADC parameters
  //  can be changed runtime, e.g if voltage fluctuates.
  bool     begin(float maxVoltage, uint16_t maxSteps);

  //  returns steps as float, e.g can be 456.33
  float    raw(uint8_t times = 1);
  //  returns voltage
  //  the lower the voltage the wetter.
  float    read(uint8_t times = 1);


  //  ANALYSIS
  //
  //  read the sensor when it is dry to get a reference (calibration).
  //  will be used by percentage(), can be used to setLevel().
  //  NOTE: dryRef is default maxVoltage parameter from begin()
  void     setDryReference(float dryRef);
  float    getDryReference();

  //  returns last read value as percentage of DryReference (if set).
  //  indicating wetness  0 == DRY   100 == WET
  //  percentage assumes / implies "linear" behaviour
  float    percentage();

  //  delta with respect to previous read().
  float    delta();


  //  LEVEL
  //
  //  level = 1..4
  //  level 0 == 0 Volt ==> WET (cannot be overruled).
  //  level 4 ==> DRY
  //  user is responsible that values are increasing voltages.
  bool     setLevel(uint8_t nr, uint16_t milliVolts);
  //  returns 0..4
  uint8_t  getLevel();


  //  POWER
  //
  //  will only work when powerPin is defined in constructor.
  void     powerOn();
  void     powerOff();
  //  for tuning the stabilization delay in powerOn(),
  //  normally not needed.
  void     setPowerDelay(uint8_t powerDelay = 100);
  uint8_t  getPowerDelay();


private:
  uint8_t  _analogPort;
  uint8_t  _powerPin      = 255;  //  255 means not set.
  uint8_t  _powerDelay    = 100;  //  default
  float    _maxVoltage;
  uint16_t _maxSteps;
  float    _mVstep        = 1;
  float    _voltage       = 0;
  float    _dryRefVoltage;
  float    _previous      = 0;
  uint16_t _level[5] = { 0, 1000, 2000, 3000, 4000 };  //  millivolts
};


//  -- END OF FILE --

