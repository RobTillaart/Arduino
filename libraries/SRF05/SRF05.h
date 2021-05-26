#pragma once
//
//    FILE: SRF05.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2021-05-17
// PURPOSE: Arduino library for SRF05 distance sensor
//     URL: https://github.com/RobTillaart/SRF05


#include "Arduino.h"

#define SRF05_LIB_VERSION         (F("0.1.0"))


class SRF05
{
public:
  explicit SRF05(const uint8_t trigger, const uint8_t echo, const uint8_t out = 0);


  // configuration
  void     setSpeedOfSound(float sos = 340);
  float    getSpeedOfSound();

  // adjust timing
  void     setCorrectionFactor(float cf = 1) { _correctionFactor = cf; };
  float    getCorrectionFactor() { return _correctionFactor; };


  // operational mode
  void     setModeSingle();
  void     setModeAverage(uint8_t cnt);
  void     setModeMedian(uint8_t cnt);
  void     setModeRunningAverage(float alpha);
  uint8_t  getOperationalMode();


  // get distance
  uint32_t getTime();         // uSec
  uint32_t getMillimeter();   // mm
  float    getCentimeter();   // cm
  float    getMeter();        // m
  float    getInch();         // inch = 2.54 cm
  float    getFeet();         // feet = 12 Inch


  // Experimental - calibration
  float    determineSpeedOfSound(uint16_t distance);


  // Experimental - adjust trigger length - gain is a few usec at best.
  // 10 usec is advised minimum
  // void     setTriggerLength(uint8_t len = 10) { _triggerLength = len; };
  // uint8_t  getTriggerLength() { return _triggerLength; };


private:
  uint8_t  _trigger;
  uint8_t  _echo;
  uint8_t  _out;
  uint8_t  _mode  = 0;
  uint8_t  _cnt   = 1;
  float    _alpha = 1.0;
  float    _val   = 0;
  float    _correctionFactor = 1;
  uint8_t  _triggerLength = 10;
  float    _speedOfSound = 340;      // ~20°C

  uint32_t _read();
  void     _insertSort(uint32_t * array, uint8_t size);

};

// -- END OF FILE --
