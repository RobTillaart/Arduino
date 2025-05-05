#pragma once
//
//    FILE: 74HC590.h
//  AUTHOR: Rob Tillaart
//    DATE: 2025-04-30
// VERSION: 0.1.0
// PURPOSE: Arduino library for the 54HC590 / 74HC590 binary counter
//     URL: https://github.com/RobTillaart/74HC590


#include "Arduino.h"

#define LIB_74HC590_VERSION         (F("0.1.0"))



class DEV_74HC590
{
public:
  //  OE      output enable
  //  CCLR    counter clear
  //  CCKEN   counter clock enable
  //  CCLK    counter clock
  //  RCLK    register clock        if set to 255 ==> RCLK == CCLK
  //  RCO     ripple carry out      if set to 255 ==> no RCO (input)
  DEV_74HC590(uint8_t OE, uint8_t CCLR, uint8_t CCKEN, uint8_t CCLK, uint8_t RCLK = 255, uint8_t RCO = 255)
  {
    _OE = OE;
    _CCLR = CCLR;
    _CCKEN = CCKEN;
    _CCLK = CCLK;
    _RCLK = RCLK;
    _RCO = RCO;

    pinMode(_OE,    OUTPUT);
    pinMode(_CCLR,  OUTPUT);
    pinMode(_CCKEN, OUTPUT);
    pinMode(_CCLK,  OUTPUT);
    if (_RCLK != 255) pinMode(_RCLK,  OUTPUT);
    if (_RCO != 255)  pinMode(_RCO,   INPUT);

    digitalWrite(_OE,    LOW);
    digitalWrite(_CCLR,  LOW);
    digitalWrite(_CCKEN, LOW);
    digitalWrite(_CCLK,  LOW);
    if (_RCLK != 255) digitalWrite(_RCLK,  LOW);
  };

  void enableOutput()
  {
    digitalWrite(_OE, LOW);
  };

  void disableOutput()
  {
    digitalWrite(_OE, HIGH);
  };

  //  clears on RISING edge
  void clearCounter()
  {
    digitalWrite(_CCLR, LOW);
    digitalWrite(_CCLR, HIGH);
  };

  void enableCounter()
  {
    digitalWrite(_CCKEN, LOW);
  };

  void disableCounter()
  {
    digitalWrite(_CCKEN, HIGH);
  };

  void pulseCounter()
  {
    digitalWrite(_CCLK, HIGH);
    digitalWrite(_CCLK, LOW);
  };

  void pulseRegister()
  {
    if (_RCLK == 255) return;
    digitalWrite(_RCLK, HIGH);
    digitalWrite(_RCLK, LOW);
  };

  uint8_t readRCO()
  {
    if (_RCO == 255) return 0;
    return digitalRead(_RCO);
  };


protected:
  uint8_t _OE;
  uint8_t _CCLR;
  uint8_t _CCKEN;
  uint8_t _CCLK;
  uint8_t _RCLK;
  uint8_t _RCO;
  };


//  -- END OF FILE --

