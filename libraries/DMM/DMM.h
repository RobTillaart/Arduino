#pragma once
//
//    FILE: DMM.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.3
//    DATE: 2022-12-19
// PURPOSE: Library for a DMM class for Arduino.
//     URL: https://github.com/RobTillaart/DMM


#include "Arduino.h"

#define DMM_LIB_VERSION        (F("0.1.3"))


class DMM
{
public:
  DMM();

  void begin(uint8_t pin, float maxVoltage, uint16_t maxSteps);


  //  CALIBRATION
  void  setMaxVoltage(float maxVoltage);
  float getMaxVoltage();


  //  GAIN e.g. due to voltage divider
  //  a 25V to 5V divider has a factor = 5.
  void  setGain(float factor = 1.0);
  float getGain();


  //  READ VOLTAGE
  float readVolts(uint8_t times = 1);
  float readMilliVolts(uint8_t times = 1);
  float readNoise(uint8_t times = 1);


  //  READ OHM
  void  setReferenceR(float ohm);
  float readOhm(uint8_t times = 1);
  float readKiloOhm(uint8_t times = 1); 


private:
  uint8_t  _pin         = 14;  //  A0;
  float    _maxVoltage  = 5.0;
  uint16_t _maxSteps    = 1023;
  float    _voltageStep = _maxVoltage/_maxSteps;

  float    _gain        = 1.0;
  
  float    _ReferenceR  = 0;
};


//  -- END OF FILE --

