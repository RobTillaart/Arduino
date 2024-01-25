#pragma once
//
//    FILE: ACS712.h
//  AUTHOR: Rob Tillaart, Pete Thompson
// VERSION: 0.3.9
//    DATE: 2020-08-02
// PURPOSE: ACS712 library - current measurement
//     URL: https://github.com/RobTillaart/ACS712
//
// Tested with a RobotDyn ACS712 20A breakout + UNO.
//


#include "Arduino.h"


#define ACS712_LIB_VERSION        (F("0.3.9"))


//  ACS712_FF_SINUS == 1.0/sqrt(2) == 0.5 * sqrt(2)
//  should be smaller in practice 0.5 ?
#define ACS712_FF_SINUS           (1.0/sqrt(2))
#define ACS712_FF_SQUARE          (1.0)
#define ACS712_FF_TRIANGLE        (1.0/sqrt(3))
#define ACS712_FF_SAWTOOTH        (1.0/sqrt(3))

#define ACS712_DEFAULT_FREQ       50
#define ACS712_DEFAULT_NOISE      21


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

    //  returns mA peak2peak current.
    //  blocks ~20-21 ms per cycle to sample a whole 50 or 60 Hz period.
    //  does NOT call yield() as that would disrupt measurement
   float mA_peak2peak(float frequency = ACS712_DEFAULT_FREQ, uint16_t cycles = 1);


    //  returns mA
    //  blocks ~20-21 ms per cycle to sample a whole 50 or 60 Hz period.
    //  works with peak2peak level and (crest) Form Factor.
    //  lower frequencies block longer.
    //  does NOT call yield() as that would disrupt measurement
    float    mA_AC(float frequency = ACS712_DEFAULT_FREQ, uint16_t cycles = 1);


    //  returns mA
    //  blocks 20-21 ms per cycle to sample a whole 50 or 60 Hz period.
    //  works with sampling.
    //  lower frequencies block longer.
    //  does NOT call yield() as that would disrupt measurement
    float    mA_AC_sampling(float frequency = ACS712_DEFAULT_FREQ, uint16_t cycles = 1);


    //  returns mA
    //  blocks < 1 ms (depending on # cycles and ADC used)
    //  does call yield() for RTOS.
    float    mA_DC(uint16_t cycles = 1);


    //  midPoint functions
    //  set reference point (raw ADC) for both DC and AC
    uint16_t setMidPoint(uint16_t midPoint);
    uint16_t getMidPoint();
    uint16_t incMidPoint();
    uint16_t decMidPoint();
    //  Auto midPoint, assuming zero DC current or any AC current
    //  For DC current set the frequency to 1000 or so to reduce blocking.
    uint16_t autoMidPoint(float frequency = ACS712_DEFAULT_FREQ, uint16_t cycles = 1);
    //  Auto midPoint, dedicated for zero DC current (much faster ==> less blocking)
    uint16_t autoMidPointDC(uint16_t cycles = 1);
    //  resets to half maxADC
    uint16_t resetMidPoint();


    //  Form Factor is also known as crest factor;
    //  affects mA_AC() only,  default sinus.
    void     setFormFactor(float formFactor = ACS712_FF_SINUS);
    float    getFormFactor();


    //  noise defaults 21 datasheet
    void     setNoisemV(uint8_t noisemV = ACS712_DEFAULT_NOISE);
    uint8_t  getNoisemV();
    //  enable/disable noiseSuppression for this measurement as needed.
    float    mVNoiseLevel(float frequency = ACS712_DEFAULT_FREQ, uint16_t cycles = 1);  //  uses mA_peak2peak()
    void     suppressNoise(bool flag);


    //  Adjusting resolution AC and DC
    void     setmVperAmp(float mVperAmpere);
    float    getmVperAmp();
    float    getmAPerStep();
    float    getAmperePerStep();


    //  Frequency detection.
    //  the minimal frequency determines the time to sample.
    float    detectFrequency(float minimalFrequency = 40);
    void     setMicrosAdjust(float factor = 1.0);
    float    getMicrosAdjust();

    //  DEBUG
    uint16_t getMinimum(uint16_t milliSeconds = 20);
    uint16_t getMaximum(uint16_t milliSeconds = 20);


    //  EXPERIMENTAL 0.3.4
    //  function returning 16 bit max, with pin or channel as parameter
    void setADC(uint16_t (*)(uint8_t), float volts, uint16_t maxADC);


  private:
    uint8_t   _pin;
    uint16_t  _maxADC;
    float     _mVperStep;
    float     _formFactor;    //  peak2peak -> RMS
    float     _mVperAmpere;
    float     _mAPerStep;
    int       _midPoint;
    uint8_t   _noisemV;
    float     _microsAdjust   = 1.0;  //  0.9986
    bool      _suppresNoise = false;

    //  EXPERIMENTAL 0.3.4
    //  supports up to 16 bits ADC.
    uint16_t (* _readADC)(uint8_t);
    uint16_t _analogRead(uint8_t pin);
    
};


//  -- END OF FILE --

