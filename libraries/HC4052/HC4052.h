#pragma once
//
//    FILE: HC4052.h
//  AUTHOR: Rob Tillaart
//    DATE: 2023-01-25
// VERSION: 0.2.1
// PURPOSE: Arduino library for HC4052 2 x 4 channel multiplexer and compatibles.
//     URL: https://github.com/RobTillaart/HC4052


#include "Arduino.h"

#define HC4052_LIB_VERSION         (F("0.2.1"))


class HC4052
{
public:
  explicit HC4052(uint8_t A, uint8_t B, uint8_t enablePin = 255)
  {
    _pins[0] = A;
    _pins[1] = B;
    uint8_t i = 2;
    while (i--)
    {
      pinMode(_pins[i], OUTPUT);
      digitalWrite(_pins[i], LOW);
    }
    _channel = 0;

    if (enablePin != 255)
    {
      _enablePin = enablePin;
      pinMode(_enablePin, OUTPUT);
      digitalWrite(_enablePin, HIGH);
    }
  }


  bool setChannel(uint8_t channel, bool disable = true)
  {
    if (channel > 3) return false;
    if (channel != _channel)
    {
      if (disable)
      {
        this->disable();  //  prevent ghost channels.
      }
      digitalWrite(_pins[0], channel & 0x01);
      digitalWrite(_pins[1], channel & 0x02);
      enable();
      _channel = channel;
    }
    return true;
  }


  uint8_t getChannel()
  {
    return _channel;
  }


  void enable()
  {
    if (_enablePin != 255)
    {
      digitalWrite(_enablePin, LOW);
    }
  }


  void disable()
  {
    if (_enablePin != 255)
    {
      digitalWrite(_enablePin, HIGH);
    }
  }


  bool isEnabled()
  {
    if (_enablePin != 255)
    {
      return (digitalRead(_enablePin) == LOW);
    }
    return true;
  }


private:
  uint8_t  _pins[3];
  uint8_t  _enablePin = 255;
  uint8_t  _channel   = 0;
};


//  -- END OF FILE --

