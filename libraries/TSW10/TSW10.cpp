//
//    FILE: TSW10.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2026-05-22
// VERSION: 0.1.0
// PURPOSE: Arduino library for TSW10 analog turbidity sensor.
//     URL: https://github.com/RobTillaart/TSW10



#include "TSW10.h"


TSW10::TSW10(uint8_t analogPin)
{
  _apin = analogPin;
  _lastRead = 0;
  _VoltsPerStep = 5.0 / 1023;  //  default assumption
}


bool TSW10::begin(float voltage, uint16_t maxSteps)
{
  //  reset variables
  _VoltsPerStep = voltage / maxSteps;
  _lastRead = 0;
  return true;
}


float TSW10::getVoltage(int times)
{
  //  constrain times
  if (times <= 0) times = 1;
  if (times > 32) times = 32;
  uint32_t sum = 0;
  for (int i = 0; i < times; i++)
  {
    sum += analogRead(_apin);
  }
  float volts = (sum * _VoltsPerStep) / times;
  _lastRead = millis();
  return volts;
}

float TSW10::getNTU(int times)
{
  float volts = getVoltage(times);
  return volts2NTU(volts);
}

float TSW10::volts2NTU(float volts)
{
  //  https://github.com/RobTillaart/MultiMap, non linear interpolation
  //  note: the _in array must have increasing values.
  //  based upon graph in the TSW10 data sheet.
  int size = 10;
  float    _in[size] = {2.70, 2.80, 3.00, 3.15, 3.35, 3.65, 4.00, 4.35, 4.70, 4.75};
  int16_t _out[size] = {2000, 1750, 1500, 1250, 1000,  750,  500,  250,   50,    0};

  //  output is constrained to out array
  if (volts <= _in[0]) return _out[0];
  if (volts >= _in[size-1]) return _out[size-1];

  //  search right interval
  uint16_t pos = 1;  // _in[0] already tested
  while(volts > _in[pos]) pos++;

  //  this will handle all exact "points" in the _in array
  if (volts == _in[pos]) return _out[pos];

  //  interpolate in the right segment for the rest
  return (volts - _in[pos-1]) * (_out[pos] - _out[pos-1]) / (_in[pos] - _in[pos-1]) + _out[pos-1];
}

uint32_t TSW10::lastRead()
{
  return _lastRead;
}


///////////////////////////////////////////////////
//
//  PRIVATE
//


//  -- END OF FILE --

