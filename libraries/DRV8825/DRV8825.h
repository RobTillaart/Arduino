#pragma once
//
//    FILE: DRV8825.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: Arduino library for DRV8825 stepper motor driver
//    DATE: 2022-07-07
//     URL: https://github.com/RobTillaart/DRV8825


#include "Arduino.h"


#define DRV8825_LIB_VERSION              (F("0.1.0"))


//  setDirection
const uint8_t DRV8825_CLOCK_WISE         = 0;  //  LOW
const uint8_t DRV8825_COUNTERCLOCK_WISE  = 1;  //  HIGH


class DRV8825
{
public:
  DRV8825();

  bool     begin(uint8_t dirPin, uint8_t stepPin);

  //       DIRECTION
  //       0 = DRV8825_CLOCK_WISE
  //       1 = DRV8825_COUNTERCLOCK_WISE
  //       returns false if parameter out of range.
  bool     setDirection(uint8_t direction = DRV8825_CLOCK_WISE);
  uint8_t  getDirection();

  //       STEPS
  void     setStepsPerRotation(uint16_t stepsPerRotation);
  uint16_t getStepsPerRotation();
  void     step();
  int32_t  resetSteps(int32_t s = 0 );
  int32_t  getSteps();

  //       CONFIGURATION
  //       step pulse length is in microseconds
  //       default 1.9 us
  void     setStepPulseLength(uint16_t us = 2);
  uint16_t getStepPulseLength();


private:
  uint16_t _stepsPerRotation = 0;
  uint8_t  _directionPin     = 255;
  uint8_t  _stepPin          = 255;
  uint8_t  _direction        = DRV8825_CLOCK_WISE;
  int32_t  _steps            = 0;
  uint16_t _us               = 2;
};


//  -- END OF FILE --


