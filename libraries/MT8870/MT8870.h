#pragma once
//
//    FILE: MT8870.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.6
//    DATE: 2019-02-11
// PURPOSE: Arduino library for MT8870 DTMF decoder (breakout)
//     URL: https://github.com/RobTillaart/MT8870
//          https://www.tinytronics.nl/shop/nl/sensoren/geluid/mt8870-dtmf-module


#include "Arduino.h"

#define MT8870_LIB_VERSION          (F("0.1.6"))


class MT8870
{
public:
  //  STQ - pin to see if new data arrived
  //  Q1 - Q4 data pins.
  void     begin(uint8_t STQ, uint8_t Q1, uint8_t Q2, uint8_t Q3, uint8_t Q4);

  bool     available();
  char     read();
  uint8_t  readRaw();
  uint8_t  lastRaw();
  uint32_t lastTimeRead();

private:
  uint8_t   _val = 255;
  uint8_t   _STQ;
  uint8_t   _q[4];
  uint32_t  _lastTimeRead;
};


//  -- END OF FILE --

