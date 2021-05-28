#pragma once
//
//    FILE: ML8511.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.5
// PURPOSE: ML8511 - UV sensor - library for Arduino
//     URL: https://github.com/RobTillaart/ML8511
//
// HISTORY:
// see ML8511.cpp file
//
// NOTES
//   ML8511 is a 3.3 Volt device, 
//   so do not connect to a 5V device (e.g. UNO)
//   this includes the ENABLE PIN !!
//


#include <Arduino.h>

#define ML8511_LIB_VERSION (F("0.1.5"))


class ML8511
{
public:
  // if enablePin is omitted, one must connect EN to 3V3.
  ML8511(uint8_t analogPin, uint8_t enablePin = 0xFF);

  // energyMode = HIGH or LOW;
  // returns mW per cm2
  float    getUV(uint8_t energyMode = HIGH);

  // experimental estimate DUV index  (not calibrated, USE WITH CARE !!)
  // input in mW per cm2
  float    estimateDUVindex(float mWcm2);

  // voltage must be > 0 otherwise it is not set
  void     setVoltsPerStep(float voltage, uint32_t steps);
  float    getVoltsPerStep() { return _voltsPerStep; };

  // manually enable / disable
  void     enable();
  void     disable();
  bool     isEnabled() { return _enabled; };

private:
  uint8_t  _analogPin;
  uint8_t  _enablePin;
  float    _voltsPerStep;
  bool     _enabled;
};


// -- END OF FILE --
