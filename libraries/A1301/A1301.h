#pragma once
//
//    FILE: A1301.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.3
//    DATE: 2010-07-22
// PURPOSE: Arduino library for A1301 A1302 magnetometer.
//     URL: https://github.com/RobTillaart/A1301


//  always check datasheet.
//    PIN    A1301
//    ===============
//     1     GND
//     2     DATA
//     3     VDD +5V


#include "Arduino.h"

#define A1301_LIB_VERSION        (F("0.2.3"))


class HALL
{
public:
  HALL(uint8_t pin);

  //  ADC parameters
  void      begin(float voltage, uint16_t steps);


  //  midpoint depends on ADC.
  void      setMidPoint(float midPoint);
  float     autoMidPoint(uint8_t times = 100);
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
  bool      isNull();
  bool      isNorth();
  bool      isSouth();
  bool      isRising();
  bool      isFalling();

  float     lastGauss();
  float     prevGauss();
  float     deltaGauss();
  float     angle();         //  == atan2(prevGauss, lastGauss);
  float     determineNoise(uint8_t times = 2);  //  in Gauss



  //  CONVERTERs
  float     Tesla(float Gauss);
  float     mTesla(float Gauss);
  float     uTesla(float Gauss);


  //  SATURATION LEVEL = EXPERIMENTAL
  //  manual override default maxGauss
  void      setMaxGauss(float maxGauss);
  float     getMaxGauss();
  bool      isSaturated();
  float     saturationLevel();


protected:
  uint8_t  _pin;
  float    _midPoint;
  float    _prevGauss;
  float    _lastGauss;
  float    _GaussmV;     //  == 1.0 / mVGauss
  float    _mVStep;
  uint16_t _maxADC;

  //  Experimental
  float    _maxGauss;
};


////////////////////////////////////////////////////
//
//  DERIVED CLASSES
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

