//
//    FILE: TGS2620.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2026-02-10
// VERSION: 0.1.0
// PURPOSE: Arduino library for TGS2620 and compatibles
//     URL: https://github.com/RobTillaart/TGS2620


#include "TGS2620.h"


TGS2620::TGS2620(uint8_t analogPin, uint16_t maxSteps = 1023)
{
  _analogPin = analogPin;
  _maxSteps  = maxSteps;
  _rLoad = 1;
  _rZero = 1;
}


bool TGS2620::configure(uint16_t Rzero, uint16_t Rload)
{
  //  reset variables
  _lastRead = 0;
  _rLoad    = Rzero;
  _rZero    = Rload;
  return true;
}


void TGS2620::calibrate(float a, float b)
{
  _a = a;
  _b = b;
}


/////////////////////////////////////////////
//
//  READ SENSOR
//
float TGS2620::getPPM(uint8_t reads)
{
  uint32_t rawRLoad = 0;
  if (reads == 0) reads = 1;
  for (int r = 0; r < reads; r++)
  {
    rawRLoad += analogRead(_analogPin);
  }
  rawRLoad /= reads;

  _lastRead = millis();
  //  formula page 2 - optimize?
  float rSensor =  ((1.0 * _maxSteps - rawRLoad) / rawRLoad) * _rLoad;
  //  convert to PPM
  return _a * pow(rSensor / _rZero, _b);
}

float TGS2620::getPPM(uint16_t rawRLoad, uint16_t maxSteps)
{
  _lastRead = millis();
  //  formula page 2 - optimize?
  float rSensor =  ((1.0 * maxSteps - rawRLoad) / rawRLoad) * _rLoad;
  //  convert to PPM
  return _a * pow(rSensor / _rZero, _b);
}


uint32_t TGS2620::lastRead()
{
  return _lastRead;
}


//  -- END OF FILE --

