//
//    FILE: TSL235R.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.5
//    DATE: 2020-05-29
// PURPOSE: library for the TSL235R light to frequency convertor
//     URL: https://github.com/RobTillaart/TSL235R


#include "TSL235R.h"


TSL235R::TSL235R(float voltage)
{
  _waveLength       = 635;
  _waveLengthFactor = 1.0;
  _voltageFactor    = 1.0;
  _voltage          = voltage;
  calculateFactor();
}


float TSL235R::irradiance(uint32_t Hz)
{
  return Hz * _factor;
}


float TSL235R::irradiance(uint32_t pulses, uint32_t milliseconds)
{
  return (pulses * 1000.0 * _factor) / milliseconds;
}


float TSL235R::irradiance_HS(uint32_t pulses, uint32_t microseconds)
{
  return (pulses * 1000000.0 * _factor) / microseconds;
}


float TSL235R::getFactor()
{
  return _factor;
}


void TSL235R::setWavelength(uint16_t wavelength)
{
  _waveLength = wavelength;
  calculateFactor();
}


uint16_t TSL235R::getWavelength()
{
  return _waveLength;
}


float TSL235R::getWaveLengthFactor()
{
  return _waveLengthFactor;
}


void TSL235R::setVoltage(float voltage)
{
  _voltage = voltage;
  calculateFactor();
}


float TSL235R::getVoltage()
{
  return _voltage;
}


float TSL235R::getVoltageFactor()
{
  return _voltageFactor;
}


void TSL235R::calculateFactor()
{
  //  figure 1 datasheet
  //  1 KHz crosses the line at 35/230 between 1 and 10.
  //  so the correction factor is 10^0.15217 = 1.419659
  //  as the graph is in kHz we need to correct a factor 1000
  //  as the irradiance function gets Hz
  const float cf = 0.001419659;
  _waveLengthFactor = calculateWaveLengthFactor(_waveLength);

  _voltageFactor = 0.988 + (_voltage - 2.7) * (0.015 / 2.8);
  _factor = cf * _waveLengthFactor * _voltageFactor;
}


float TSL235R::calculateWaveLengthFactor(uint16_t _waveLength)
{
  //  figure 2 datasheet
  //  635 nm is reference 1.000
  //  remaining is linear interpolated between points in the graph
  float in[]  = { 300, 350,  400, 500,  600,  635,  700,  750,  800,  850,  900,  1000, 1100};
  float out[] = { 0.1, 0.35, 0.5, 0.75, 0.93, 1.00, 1.15, 1.20, 1.15, 1.10, 0.95, 0.40, 0.10};
  return 1.0 / multiMap(_waveLength, in, out, 13);
}


//  from https://github.com/RobTillaart/MultiMap
float TSL235R::multiMap(float value, float * _in, float * _out, uint8_t size)
{
  //  take care the value is within range
  //  value = constrain(value, _in[0], _in[size-1]);
  if (value <= _in[0]) return _out[0];
  if (value >= _in[size-1]) return _out[size-1];

  //  search right interval
  uint8_t pos = 1;  //  _in[0] already tested
  while(value > _in[pos]) pos++;

  //  this will handle all exact "points" in the _in array
  if (value == _in[pos]) return _out[pos];

  //  interpolate in the right segment for the rest
  uint8_t pos1 = pos - 1;
  return (value - _in[pos1]) * (_out[pos] - _out[pos1]) / (_in[pos] - _in[pos1]) + _out[pos1];
}


//  -- END OF FILE --

