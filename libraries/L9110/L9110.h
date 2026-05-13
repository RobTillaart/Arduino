#pragma once
//
//    FILE: L9110.h
//  AUTHOR: Rob Tillaart
//    DATE: 2025-09-08
// VERSION: 0.1.1
// PURPOSE: Arduino library for L9110 motor driver.
//     URL: https://github.com/RobTillaart/L9110
//
//  Motor driver chip on de propeller
//  TEXT ON CHIP: L9110H, AU1951AZ


#include "Arduino.h"

#define L9110_LIB_VERSION         (F("0.1.1"))


constexpr uint8_t L9110_STOP    = 0x00;
constexpr uint8_t L9110_REVERSE = 0x01;
constexpr uint8_t L9110_FORWARD = 0x02;


class L9110
{
public:
  L9110(uint8_t forwardPin, uint8_t reversePin)
  {
    _fwdPin = forwardPin;
    _revPin = reversePin;
  }

  void begin()
  {
    pinMode(_fwdPin, OUTPUT);
    pinMode(_revPin, OUTPUT);
    digitalWrite(_fwdPin, LOW);
    digitalWrite(_revPin, LOW);
  }

  void swapPins()
  {
    digitalWrite(_fwdPin, LOW);
    digitalWrite(_revPin, LOW);
    uint8_t tmp = _fwdPin;
    _fwdPin = _revPin;
    _revPin = tmp;
  }

  void forward()
  {
    digitalWrite(_revPin, LOW);
    if (_delay) delayMicroseconds(_delay);
    digitalWrite(_fwdPin, HIGH);
  }

  void reverse()
  {
    digitalWrite(_fwdPin, LOW);
    if (_delay) delayMicroseconds(_delay);
    digitalWrite(_revPin, HIGH);
  }

  void stop()
  {
    digitalWrite(_fwdPin, LOW);
    digitalWrite(_revPin, LOW);
  }

  uint8_t status()
  {
    uint8_t status = digitalRead(_revPin) << 1;
    status |= digitalRead(_fwdPin);
    if (status == 0x03) status = L9110_STOP;
    return status;
  }

  void setMicroDelay(uint16_t del = 20)
  {
    _delay = del;
  }

  uint16_t getMicroDelay()
  {
    return _delay;
  }


protected:
  uint8_t _fwdPin;
  uint8_t _revPin;
  uint16_t _delay = 20;
};


class HG7881 : public L9110
{
public:
  HG7881(uint8_t forwardPin, uint8_t reversePin) : L9110(forwardPin, reversePin)
  {
  }
};

//  -- END OF FILE --

