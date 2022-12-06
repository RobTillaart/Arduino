#pragma once
//
//    FILE: rain.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.2
//    DATE: 2022-11-23
// PURPOSE: Arduino library for rain sensor (analog).
//     URL: https://github.com/RobTillaart/RAIN
//          https://www.tinytronics.nl/shop/nl/sensoren/vloeistof/regensensor


#include "Arduino.h"


#define RAIN_LIB_VERSION         (F("0.1.2"))


class RAIN
{
public:
  //  port = analogPort,
  //  powerPin is optional, 255 == not used => see readme.md
  RAIN(uint8_t port, uint8_t powerPin = 255);

  //  set the ADC parameters
  //  can be changed runtime, e.g if voltage fluctuates.
  bool     begin(float maxVoltage, uint16_t maxSteps);

  //  returns steps
  float    raw(uint8_t times = 1);
  //  returns voltage
  //  the lower the voltage the wetter.
  float    read(uint8_t times = 1);


  //  ANALYSIS
  //  read the sensor when it is dry to get a reference (calibration).
  //  will be used by percentage(), can be used to setLevel().
  void     setDryReference(float dryRef);
  float    getDryReference();

  //  returns last read value as percentage of DryReference (if set).
  //  indicating wetness  0 == DRY   100 == WET
  //  percentage assumes / implies "linear" behaviour
  float    percentage();

  //  delta with respect to previous read().
  float    delta();


  //  level = 1..4
  //  level 0 == 0 Volt ==> WET)
  //  level 4 ==> DRY
  //  user is responsible that values are increasing voltages.
  bool     setLevel(uint8_t nr, uint16_t milliVolts);
  uint8_t  getLevel();

  //  will only work when set in constructor.
  void     powerOn();
  void     powerOff();


private:
  uint8_t  _port;
  uint8_t  _powerPin   = 255;  //  255 means not set.
  float    _maxVoltage;
  uint16_t _maxSteps;
  float    _mVstep;
  float    _voltage;
  float    _dryRefVoltage;
  float    _previous;
  uint16_t _level[5] = { 0, 1000, 2000, 3000, 4000 };  //  millivolts
};


//  -- END OF FILE --

