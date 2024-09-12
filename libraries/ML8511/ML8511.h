#pragma once
//
//    FILE: ML8511.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.0
//    DATE: 2020-02-03
// PURPOSE: ML8511 - UV sensor - library for Arduino
//     URL: https://github.com/RobTillaart/ML8511
//
//  NOTES
//    ML8511 is a 3.3 Volt device,
//    so do not connect to a 5V device (e.g. UNO)
//    this includes the ENABLE PIN !!
//
//        +-------+--+
//    VIN |o      +-+| mounting hole
//    3V3 |o      +-+|
//    GND |o         |
//    OUT |o         |
//     EN |o       S |  Sensor
//        +----------+


#include <Arduino.h>

#define ML8511_LIB_VERSION            (F("0.2.0"))


class ML8511
{
public:
  //  if enablePin is omitted, one must connect EN to 3V3.
  ML8511(uint8_t analogPin, uint8_t enablePin = 0xFF);

  void  reset();  //  reset internal variables to initial value.

  //  energyMode = HIGH or LOW;
  //  returns mW per cm2
  float getUV(uint8_t energyMode = HIGH);

  //  for external ADC
  //  voltage must be >= 1.0 otherwise 0 is returned.
  //  returns mW per cm2
  float voltage2mW(float voltage);

  //  voltage and steps must both be > 0 otherwise voltagePerStep
  //  is not set and the function returns false.
  bool  setVoltsPerStep(float voltage, uint32_t steps);
  float getVoltsPerStep();

  //  manually enable / disable the sensor
  //  if enable pin is not set, device is always enabled.
  bool  enable();   //  returns false if enable pin not set.
  bool  disable();  //  returns false if enable pin not set.
  bool  isEnabled();


  //  EXPERIMENTAL: estimate DUV index
  //  WARNING: USE WITH CARE
  //
  //  input in mW per cm2 == typical the output of getUV()
  float estimateDUVindex(float mWcm2);

  //  https://github.com/RobTillaart/ML8511/issues/4
  //  discusses the calibration
  //  see readme.md how to reverse engineer the factor for
  //  the estimateDUVindex() conversion function.
  //  a value of 1.61 was found to be far more accurate
  //
  //  returns false  if f < 0.01 (to force positive factor only)
  bool  setDUVfactor(float factor);
  float getDUVfactor();


private:
  uint8_t _analogPin;
  uint8_t _enablePin;
  float   _voltsPerStep;
  bool    _enabled;

  float   _DUVfactor;
};


//  -- END OF FILE --

