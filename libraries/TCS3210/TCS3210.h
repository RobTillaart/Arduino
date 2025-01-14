#pragma once
//
//    FILE: TCS3210.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
// PURPOSE: Arduino library for TCS3210 colour light to frequency convertor.
//    DATE: 2025-01-12
//     URL: https://github.com/RobTillaart/TCS3210


#include "Arduino.h"

#define TCS3210_LIB_VERSION               (F("0.1.1"))


class TCS3210
{
public:
  TCS3210(uint8_t S0, uint8_t S1, uint8_t S2, uint8_t S3, uint8_t OE, uint8_t data);

  bool begin();
  uint8_t getType();

  void enable();
  void disable();

  //  Select colour filter for the next measurement
  void selectRed();
  void selectGreen();
  void selectBlue();
  void selectNone();

  //  Select the percentage for the next measurement
  void powerDown();
  void set2Percent();
  void set20Percent();
  void set100Percent();

  //  Read the duration or frequency.
  //  default may block for up to 100 milliseconds.
  uint32_t getDuration(uint16_t ms = 100);   //  returns micros
  float    getFrequency(uint16_t ms = 100);  //  returns Hz.


protected:
  void _setFilter(uint8_t n);
  void _setPercentage(uint8_t n);

  uint8_t _s0, _s1, _s2, _s3;
  uint8_t _oe, _data;
  uint8_t _factor = 0;
  uint8_t _type;
};


/////////////////////////////////////////////////////////////////////////////
//
//  DERIVED CLASS TCS3200
//
class TCS3200 : public TCS3210
{
public:
  TCS3200(uint8_t S0, uint8_t S1, uint8_t S2, uint8_t S3, uint8_t OE, uint8_t data);
};


//  -- END OF FILE --

