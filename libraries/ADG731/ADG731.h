#pragma once
//
//    FILE: ADG731.h
//  AUTHOR: Rob Tillaart
//    DATE: 2023-07-24
// VERSION: 0.1.2
// PURPOSE: Arduino library for ADG731 - 32 to 1 channel multiplexer
//     URL: https://github.com/RobTillaart/ADG731


#include "Arduino.h"

#define ADG731_LIB_VERSION         (F("0.1.2"))

#define ADG731_ALLOFF              0x80


class ADG731
{
public:
  explicit ADG731(uint8_t clockPin, uint8_t dataPin, uint8_t syncPin)
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
    _channel = ADG731_ALLOFF;
  }


  void setChannel(uint8_t channel)
  {
    _channel = channel & 0x1F;
    write(_channel);
  }


  uint8_t getChannel()
  {
    return _channel;
  }


  uint8_t channelCount()
  {
    return 32;
  }


  void allOff()
  {
    _channel = ADG731_ALLOFF;
    write(_channel);
  }


private:
  void write(uint8_t data)
  {
    digitalWrite(_syncPin, LOW);
    for (int i = 0; i < 8; i++)
    {
      //  CLOCK max 30 MHz.
      digitalWrite(_clockPin, HIGH);
      digitalWrite(_dataPin, (data & 0x80) > 0);
      data <<= 1;
      digitalWrite(_clockPin, LOW);
    }
    digitalWrite(_syncPin, HIGH);
  }

  uint8_t  _clockPin;
  uint8_t  _dataPin;
  uint8_t  _syncPin;
  uint8_t  _channel;
};


//  -- END OF FILE --
