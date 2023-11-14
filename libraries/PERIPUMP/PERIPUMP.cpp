//
//    FILE: PERIPUMP.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.2
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


void PERIPUMP::begin(float percentage)
{
  _myServo.attach(_pin);
  resetRunTime();
  setPercentage(percentage);
}


void PERIPUMP::stop()
{
  setPercentage(0);
}


void PERIPUMP::forward()
{
  setPercentage(100);
}


void PERIPUMP::backward()
{
  setPercentage(-100);
}


//  the worker.
void PERIPUMP::setPercentage(float percentage)
{
  //  weighted runtime ?
  //  _sumTime += (millis() - _start) * abs(_percentage);

  _percentage = constrain(percentage, -100.0, 100.0);

  uint32_t now = millis();

  uint16_t ms = 0;
  if (_percentage == 0)
  {
    if (_start != 0) _sumTime += (now - _start);
    //  middle position is stop
    ms = 0;
    _start = 0;
  }
  else if (_percentage > 0)
  {
    ms = 500 + 5 * _percentage;
    if (_start == 0) _start = now;
  }
  else if (_percentage < 0)
  {
    ms = -500 + 5 * _percentage;
    if (_start == 0) _start = now;
  }

  if (_invert) _myServo.writeMicroseconds(1500 - ms);
  else _myServo.writeMicroseconds(1500 + ms);
}


float PERIPUMP::getPercentage()
{
  return _percentage;
}


void PERIPUMP::setInvert(bool flag)
{
  _invert = flag;
}


bool PERIPUMP::getInvert()
{
  return _invert;
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


//  -- END OF FILE --

