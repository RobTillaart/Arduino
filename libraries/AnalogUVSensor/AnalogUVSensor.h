#pragma once
//
//    FILE: AnalogUVSensor.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.6
//    DATE: 2021-09-25
// PURPOSE: Arduino library for an analogue UV sensor.
//     URL: https://github.com/RobTillaart/AnalogUVSensor


#include "Arduino.h"

#define ANALOG_UVSENSOR_LIB_VERSION        (F("0.1.6"))


class AnalogUVSensor
{
public:

  AnalogUVSensor();

  //  adjust ADC settings to your board!
  void begin(uint8_t analogPin, float volts = 5.0, uint16_t maxADC = 1023);

  float read(uint8_t times = 1);
  float mV2index(uint16_t milliVolt);  //  for external ADC
  char  index2color(float index);

  //  POWER
  void setPowerPin(uint8_t powerPin, bool invert = false);
  void switchOff();
  void switchOn();


private:
  uint8_t  _analogPin;
  float    _volts;
  uint16_t _maxADC;
  uint8_t  _powerPin;
  bool     _invert;
};


//  -- END OF FILE --

