#pragma once
//
//    FILE: ML8511.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.6
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

#define ML8511_LIB_VERSION            (F("0.1.6"))


class ML8511
{
public:
  // if enablePin is omitted, one must connect EN to 3V3.
  ML8511(uint8_t analogPin, uint8_t enablePin = 0xFF);

  void reset();  // reset internal vars to initial value.

  // energyMode = HIGH or LOW;
  // returns mW per cm2
  float    getUV(uint8_t energyMode = HIGH);

  // voltage must be > 0 otherwise it is not set
  void     setVoltsPerStep(float voltage, uint32_t steps);
  float    getVoltsPerStep() { return _voltsPerStep; };

  // manually enable / disable
  void     enable();
  void     disable();
  bool     isEnabled() { return _enabled; };


  // experimental estimate DUV index
  // WARNING: USE WITH CARE
  //
  // input in mW per cm2    == typical the output of getUV()
  float    estimateDUVindex(float mWcm2);
  //
  // https://github.com/RobTillaart/ML8511/issues/4
  // discusses the calibration 
  // see readme.md how to reverse engineer the factor for 
  // the estimateDUVindex() conversion function.
  // a value of 1.61 was found to be far more accurate
  //
  // returns false  if f < 0.01 (to force positive only)
  bool     setDUVfactor(float f);
  float    getDUVfactor()        { return _DUVfactor; };


private:
  uint8_t  _analogPin;
  uint8_t  _enablePin;
  float    _voltsPerStep;
  bool     _enabled;


  float    _DUVfactor;
};


// -- END OF FILE --
