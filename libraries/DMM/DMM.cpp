//
//    FILE: DMM.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.3
//    DATE: 2022-12-19
// PURPOSE: Library for a DMM class for Arduino UNO.
//     URL: https://github.com/RobTillaart/DMM


#include "DMM.h"


DMM::DMM()
{
}


void DMM::begin(uint8_t pin, float maxVoltage, uint16_t maxSteps)
{
  _pin         = pin;
  _maxVoltage  = maxVoltage;
  _maxSteps    = maxSteps;
  _voltageStep = _maxVoltage/_maxSteps;
}


void DMM::setMaxVoltage(float maxVoltage)
{
  _maxVoltage  = maxVoltage;
  _voltageStep = _maxVoltage/_maxSteps;
}


float DMM::getMaxVoltage()
{
  return _maxVoltage;
}


void  DMM::setGain(float factor)
{
  _gain = factor;
}


float DMM::getGain()
{
  return _gain;
}


/////////////////////////////////////////////////
//
//  READ VOLTAGE
//
float DMM::readVolts(uint8_t times)
{
  uint32_t total = 0;
  if (times == 0) 
  {
    times = 1;
  }
  for (int i = 0; i < times; i++)
  {
    total += analogRead(_pin);
  }
  float volts = (total * _voltageStep) / times;

  if (_gain != 1.0) 
  {
    volts *= _gain;
  }
  return volts;
}


float DMM::readMilliVolts(uint8_t times)
{
  return readVolts(times) * 1000.0;
}


float DMM::readNoise(uint8_t times)
{
  uint16_t  maxV = 0;
  uint16_t  minV = _maxSteps;

  if (times == 0) times = 1;
  for (int i = 0; i < times; i++)
  {
    uint16_t x = analogRead(_pin);
    if (x > maxV) maxV = x;
    if (x < minV) minV = x;
  }
  float v = ((maxV - minV) * _voltageStep) / times;

  if (_gain != 1.0) v *= _gain;
  return v;
}


/////////////////////////////////////////////////
//
//  READ OHM
//
void DMM::setReferenceR(float ohm)
{
  _ReferenceR = ohm;
}


float DMM::readOhm(uint8_t times)
{
  float voltage = readVolts(times);
  
  float R = _ReferenceR / voltage * _maxVoltage - _ReferenceR;
  // float R = (_maxVoltage - voltage) * _ReferenceR / voltage;
  return R;
}


float DMM::readKiloOhm(uint8_t times)
{
  return readOhm(times) * 0.001;
}


//  -- END OF FILE --


