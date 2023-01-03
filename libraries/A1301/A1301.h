#pragma once
//
//    FILE: A1301.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.2
//    DATE: 2010-07-22
// PURPOSE: Arduino library for A1301 A1302 magnetometer.

//  always check datasheet.
//    PIN    A1301
//    ===============
//     1     GND
//     2     DATA
//     3     VDD +5V


#include "Arduino.h"

#define A1301_LIB_VERSION        (F("0.1.2"))


class HALL
{
public:
  HALL(uint8_t pin);

  //  ADC parameters
  void      begin(float voltage, uint16_t steps);

  //  midpoint depends on ADC.
  void      setMidPoint(float midPoint);
  float     getMidPoint();
  //  to override default sensitivity
  void      setSensitivity(float sensitivity);
  float     getSensitivity();

  //  READ
  //  times > 1 ==> more stable read / averaging.
  //  uses internal ADC
  float     raw(uint8_t times = 1);   //  returns raw ADC
  float     read(uint8_t times = 1);  //  returns Gauss
  //  for external ADC
  float     readExt(float raw);

  //  ANALYSE
  bool      isNorth();
  bool      isSouth();
  float     lastGauss();
  float     prevGauss();

  //  CONVERTERs
  float     Tesla(float Gauss);
  float     mTesla(float Gauss);
  float     uTesla(float Gauss);

  //  EXPERIMENTAL
  //  manual override default maxGauss
  void      setMaxGauss(uint16_t maxGauss);
  float     getMaxGauss();
  bool      isSaturated();


protected:
  uint8_t  _pin         = 0;
  float    _midPoint    = 512;
  float    _prevGauss   = 0;
  float    _lastGauss   = 0;
  float    _mVGauss     = 2.5;
  float    _mVStep      = 5000.0 / 1023;
  uint16_t _maxADC      = 1023;
  
  //  Experimental
  float    _maxGauss    = 500;
};

////////////////////////////////////////////////////
//
//  DERIVED
//
class A1301 : public HALL
{
public:
  A1301(uint8_t pin);
};

class A1302 : public HALL
{
public:
  A1302(uint8_t pin);
};

class A1324 : public HALL
{
public:
  A1324(uint8_t pin);
};

class A1325 : public HALL
{
public:
  A1325(uint8_t pin);
};

class A1326 : public HALL
{
public:
  A1326(uint8_t pin);
};


//  -- END OF FILE --

