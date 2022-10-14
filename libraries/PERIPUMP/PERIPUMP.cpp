//
//    FILE: PERIPUMP.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2022-10-13
// PURPOSE: Arduino library for peristaltic pump


#include "PERIPUMP.h"


//  CONSTRUCTOR
PERIPUMP::PERIPUMP(uint8_t pumpPin)
{
  _pin        = pumpPin;
  _percentage = 0;
  _sumTime    = 0;
}


void PERIPUMP::begin()
{
  _myServo.attach(_pin);
  stop();
  resetRunTime();
}


void PERIPUMP::stop()
{
  _myServo.writeMicroseconds(1500);
  if (_start != 0)
  {
    _sumTime += (millis() - _start);
    _start = 0;
  }
}


void PERIPUMP::setPercentage(float percentage)
{
  //  weighted runtime ?
  //  _sumTime += (millis() - _start) * abs(_percentage);
  _percentage = constrain(percentage, -100, 100);

  uint16_t ms = 0;
  if (_percentage == 0)
  {
    ms = 1500;
    if (_start != 0)
    {
      _sumTime += (millis() - _start);
      _start = 0;
    }
  }
  else if (_percentage > 0)
  {
    //  1600 - 2500
    ms = 1600 + 9 * _percentage;         //  9 ==  900 / 100%
    if (_start == 0) _start = millis();
  }
  else if (_percentage < 0)
  {
    //  500 - 1400
    ms = 1400 + 9 * _percentage;
    if (_start == 0) _start = millis();
  }
  _myServo.writeMicroseconds(ms);
}


float PERIPUMP::getPercentage()
{
  return _percentage;
}


//////////////////////////////////////////////////////
//
//  DURATION
//
float PERIPUMP::getRunTime()
{
  float seconds = _sumTime;
  if (_start != 0) seconds += (millis() - _start);
  return seconds * 0.001;
}


float PERIPUMP::resetRunTime()
{
  float s = getRunTime();
  _sumTime = 0;
  _start = 0;
  return s;
}


// -- END OF FILE --

