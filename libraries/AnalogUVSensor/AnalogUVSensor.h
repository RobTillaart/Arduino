#pragma once
//
//    FILE: AnalogUVSensor.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
//    DATE: 2021-09-25
// PURPOSE: AnalogUVSensor library
//
// library for analogue UV sensor
//


#include "Arduino.h"

#define ANALOG_UVSENSOR_LIB_VERSION        (F("0.1.1"))


class AnalogUVSensor
{
public:

  AnalogUVSensor();

  void begin(uint8_t analogPin, float volts = 5.0, uint16_t maxADC = 1023);

  float read(uint8_t times = 1);
  float mV2index(uint16_t milliVolt);
  char  index2color(float index);

  //  POWER
  void setPowerPin(uint8_t powerPin, bool invert = false);
  void switchOff() { digitalWrite(_powerPin, _invert ? HIGH : LOW); };
  void switchOn()  { digitalWrite(_powerPin, _invert ? LOW : HIGH); };


private:
  uint8_t  _analogPin;
  float    _volts;
  uint16_t _maxADC;
  uint8_t  _powerPin;
  bool     _invert;
};


// -- END OF FILE --
