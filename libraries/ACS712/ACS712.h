#pragma once
//
//    FILE: ACS712.h
//  AUTHOR: Rob Tillaart, Pete Thompson
// VERSION: 0.2.6
//    DATE: 2020-08-02
// PURPOSE: ACS712 library - current measurement
//
// Tested with a RobotDyn ACS712 20A breakout + UNO.
//


#include "Arduino.h"

#define ACS712_LIB_VERSION        (F("0.2.6"))


//  ACS712_FF_SINUS == 1.0/sqrt(2) == 0.5 * sqrt(2)
//  should be smaller in practice 0.5 ?
#define ACS712_FF_SINUS           (1.0/sqrt(2))
#define ACS712_FF_SQUARE          (1.0)
#define ACS712_FF_TRIANGLE        (1.0/sqrt(3))


class ACS712
{
  public:
    //  NOTE:
    //  One can quite precisely tune the value of the sensor
    //      (1) the milliVolt per Ampere and
    //      (2) the volts parameter.
    //
    //  TYPE  mV per Ampere
    //  5A    185
    //  20A   100
    //  30A   66
    ACS712(uint8_t analogPin, float volts = 5.0, uint16_t maxADC = 1023, uint8_t mVperA = 100);


    // returns mA
    // blocks 20-21 ms to sample a whole 50 or 60 Hz period.
    // lower frequencies block longer.
    int        mA_AC(float freq = 50);


    // returns mA
    // blocks < 1 ms
    int        mA_DC();


    // midpoint ADC for DC only
    inline void     setMidPoint(uint16_t mp) { _midPoint = mp; };
    inline uint16_t getMidPoint() { return _midPoint; };
    inline void     incMidPoint() { _midPoint++; };
    inline void     decMidPoint() { _midPoint--; };
    // Auto midPoint, assuming zero DC current or any AC current
    void autoMidPoint(float freq = 50);


    // also known as crest factor;  affects mA_AC() only
    // default sinus.
    inline void     setFormFactor(float ff = ACS712_FF_SINUS) { _formFactor = ff; };
    inline float    getFormFactor() { return _formFactor; };


    //  noise defaults 21
    inline void     setNoisemV(uint8_t noisemV = 21) { _noisemV = noisemV; };
    inline uint8_t  getNoisemV() { return _noisemV; };


    // AC and DC
    inline void     setmVperAmp(uint8_t mva) { _mVperAmpere = mva; };
    inline uint8_t  getmVperAmp() { return _mVperAmpere; };


    // Experimental frequency detection.
    // the minimal frequency determines the time to sample.
    float           detectFrequency(float minimalFrequency = 40);
    void            setMicrosAdjust(float factor = 1.0) { _microsAdjust = factor; };
    float           getMicrosAdjust() { return _microsAdjust; };


  private:
    uint8_t   _pin;
    float     _mVpstep;       // millivolt per step
    float     _formFactor;    // point2point -> RMS
    uint8_t   _mVperAmpere;
    uint16_t  _midPoint;
    uint8_t   _noisemV;
    float     _microsAdjust = 1.0;  // 0.9986
};

// -- END OF FILE --
