#pragma once
//
//    FILE: ADG732.h
//  AUTHOR: Rob Tillaart
//    DATE: 2023-07-24
// VERSION: 0.1.2
// PURPOSE: Arduino library for ADG732 - 32 to 1 channel multiplexer
//     URL: https://github.com/RobTillaart/ADG732


#include "Arduino.h"

#define ADG732_LIB_VERSION         (F("0.1.2"))

#define ADG732_ALLOFF              0x80


class ADG732
{
public:
  ADG732(uint8_t A, uint8_t B, uint8_t C, uint8_t D, uint8_t E, uint8_t CS, uint8_t EN, uint8_t WR)
  {
    uint8_t arr[5] = { A, B, C, D, E };
    ADG732(arr, CS, EN, WR);
  }

  explicit ADG732(uint8_t address[5], uint8_t CS, uint8_t EN, uint8_t WR)
  {
    for (int i = 0; i < 5; i++)
    {
      _addr[i] = address[i];
      pinMode(_addr[i], OUTPUT);
      digitalWrite(_addr[i], LOW);
    }

    _CS = CS;
    _EN = EN;
    _WR = WR;
    pinMode(_CS, OUTPUT);
    pinMode(_EN, OUTPUT);
    pinMode(_WR, OUTPUT);

    digitalWrite(_CS, HIGH);
    digitalWrite(_EN, HIGH);
    digitalWrite(_WR, HIGH);

    //  default all off.
    _channel = ADG732_ALLOFF;
  }


  void setChannel(uint8_t channel)
  {
    _channel = channel & 0x1F;
    write(_channel, LOW);
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
    _channel = ADG732_ALLOFF;
    write(_channel, HIGH);
  }


private:
  void write(uint8_t data, uint8_t en)
  {
    digitalWrite(_CS, LOW);
    digitalWrite(_WR, LOW);

    digitalWrite(_EN, en);
    if (en == LOW)
    {
      uint8_t mask = 0x01;
      for (int i = 0; i < 5; i++)
      {
        digitalWrite(_addr[i], ((data & mask) > 0));
        mask <<= 1;
      }
      digitalWrite(_EN, HIGH);
    }

    digitalWrite(_WR, HIGH);
    digitalWrite(_CS, HIGH);
  }

  uint8_t  _addr[5];
  uint8_t  _CS;
  uint8_t  _EN;
  uint8_t  _WR;
  uint8_t  _channel;
};


//  -- END OF FILE --

