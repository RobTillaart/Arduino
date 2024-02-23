#pragma once
//
//    FILE: 74HC138.h
//  AUTHOR: Rob Tillaart
//    DATE: 2024-02-22
// VERSION: 0.1.0
// PURPOSE: Arduino library for the 74HC138 3-to-8 line decoder/demultiplexer.
//     URL: https://github.com/RobTillaart/74HC138


#include "Arduino.h"

#define LIB_74HC138_VERSION         (F("0.1.0"))



class DEV_74HC138
{
public:
  DEV_74HC138(uint8_t pin0, uint8_t pin1, uint8_t pin2, uint8_t pinEnable = 255)
  {
    _pin[0] = pin0;
    _pin[1] = pin1;
    _pin[2] = pin2;
    _enable = pinEnable;
    _line = 0;

    for (int i = 0; i < 3; i++)
    {
      pinMode(_pin[i], OUTPUT);
      digitalWrite(_pin[i], LOW);
    }
    if (pinEnable != 255)
    {
      //  default disable.
      pinMode(_enable, OUTPUT);
      digitalWrite(_enable, HIGH);
    }
  }

  DEV_74HC138(uint8_t * pins, uint8_t pinEnable = 255)
  {
    _line = 0;
    for (int i = 0; i < 3; i++)
    {
      _pin[i] = pins[i];
      pinMode(_pin[i], OUTPUT);
      digitalWrite(_pin[i], LOW);
    }
    if (pinEnable != 255)
    {
      //  default disable.
      pinMode(_enable, OUTPUT);
      digitalWrite(_enable, HIGH);
    }
  }

  //  nr == 0..7
  bool setLine(uint8_t nr)
  {
    if (nr > 7) return false;
    _line = nr;
    _setLine();
    return true;
  }

  uint8_t getLine()
  {
    return _line;
  }

  void nextLine()
  {
    if (_line >= 7) _line = 0;
    else _line++;
    _setLine();
  }

  void prevLine()
  {
    if (_line == 0) _line = 7;
    else _line--;
    _setLine();
  }

  void enable()
  {
    digitalWrite(_enable, LOW);
  }

  void disable()
  {
    digitalWrite(_enable, HIGH);
  }

  bool isEnabled()
  {
    return digitalRead(_enable);
  }


private:
  uint8_t _pin[3];
  uint8_t _enable = 255;
  uint8_t _line = 0;

  void _setLine()
  {
    digitalWrite(_pin[0], _line & 0x01);
    digitalWrite(_pin[1], _line & 0x02);
    digitalWrite(_pin[2], _line & 0x04);
  }

/*
  uint8_t getLine()
  {
    uint8_t val = digitalRead(_pin[0]);
    val |= digitalRead(_pin[1]) << 1;
    val |= digitalRead(_pin[2]) << 2;
    return val;
  };
*/

};


//  -- END OF FILE --

