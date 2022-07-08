//
//    FILE: DRV8825.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: Arduino library for DRV8825 stepper motor driver
//    DATE: 2022-07-07
//     URL: https://github.com/RobTillaart/DRV8825

//  0.1.0   2022-07-07  initial version.


#include "DRV8825.h"


DRV8825::DRV8825()
{
}


bool DRV8825::begin(uint8_t dirPin, uint8_t stepPin)
{
  _directionPin = dirPin;
  _stepPin      = stepPin;
  pinMode(_directionPin, OUTPUT);
  pinMode(_stepPin, OUTPUT);
  
  digitalWrite(_directionPin, LOW);  // TODO check
  digitalWrite(_stepPin, LOW);       // TODO check
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
  digitalWrite(_directionPin, _direction);
  delayMicroseconds(_us);
  return true;
}


uint8_t DRV8825::getDirection()
{
  return digitalRead(_directionPin);
}


void DRV8825::step()
{
  digitalWrite(_stepPin, HIGH);
  delayMicroseconds(_us);
  digitalWrite(_stepPin, LOW);
  delayMicroseconds(_us);

  if (_stepsPerRotation > 0)
  {
    if (_direction == DRV8825_CLOCK_WISE) _steps++;
    else _steps--;
  }
}


int32_t DRV8825::resetSteps(int32_t s)
{
  int32_t t = _steps;
  _steps = s;
  return t;
}


int32_t DRV8825::getSteps()
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


//  -- END OF FILE --


