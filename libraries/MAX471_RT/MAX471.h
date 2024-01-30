#pragma once
//
//    FILE: MAX471.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
//    DATE: 2024-01-30
// PURPOSE: Arduino library for MAX471 current sensor.
//     URL: https://github.com/RobTillaart/MAX471_RT



#include "Arduino.h"

#define MAX471_LIB_VERSION        (F("0.1.1"))


class MAX471
{
public:
  //  red board
  MAX471(uint8_t currentPin, uint8_t voltagePin);
  //  purple board
  MAX471(uint8_t currentPin, uint8_t voltagePin, uint8_t signPin);

  //  ADC parameters, defaults 10 bit 5V (UNO)
  //  assumes both ADC are equal.
  void      begin(float maxVoltage = 5, uint16_t maxSteps = 1023);

  float     readCurrent(uint8_t times = 1);
  float     readCurrentMilliAmpere(uint8_t times = 1);
  float     readVoltage(uint8_t times = 1);
  float     readVoltageMilliVolts(uint8_t times = 1);
  float     calcPower();
  float     calcPowerMilliWatt();


protected:
  uint8_t  _currentPin;
  uint8_t  _voltagePin;
  uint8_t  _signPin;
  float    _current;
  float    _voltage;
  float    _units;
};


//  -- END OF FILE --

