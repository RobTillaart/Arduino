#pragma once
//
//    FILE: HC4053.h
//  AUTHOR: Rob Tillaart
//    DATE: 2023-01-25
// VERSION: 0.2.1
// PURPOSE: Arduino library for CD74HC4053 8 channel multiplexer and compatibles.
//     URL: https://github.com/RobTillaart/HC4053


#include "Arduino.h"

#define HC4053_LIB_VERSION         (F("0.2.1"))


class HC4053
{
public:
  explicit HC4053(uint8_t A, uint8_t B, uint8_t C, uint8_t enablePin = 255)
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
    //  two states only (could be one byte)
    _channelA = 0;
    _channelB = 0;
    _channelC = 0;

    if (enablePin != 255)
    {
      _enablePin = enablePin;
      pinMode(_enablePin, OUTPUT);
      digitalWrite(_enablePin, HIGH);
    }
  }


  bool setChannel(uint8_t channel, bool disable = true)
  {
    if (channel > 1) return false;
    if (disable)
    {
      this->disable();
    }
    setChannelA(channel);
    setChannelB(channel);
    setChannelC(channel);
    enable();
    return true;
  }


  void setChannelA(uint8_t channel)
  {
    if (_channelA != (channel & 0x01))
    {
      _channelA = channel & 0x01;
      digitalWrite(_pins[0], _channelA);
    }
  }


  void setChannelB(uint8_t channel)
  {
    if (_channelB != (channel & 0x01))
    {
      _channelB = channel & 0x01;
      digitalWrite(_pins[1], _channelB);
    }
  }


  void setChannelC(uint8_t channel)
  {
    if (_channelC != (channel & 0x01))
    {
      _channelC = channel & 0x01;
      digitalWrite(_pins[2], _channelC);
    }
  }


  uint8_t getChannelA()
  {
    return _channelA;
  }


  uint8_t getChannelB()
  {
    return _channelB;
  }


  uint8_t getChannelC()
  {
    return _channelC;
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
  uint8_t  _channelA  = 0;
  uint8_t  _channelB  = 0;
  uint8_t  _channelC  = 0;
};


//  -- END OF FILE --

