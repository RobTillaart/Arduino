#pragma once
//
//    FILE: PERIPUMP.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2022-10-13
// PURPOSE: Arduino library for peristaltic pump
//
// Tested with dfrobot peristaltic pump DFR0523
//


#include "Arduino.h"
#include "Servo.h"

#define PERIPUMP_LIB_VERSION        (F("0.1.0"))


class PERIPUMP
{
public:
  PERIPUMP(uint8_t pumpPin);

  void     begin();

  //////////////////////////////////////////////////////
  //
  //  RUNNING
  //
  void     stop();
  void     setPercentage(float percentage);
  float    getPercentage();

  //////////////////////////////////////////////////////
  //
  //  DURATION
  //
  float    getRunTime();    //  total seconds running since last reset / start.
  float    resetRunTime();


private:
  uint8_t  _pin;
  float    _percentage;
  Servo    _myServo;
  uint32_t _sumTime = 0;
  uint32_t _start   = 0;
};


// -- END OF FILE --

