//
//    FILE: ML8511.cpp
//  AUTHOR: Rob.Tillaart@gmail.com
// VERSION: 0.1.8
// PURPOSE: ML8511 - UV sensor - library for Arduino
//
//  HISTORY:
//  0.1.0  2020-02-03  initial version
//  0.1.1  2020-02-17  added _voltPerStep() to support more boards
//  0.1.2  2020-06-21  refactor; add estimateDUVindex()
//  0.1.3  2021-01-01  Arduino-CI + unit test
//  0.1.4  2021-04-23  fix for platformIO
//  0.1.5  2021-05-27  fix Arduino-lint
//  0.1.6  2021-06-19  add get/setDUVfactor(),
//                     rewrite estimateDUVindex(),
//                     add reset();
//  0.1.7  2021-11-09  update Arduino-CI, badges
//                     add voltage2mW() for external ADC
//  0.1.8  2021-12-21  update library.json, license, minor edits


#include "ML8511.h"


/////////////////////////////////////////////////////
//
// PUBLIC
//
ML8511::ML8511(uint8_t analogPin, uint8_t enablePin)
{
  _analogPin    = analogPin;
  _enablePin    = enablePin;
  if (enablePin != 0xFF)
  {
    pinMode(_enablePin, OUTPUT);
    digitalWrite(_enablePin, LOW);
    _enabled = false;
    enable();
  }
  else
  {
    _enabled = true;
  }
  reset();
};


void ML8511::reset()
{
  _voltsPerStep = 5.0/1023;
  _DUVfactor    = 1.61;      // https://github.com/RobTillaart/ML8511/issues/4
}


float ML8511::getUV(uint8_t energyMode)
{
  if (!_enabled)
  {
    enable();
    // datasheet page 5 states wait for max 1 millisecond
    uint32_t start = micros();
    while (micros() - start < 1000) yield();
  }
  //  read the sensor
  float voltage = analogRead(_analogPin) * _voltsPerStep;
  //  go to low power mode?
  if (energyMode == LOW)
  {
    disable();
  }

  return voltage2mW(voltage);
}


//  to be used by external ADC
float ML8511::voltage2mW(float voltage)
{
  // see datasheet - page 4
  // mW/cm2 @ 365 nm
  // @ 25 Celsius
  // formula estimated on graph
  if (voltage <= 1.0)
  {
    return 0.0;
  }
  voltage -= 1.0;    // subtract for zero point.
  float mWcm2 = voltage * (15.0 / 1.8);
  return mWcm2;
}


// experimental estimate DUV index ( ==> USE WITH CARE !!)
// use setDUVfactor(float w) to calibrate
//
// input is power in mW per cm2
float ML8511::estimateDUVindex(float mWcm2)
{
  // rewrite in 0.1.6
  // https://github.com/RobTillaart/ML8511/issues/4
  return mWcm2 * _DUVfactor;
};


bool ML8511::setDUVfactor(float factor)
{
  if (factor < 0.01) return false;  // enforce positive values
  _DUVfactor = factor;
  return true;
};


void  ML8511::setVoltsPerStep(float voltage, uint32_t steps)
{
  if (steps == 0) return;
  if (voltage > 0.0) _voltsPerStep = voltage / steps;
}


void ML8511::enable()
{
  if (_enablePin != 0xFF) digitalWrite(_enablePin, HIGH);
  _enabled = true;
};


void ML8511::disable()
{
  if (_enablePin != 0xFF) digitalWrite(_enablePin, LOW);
  _enabled = false;
};


// -- END OF FILE --

