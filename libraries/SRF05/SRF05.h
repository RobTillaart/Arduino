#pragma once
//
//    FILE: SRF05.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.4
//    DATE: 2021-05-17
// PURPOSE: Arduino library for SRF05 distance sensor
//     URL: https://github.com/RobTillaart/SRF05


#include "Arduino.h"

#define SRF05_LIB_VERSION                 (F("0.1.4"))


const uint8_t SRF05_MODE_SINGLE      = 0;
const uint8_t SRF05_MODE_AVERAGE     = 1;
const uint8_t SRF05_MODE_MEDIAN      = 2;
const uint8_t SRF05_MODE_RUN_AVERAGE = 3;


class SRF05
{
public:
  explicit SRF05(const uint8_t trigger, const uint8_t echo, const uint8_t out = 0);


  //  configuration
  void     setSpeedOfSound(float sos = 340);
  float    getSpeedOfSound();

  //  adjust timing
  bool     setCorrectionFactor(float factor = 1);
  float    getCorrectionFactor();


  //  operational mode
  void     setModeSingle();  //  default
  void     setModeAverage(uint8_t count);
  void     setModeMedian(uint8_t count);
  void     setModeRunningAverage(float alpha);
  uint8_t  getOperationalMode();


  //  get distance
  uint32_t getTime();         //  uSec
  uint32_t getMillimeter();   //  mm
  float    getCentimeter();   //  cm
  float    getMeter();        //  m
  float    getInch();         //  inch = 2.54 cm
  float    getFeet();         //  feet = 12 inch


  //  Experimental - calibration
  float    determineSpeedOfSound(uint16_t count);


  //  Experimental - adjust trigger length 
  //  - gain is a few microseconds at best.
  //  - 10 microseconds is advised minimum
  //  - to be investigated.
  void     setTriggerLength(uint8_t length = 10);
  uint8_t  getTriggerLength();

  //  TIMING
  uint32_t lastTime();


private:
  uint8_t  _trigger;
  uint8_t  _echo;
  uint8_t  _out;
  uint8_t  _mode  = SRF05_MODE_SINGLE;
  uint8_t  _count = 1;
  float    _alpha = 1.0;
  float    _value = 0;
  float    _correctionFactor = 1;
  uint8_t  _triggerLength    = 10;
  float    _speedOfSound     = 340;      //  20°C
  uint32_t _lastTime = 0;
 
  uint32_t _read();
  void     _insertSort(uint32_t * array, uint8_t size);
};


//  -- END OF FILE --

