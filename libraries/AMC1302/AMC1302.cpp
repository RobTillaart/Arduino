//
//    FILE: AMC1302.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2026-03-14
// VERSION: 0.1.0
// PURPOSE: Arduino library for AMC1302
//     URL: https://github.com/RobTillaart/AMC1302


#include "AMC1302.h"


AMC1302::AMC1302(uint8_t outNpin, uint8_t outPpin)
{
  _outNpin = outNpin;
  _outPpin = outPpin;
  _lastError = AMC1302_OK;
  _gain = 41;
}


bool AMC1302::begin(float voltsPerStep, float shunt)
{
  //  TODO verify ranges
  if (_shunt < 1e-3) _shunt = 1e-3;
  if (_voltsPerStep < 1e-6) _voltsPerStep = 1e-6;

  _voltsPerStep = voltsPerStep;
  _shunt = shunt;
  _voltsToCurrent = 1.0 / (_shunt * _gain);
  return true;
}


float AMC1302::calibrateVoltsPerStep(float current)
{
  if (current != 0)
  {
    float measured = readCurrent();
    if (measured != 0)
    {
      _voltsPerStep = _voltsPerStep * current / measured;
    }
  }
  return _voltsPerStep;
}


float AMC1302::readCurrent(bool twice)
{
  //  need to stabilize..
  int32_t rawN = analogRead(_outNpin);
  if (twice) rawN = analogRead(_outNpin);
  int32_t rawP = analogRead(_outPpin);
  if (twice) rawP = analogRead(_outPpin);

  int32_t steps = rawP - rawN;
  float voltage = steps * _voltsPerStep;
  float current = voltage * _voltsToCurrent;
  return current;
}


float AMC1302::readVoltageN()
{
  return analogRead(_outNpin) * _voltsPerStep;
}

float AMC1302::readVoltageP()
{
  return analogRead(_outPpin) * _voltsPerStep;

}


int32_t AMC1302::readDiff()
{
  int32_t rawN = analogRead(_outNpin);
  int32_t rawP = analogRead(_outPpin);
  return rawP - rawN;
}


float AMC1302::getGain()
{
  return _gain;
}


int16_t AMC1302::getLastError()
{
  int16_t e = _lastError;
  _lastError = AMC1302_OK;
  return e;
}


/////////////////////////////////////////////////////////////////////////////
//
//  DERIVED CLASSES
//
AMC1300::AMC1300(uint8_t outNpin, uint8_t outPpin)
        :AMC1302(outNpin, outPpin)
{
  _gain = 8.2f;
}

AMC1301::AMC1301(uint8_t outNpin, uint8_t outPpin)
        :AMC1302(outNpin, outPpin)
{
  _gain = 8.2f;
}

AMC1311::AMC1311(uint8_t outNpin, uint8_t outPpin)
        :AMC1302(outNpin, outPpin)
{
  _gain =1.0f;
}

AMC1351::AMC1351(uint8_t outNpin, uint8_t outPpin)
        :AMC1302(outNpin, outPpin)
{
  _gain = 0.4f;
}



//  -- END OF FILE --

