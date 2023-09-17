//
//    FILE: DRV8825.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.0
// PURPOSE: Arduino library for DRV8825 stepper motor driver
//    DATE: 2022-07-07
//     URL: https://github.com/RobTillaart/DRV8825


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
    digitalWrite(_enablePin, LOW);   //  page 3
  }
  if (RST != 255)
  {
    _resetPin = RST;
    pinMode(_resetPin, OUTPUT);
    digitalWrite(_resetPin, HIGH);   //  page 3
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
  if (_stepPulseLength > 0) delayMicroseconds(_stepPulseLength);
  digitalWrite(_stepPin, LOW);
  if (_stepPulseLength > 0) delayMicroseconds(_stepPulseLength);

  _steps++;
  if (_stepsPerRotation > 0)
  {
    if (_direction == DRV8825_CLOCK_WISE)
    {
      _position++;
      if (_position >= _stepsPerRotation) _position = 0;
    }
    else
    {
      if (_position == 0) _position = _stepsPerRotation;
      _position--;
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


void DRV8825::setStepPulseLength(uint16_t stepPulseLength)
{
  _stepPulseLength = stepPulseLength;
}


uint16_t DRV8825::getStepPulseLength()
{
  return _stepPulseLength;
}


bool DRV8825::setPosition(uint16_t position)
{
  if (position >= _stepsPerRotation) return false;
  _position = position;
  return true;
}


uint16_t DRV8825::getPosition()
{
  return _position;
}

//  Table page 3
bool DRV8825::enable()
{
  if (_enablePin == 255) return false;
  digitalWrite(_enablePin, LOW);
  return true;
}

bool DRV8825::disable()
{
  if (_enablePin == 255) return false;
  digitalWrite(_enablePin, HIGH);
  return true;
}

bool DRV8825::isEnabled()
{
  if (_enablePin != 255)
  {
    return (digitalRead(_enablePin) == LOW);
  }
  return true;
}


bool DRV8825::reset()
{
  if (_resetPin == 255) return false;
  digitalWrite(_resetPin, LOW);
  delay(1);
  digitalWrite(_resetPin, HIGH);
  return true;
}


bool DRV8825::sleep()
{
  if (_sleepPin == 255) return false;
  digitalWrite(_sleepPin, LOW);
  return true;
}

bool DRV8825::wakeup()
{
  if (_sleepPin == 255) return false;
  digitalWrite(_sleepPin, HIGH);
  return true;
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

