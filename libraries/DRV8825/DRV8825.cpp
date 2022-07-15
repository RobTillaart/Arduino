//
//    FILE: DRV8825.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.2
// PURPOSE: Arduino library for DRV8825 stepper motor driver
//    DATE: 2022-07-07
//     URL: https://github.com/RobTillaart/DRV8825

//  0.1.0   2022-07-07  initial version.
//  0.1.1   2022-07-08  update readme.md
//                      add setPosition() + getPosition();
//                      minor optimizations
//  0.1.2   2022-07-14  add support for SLP RST and EN pin
//                      update documentation
//                      update build-CI


#include "DRV8825.h"


DRV8825::DRV8825()
{
}


bool DRV8825::begin(uint8_t DIR, uint8_t STEP, uint8_t EN, uint8_t RST, uint8_t SLP)
{
  _directionPin = DIR;
  _stepPin      = STEP;

  pinMode(_directionPin, OUTPUT);
  pinMode(_stepPin, OUTPUT);
  digitalWrite(_directionPin, LOW);
  digitalWrite(_stepPin, LOW);

  //  handle conditional parameters
  if (EN != 255)
  {
    _enablePin = EN;
    pinMode(_enablePin, OUTPUT);
    digitalWrite(_enablePin, LOW);  //  page 3
  }
  if (RST != 255)
  {
    _resetPin = RST;
    pinMode(_resetPin, OUTPUT);
    digitalWrite(_resetPin, LOW);    //  page 3
  }
  if (SLP != 255)
  {
    _sleepPin = SLP;
    pinMode(_sleepPin, OUTPUT);
    digitalWrite(_sleepPin, HIGH);   //  page 3
  }
  return true;
}


void DRV8825::setStepsPerRotation(uint16_t stepsPerRotation)
{
  _stepsPerRotation = stepsPerRotation;
}


uint16_t DRV8825::getStepsPerRotation()
{
  return _stepsPerRotation;
}


bool DRV8825::setDirection(uint8_t direction)
{
  if (direction > 1) return false;
  _direction = direction;
  //  timing from datasheet 650 ns figure 1
  delayMicroseconds(1);
  digitalWrite(_directionPin, _direction);
  delayMicroseconds(1);
  return true;
}


uint8_t DRV8825::getDirection()
{
  return digitalRead(_directionPin);
}


void DRV8825::step()
{
  digitalWrite(_stepPin, HIGH);
  if (_us > 0) delayMicroseconds(_us);
  digitalWrite(_stepPin, LOW);
  if (_us > 0) delayMicroseconds(_us);

  _steps++;
  if (_stepsPerRotation > 0)
  {
    if (_direction == DRV8825_CLOCK_WISE)
    {
      _pos++;
      if (_pos >= _stepsPerRotation) _pos = 0;
    }
    else
    {
      if (_pos == 0) _pos = _stepsPerRotation;
      _pos--;
    }
  }
}


uint32_t DRV8825::resetSteps(uint32_t s)
{
  uint32_t t = _steps;
  _steps = s;
  return t;
}


uint32_t DRV8825::getSteps()
{
  return _steps;
}


void DRV8825::setStepPulseLength(uint16_t us)
{
  _us = us;
}


uint16_t DRV8825::getStepPulseLength()
{
  return _us;
}


bool DRV8825::setPosition(uint16_t pos)
{
  if (pos >= _stepsPerRotation) return false;
  _pos = pos;
  return true;
}


uint16_t DRV8825::getPosition()
{
  return _pos;
}

//  Table page 3
void DRV8825::enable()
{
  if (_enablePin != 255)
  {
    digitalWrite(_enablePin, LOW);
  }
}

void DRV8825::disable()
{
  if (_enablePin != 255)
  {
    digitalWrite(_enablePin, HIGH);
  }
}

bool DRV8825::isEnabled()
{
  if (_enablePin != 255)
  {
    return (digitalRead(_enablePin) == LOW);
  }
  return true;
}


void DRV8825::reset()
{
  if (_resetPin != 255)
  {
    digitalWrite(_resetPin, HIGH);
    delay(1);
    digitalWrite(_resetPin, LOW);
  }
}


void DRV8825::sleep()
{
  if (_sleepPin != 255)
  {
    digitalWrite(_sleepPin, LOW);
  }
}

void DRV8825::wakeup()
{
  if (_sleepPin != 255)
  {
    digitalWrite(_sleepPin, HIGH);
  }
}

bool DRV8825::isSleeping()
{
  if (_sleepPin != 255)
  {
    return (digitalRead(_sleepPin) == LOW);
  }
  return false;
}


//  -- END OF FILE --


