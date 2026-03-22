#pragma once
//
//    FILE: AMC1302.h
//  AUTHOR: Rob Tillaart
//    DATE: 2026-03-14
// VERSION: 0.1.1
// PURPOSE: Arduino library for AMC1302 current sensor.
//     URL: https://github.com/RobTillaart/AMC1302
//     URL: https://github.com/RobTillaart/ACS712   (0.4.0 API reference)


#include "Arduino.h"
#include "Wire.h"


#define AMC1302_LIB_VERSION         (F("0.1.1"))

//  ERROR CODES
//  values <> 0 are errors.
#define AMC1302_OK                  0


#define AMC_FF_SINUS                 (1.0/sqrt(2))
#define AMC_FF_SQUARE                (1.0)
#define AMC_FF_TRIANGLE              (1.0/sqrt(3))
#define AMC_FF_SAWTOOTH              (1.0/sqrt(3))
#define AMC_DEFAULT_FREQ             (50.0)



class AMC1302
{
  public:
    AMC1302(uint8_t outNpin, uint8_t outPpin);

    //  call begin() to calibrate.
    bool     begin(float voltsPerStep, float shunt = 50e-3);

    //  needs a DC current (?).
    float    calibrateVoltsPerStep(float current);

    //  manual set frequency
    void     setFrequency(float frequency);
    float    getFrequency();
    //  Frequency detection (sine wave only)
    //  the minimal frequency determines the time to sample.
    float    detectFrequency(float minimalFrequency = 40.0);
    void     setMicrosAdjust(float factor = 1.000);
    float    getMicrosAdjust();

    //  returns mA peak2peak current.
    //  blocks ~20-21 ms per cycle to sample a whole 50 or 60 Hz period.
    //  does NOT call yield() as that would disrupt measurement
    float    mA_peak2peak(uint16_t cycles = 1);

    //  returns mA
    //  blocks ~20-21 ms per cycle to sample a whole 50 or 60 Hz period.
    //  works with peak2peak level and (crest) Form Factor.
    //  does NOT call yield() as that would disrupt measurement
    float    mA_AC(uint16_t cycles = 1);


    //  returns mA
    //  blocks 20-21 ms per cycle to sample a whole 50 or 60 Hz period.
    //  works with sampling.
    //  lower frequencies block longer.
    //  does NOT call yield() as that would disrupt measurement
    float    mA_AC_sampling(uint16_t cycles = 1);


    //  returns mA
    //  blocks < 1 ms (depending on # cycles and ADC used)
    //  does call yield() for RTOS.
    float    mA_DC(uint16_t cycles = 1);


    //  Form Factor is also known as crest factor;
    //  affects mA_AC() only,  default sinus.
    void     setFormFactor(float formFactor = AMC_FF_SINUS);
    float    getFormFactor();


    //  DEBUGGING
    //  raw ADC minimum and maximum
    uint32_t getMinimum();
    uint32_t getMaximum();
    //  difference between raw outP and outN.
    //  note there is a time difference between sampling moment.
    int32_t  rawDifference();
    //  read voltage of 2 pins.
    float    readVoltageN();
    float    readVoltageP();
    //  Gain is fixed per device and cannot be set.
    float    getGain();

    //  placeholder
    int16_t  getLastError();


  protected:
    uint8_t _outNpin;
    uint8_t _outPpin;

    float   _gain;        //  fixed gain see datasheet, set in constructor.
    float   _formFactor;  //  peak2peak -> RMS
    float   _frequency     = 50.0;   //  default
    float   _microsAdjust  = 1.0;    //  0.9986

    float   _voltsPerStep  = 1.0f;   //  e.g. 5.0/1023
    float   _shunt         = 50e-3;  //  50 mOhm
    float   _amperePerVolt = 1.0f;   //  factor for optimized math

    uint8_t _lastError = AMC1302_OK;
};


/////////////////////////////////////////////////////////////////////////////
//
//  DERIVED CLASSES
//
class AMC1200 : public AMC1302
{
public:
  AMC1200(uint8_t outNpin, uint8_t outPpin);
};

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





