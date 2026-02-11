#pragma once
//
//    FILE: TGS2620.h
//  AUTHOR: Rob Tillaart
//    DATE: 2026-02-10
// VERSION: 0.1.0
// PURPOSE: Arduino library for TGS2620 and compatibles
//     URL: https://github.com/RobTillaart/TGS2620


#include "Arduino.h"


#define TGS2620_LIB_VERSION         (F("0.1.0"))


class TGS2620
{
public:
  TGS2620(uint8_t analogPin, uint16_t maxSteps);

  //  combine with calibrate?
  bool     configure(uint16_t RZero, uint16_t RLoad);

  //  to be determined once per sensor or from datasheet.
  //  will be different per gas type.
  //  TODO describe a calibration process?
  //  store in EEPROM?
  void     calibrate(float a, float b);

  //  read the sensor and convert to PPM
  //  internal ADC
  float    getPPM(uint8_t reads = 1);
  //  external ADC  (e.g. measure 477 , maxSteps 4095 = 12 bit).
  float    getPPM(uint16_t rawRLoad, uint16_t maxSteps);
  uint32_t lastRead();


private:
  uint8_t  _analogPin;
  uint16_t _maxSteps;
  uint32_t _lastRead;

  uint16_t _rZero;
  uint16_t _rLoad;

  //  calibration values
  float    _a;
  float    _b;
};


//  -- END OF FILE --





