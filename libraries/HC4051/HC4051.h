#pragma once
//
//    FILE: HC4051.h
//  AUTHOR: Rob Tillaart
//    DATE: 2023-01-25
// VERSION: 0.3.0
// PURPOSE: Arduino library for CD74HC4051 1 x 8 channel multiplexer and compatibles.
//     URL: https://github.com/RobTillaart/HC4051



#include "Arduino.h"

#define HC4051_LIB_VERSION         (F("0.3.0"))


class HC4051
{
public:
  explicit HC4051(uint8_t A, uint8_t B, uint8_t C, uint8_t enablePin = 255)
  {
    _pins[0] = A;
    _pins[1] = B;
    _pins[2] = C;
    uint8_t i = 3;
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
    if (channel > 7) return false;
    uint8_t _new = channel;
    if (_new != _channel)
    {
      uint8_t _changed = _new ^ _channel;
      uint8_t mask = 0x04;
      uint8_t i = 2;
      if (disable)
      {
        this->disable();  //  prevent ghost channels.
      }
      while (mask)
      {
        //  only write changed pins. //  AVR only?
        if (mask & _changed)
        {
          digitalWrite(_pins[i], (mask & _new));
        }
        i--;
        mask >>= 1;
      }
      enable();
      _channel = _new;
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

