//
//    FILE: rain.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.4
//    DATE: 2021-12-03
// PURPOSE: Arduino library for a rain sensor
//     URL: https://github.com/RobTillaart/RAIN
//          https://www.tinytronics.nl/shop/nl/sensoren/vloeistof/regensensor


#include "rain.h"


RAIN::RAIN(uint8_t analogPort, uint8_t powerPin)
{
  _analogPort = analogPort;
  _powerPin   = powerPin;
  _maxVoltage = 5;
  _maxSteps   = 1023;
  _dryRefVoltage = _maxVoltage;
}


bool RAIN::begin(float maxVoltage, uint16_t maxSteps)
{
  _maxVoltage    = maxVoltage;
  _maxSteps      = maxSteps;
  _mVstep        = _maxVoltage / _maxSteps;
  _dryRefVoltage = _maxVoltage;

  if (_powerPin != 255)
  {
    pinMode(_powerPin, OUTPUT);
    powerOn();
  }
  read();
  return true;
}


float RAIN::raw(uint8_t times)
{
  if (times == 0) times = 1;
  float sum = 0;

  powerOn();
  for (int i = 0; i < times; i++)
  {
    sum += analogRead(_analogPort);
  }
  powerOff();

  if (times > 1) sum /= times;
  return sum;
}


float RAIN::read(uint8_t times)
{
  _previous = _voltage;
  _voltage = raw(times) * _mVstep;
  return _voltage;
}


//////////////////////////////////////////////////////////////////
//
//  ANALYSIS
//
void RAIN::setDryReference(float dryRef)
{
  _dryRefVoltage = dryRef;
}


float RAIN::getDryReference()
{
  return _dryRefVoltage;
}


float RAIN::percentage()
{
  float perc = 100.0 - (_voltage * 100.0 / _dryRefVoltage);
  if (perc < 0) perc = 0;
  return perc;
}


float RAIN::delta()
{
  return _voltage - _previous;
}


//////////////////////////////////////////////////////////////////
//
//  LEVEL
//
bool RAIN::setLevel(uint8_t nr, uint16_t milliVolts)
{
  if (nr == 0) return false;
  if (nr > 4) return false;
  _level[nr] = milliVolts;
  return true;
}


uint8_t RAIN::getLevel()
{
  uint16_t value = _voltage * 1000;
  for (int index = 4; index > 0; index--)
  {
    if (value >= _level[index]) return index;
  }
  return 0;
}


//////////////////////////////////////////////////////////////////
//
//  POWER
//
void RAIN::powerOn()
{
  if (_powerPin != 255)
  {
    digitalWrite(_powerPin, HIGH);
    delayMicroseconds(_powerDelay);  //  time to stabilize, adjust if needed.
  }
}


void RAIN::powerOff()
{
  if (_powerPin != 255)
  {
    digitalWrite(_powerPin, LOW);
  }
}

void RAIN::setPowerDelay(uint8_t powerDelay)
{
  _powerDelay = powerDelay;
}


uint8_t RAIN::getPowerDelay()
{
  return _powerDelay;
}


//  -- END OF FILE --

