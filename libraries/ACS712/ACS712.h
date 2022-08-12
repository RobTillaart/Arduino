#pragma once
//
//    FILE: ACS712.h
//  AUTHOR: Rob Tillaart, Pete Thompson
// VERSION: 0.2.7
//    DATE: 2020-08-02
// PURPOSE: ACS712 library - current measurement
//
// Tested with a RobotDyn ACS712 20A breakout + UNO.
//


#include "Arduino.h"

#define ACS712_LIB_VERSION        (F("0.2.7"))


//  ACS712_FF_SINUS == 1.0/sqrt(2) == 0.5 * sqrt(2)
//  should be smaller in practice 0.5 ?
#define ACS712_FF_SINUS           (1.0/sqrt(2))
#define ACS712_FF_SQUARE          (1.0)
#define ACS712_FF_TRIANGLE        (1.0/sqrt(3))
#define ACS712_FF_SAWTOOTH        (1.0/sqrt(3))


class ACS712
{
  public:
    //  NOTE:
    //  One can quite precisely tune the value of the sensor
    //      (1) the milliVolt per Ampere and
    //      (2) the volts parameter.
    //
    //  TYPE   mV per Ampere
    //  5A        185.0
    //  20A       100.0
    //  30A        66.0
    ACS712(uint8_t analogPin, float volts = 5.0, uint16_t maxADC = 1023, float mVperAmpere = 100);


    //  returns mA
    //  blocks 20-21 ms to sample a whole 50 or 60 Hz period.
    //  lower frequencies block longer.
    int      mA_AC(float frequency = 50);


    //  returns mA
    //  blocks < 1 ms
    int      mA_DC();


    //  midPoint ADC for DC only
    void     setMidPoint(uint16_t midPoint) { _midPoint = midPoint; };
    uint16_t getMidPoint() { return _midPoint; };
    void     incMidPoint() { _midPoint++; };
    void     decMidPoint() { _midPoint--; };
    //  Auto midPoint, assuming zero DC current or any AC current
    void autoMidPoint(float frequency = 50);


    //  Form Factor is also known as crest factor;
    //  affects mA_AC() only,  default sinus.
    void     setFormFactor(float formFactor = ACS712_FF_SINUS) { _formFactor = formFactor; };
    float    getFormFactor() { return _formFactor; };


    //  noise defaults 21
    void     setNoisemV(uint8_t noisemV = 21) { _noisemV = noisemV; };
    uint8_t  getNoisemV() { return _noisemV; };


    //  AC and DC
    void     setmVperAmp(float mVperAmpere) { _mVperAmpere = mVperAmpere; };
    float    getmVperAmp() { return _mVperAmpere; };


    //  Frequency detection.
    //  the minimal frequency determines the time to sample.
    float    detectFrequency(float minimalFrequency = 40);
    void     setMicrosAdjust(float factor = 1.0) { _microsAdjust = factor; };
    float    getMicrosAdjust() { return _microsAdjust; };


  private:
    uint8_t   _pin;
    float     _mVperStep;
    float     _formFactor;    //  point2point -> RMS
    float     _mVperAmpere;
    uint16_t  _midPoint;
    uint8_t   _noisemV;
    float     _microsAdjust = 1.0;  //  0.9986
};


// -- END OF FILE --

