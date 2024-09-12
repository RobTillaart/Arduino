//
//    FILE: ML8511.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.0
//    DATE: 2020-02-03
// PURPOSE: ML8511 - UV sensor - library for Arduino
//     URL: https://github.com/RobTillaart/ML8511


#include "ML8511.h"


/////////////////////////////////////////////////////
//
//  PUBLIC
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
  _voltsPerStep = 5.0 / 1023.0;
  _DUVfactor    = 1.61;      //  https://github.com/RobTillaart/ML8511/issues/4
}


float ML8511::getUV(uint8_t energyMode)
{
  if (!_enabled)
  {
    enable();
    //  datasheet page 5 states wait for max 1 millisecond
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


//  can be used by external ADC
float ML8511::voltage2mW(float voltage)
{
  //  see datasheet - page 4
  //  mW/cm2 @ 365 nm
  //  @ 25 Celsius
  //  formula estimated from graph
  if (voltage <= 1.0)
  {
    return 0.0;
  }
  voltage -= 1.0;    // subtract for zero point.
  float mWcm2 = voltage * (15.0 / 1.8);
  return mWcm2;
}


bool ML8511::setVoltsPerStep(float voltage, uint32_t steps)
{
  if (steps == 0) return false;
  if (voltage <= 0.0) return false;
  _voltsPerStep = voltage / steps;
  return true;
}


float ML8511::getVoltsPerStep()
{
  return _voltsPerStep;
}


bool ML8511::enable()
{
  if (_enablePin == 0xFF) return false;
  digitalWrite(_enablePin, HIGH);
  _enabled = true;
  return true;
}


bool ML8511::disable()
{
  if (_enablePin == 0xFF) return false;
  digitalWrite(_enablePin, LOW);
  _enabled = false;
  return true;
}


bool ML8511::isEnabled()
{
  return _enabled;
}



//  experimental estimate DUV index ( ==> USE WITH CARE !!)
//  use setDUVfactor(float w) to calibrate
//
//  input is power in mW per cm2
float ML8511::estimateDUVindex(float mWcm2)
{
  //  rewrite in 0.1.6
  //  https://github.com/RobTillaart/ML8511/issues/4
  if (mWcm2 <= 0.0) return 0.0;
  return mWcm2 * _DUVfactor;
}


bool ML8511::setDUVfactor(float factor)
{
  if (factor < 0.01) return false;  //  enforce positive values
  _DUVfactor = factor;
  return true;
}


float ML8511::getDUVfactor()
{
  return _DUVfactor;
}


//  -- END OF FILE --

