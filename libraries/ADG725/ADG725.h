#pragma once
//
//    FILE: ADG725.h
//  AUTHOR: Rob Tillaart
//    DATE: 2023-07-24
// VERSION: 0.1.2
// PURPOSE: Arduino library for ADG725 - 16 to 1 channel (2x) multiplexer
//     URL: https://github.com/RobTillaart/ADG725


#include "Arduino.h"

#define ADG725_LIB_VERSION         (F("0.1.2"))

#define ADG725_ALLOFF              0x80    //  ENable bit (false)
#define ADG725_A_ONLY              0x20    //  retain B
#define ADG725_B_ONLY              0x40    //  retain A
#define ADG725_AB_BOTH             0x00    //  retain none


class ADG725
{
public:
  explicit ADG725(uint8_t clockPin, uint8_t dataPin, uint8_t syncPin)
  {
    _clockPin = clockPin;
    _dataPin  = dataPin;
    _syncPin  = syncPin;

    pinMode(_clockPin, OUTPUT);
    pinMode(_dataPin, OUTPUT);
    pinMode(_syncPin, OUTPUT);

    digitalWrite(_clockPin, HIGH);
    digitalWrite(_dataPin, HIGH);
    digitalWrite(_syncPin, HIGH);

    //  default all off.
    _channelA = ADG725_ALLOFF;
    _channelB = ADG725_ALLOFF;
  }

  //  set both channels
  void setChannel(uint8_t channel)
  {
    _channelA = channel & 0x0F;
    uint8_t data = ADG725_AB_BOTH | _channelA;
    _channelB = _channelA;
    write(data);
  }

  void setChannelA(uint8_t channel)
  {
    _channelA = channel & 0x0F;
    uint8_t data = ADG725_A_ONLY | _channelA;
    write(data);
  }

  void setChannelB(uint8_t channel)
  {
    _channelB = channel & 0x0F;
    uint8_t data = ADG725_B_ONLY | _channelB;
    write(data);
  }

  //  last set channel
  uint8_t getChannelA()
  {
    return _channelA;
  }


  uint8_t getChannelB()
  {
    return _channelB;
  }


  uint8_t channelCount()
  {
    return 16;
  }


  void allOff()
  {
    _channelA = ADG725_ALLOFF;
    _channelB = _channelA;
    write(_channelA);
  }


private:
  void write(uint8_t data)
  {
    uint8_t cl = _clockPin;
    uint8_t da = _dataPin;
    digitalWrite(_syncPin, LOW);
    for (int i = 0; i < 8; i++)
    {
      //  CLOCK max 30 MHz.
      digitalWrite(cl, HIGH);
      //  MSB first
      digitalWrite(da, (data & 0x80) > 0);
      data <<= 1;
      digitalWrite(cl, LOW);
    }
    digitalWrite(_syncPin, HIGH);
  }

  uint8_t  _clockPin;
  uint8_t  _dataPin;
  uint8_t  _syncPin;
  uint8_t  _channelA;
  uint8_t  _channelB;
};


//  -- END OF FILE --
