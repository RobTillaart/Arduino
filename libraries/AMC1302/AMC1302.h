#pragma once
//
//    FILE: AMC1302.h
//  AUTHOR: Rob Tillaart
//    DATE: 2026-03-14
// VERSION: 0.1.0
// PURPOSE: Arduino library for AMC1302 current sensor.
//     URL: https://github.com/RobTillaart/AMC1302
//


#include "Arduino.h"
#include "Wire.h"


#define AMC1302_LIB_VERSION         (F("0.1.0"))

//  ERROR CODES
//  values <> 0 are errors.
#define AMC1302_OK                  0


class AMC1302
{
public:
  AMC1302(uint8_t outNpin, uint8_t outPpin);

  //  call begin() to calibrate.
  bool     begin(float voltsPerStep, float shunt = 50e-3);

  float    calibrateVoltsPerStep(float current);

  float    readCurrent(bool twice = false);
  float    readVoltageN();
  float    readVoltageP();

  //  DEBUGGING
  int32_t  readDiff();
  float    getGain();

  //  placeholder
  int16_t  getLastError();

protected:
  uint8_t _outNpin;
  uint8_t _outPpin;

  float   _gain;  //  fixed see datasheet, set in constructor.

  float   _voltsPerStep  = 1.0f;   //  e.g. 5.0/1023
  float   _shunt = 50e-3;          //  50 mOhm
  float   _voltsToCurrent = 1.0f;  //  factor for optimized math

  uint8_t _lastError = AMC1302_OK;
};


/////////////////////////////////////////////////////////////////////////////
//
//  DERIVED CLASSES
//
class AMC1300 : public AMC1302
{
public:
  AMC1300(uint8_t outNpin, uint8_t outPpin);
};

class AMC1301 : public AMC1302
{
public:
  AMC1301(uint8_t outNpin, uint8_t outPpin);
};

class AMC1311 : public AMC1302
{
public:
  AMC1311(uint8_t outNpin, uint8_t outPpin);
};

class AMC1351 : public AMC1302
{
public:
  AMC1351(uint8_t outNpin, uint8_t outPpin);
};




//  -- END OF FILE --





