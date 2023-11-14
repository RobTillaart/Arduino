#pragma once
//
//    FILE: PERIPUMP.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.2
//    DATE: 2022-10-13
// PURPOSE: Arduino library for peristaltic pump
//
// Tested with dfrobot peristaltic pump DFR0523
//


#include "Arduino.h"
#include "Servo.h"

#define PERIPUMP_LIB_VERSION                  (F("0.1.2"))


class PERIPUMP
{
public:
  PERIPUMP(uint8_t pumpPin);

  void     begin(float percentage = 0);

  //////////////////////////////////////////////////////
  //
  //  RUNNING
  //
  void     stop();
  //  For 100% speed
  void     forward();
  void     backward();
  //  Fine tuning speed
  void     setPercentage(float percentage);
  float    getPercentage();

  //  EXPERIMENTAL / TEST
  //  flag to swap forward and backward in software if needed.
  //       easier than doing it hardware way
  void     setInvert(bool flag = false);
  bool     getInvert();

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
  bool     _invert = false;
};


//  -- END OF FILE --

