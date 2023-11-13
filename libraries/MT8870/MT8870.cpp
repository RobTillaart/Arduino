//
//    FILE: MT8870.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.6
//    DATE: 2019-02-11
// PURPOSE: Arduino library for MT8870 DTMF decoder (breakout)
//     URL: https://github.com/RobTillaart/MT8870
//          https://www.tinytronics.nl/shop/nl/sensoren/geluid/mt8870-dtmf-module


#include "MT8870.h"


void MT8870::begin(uint8_t STQ, uint8_t Q1, uint8_t Q2, uint8_t Q3, uint8_t Q4)
{
  _STQ = STQ;
  _q[0] = Q1;
  _q[1] = Q2;
  _q[2] = Q3;
  _q[3] = Q4;
  for (uint8_t p = 0; p < 4; p++)
  {
    pinMode(_q[p], INPUT);    //  PULLUP ?
  }
  pinMode(_STQ, INPUT);
}


bool MT8870::available()
{
  return (digitalRead(_STQ) == HIGH);
}


char MT8870::read()
{
  uint8_t n = readRaw();
  if (n < 16) return "D1234567890*#ABC"[n];
  return 255;
}


uint8_t MT8870::readRaw()
{
  _val = 255;
  if (available())
  {
    _val = 0;
    if (digitalRead(_q[0]) == HIGH) _val += 0x01;
    if (digitalRead(_q[1]) == HIGH) _val += 0x02;
    if (digitalRead(_q[2]) == HIGH) _val += 0x04;
    if (digitalRead(_q[3]) == HIGH) _val += 0x08;
  }
  _lastTimeRead = millis();
  return _val;
}


uint8_t MT8870::lastRaw()
{
  return _val;
};


uint32_t MT8870::lastTimeRead()
{
  return _lastTimeRead;
};


//  -- END OF FILE --

