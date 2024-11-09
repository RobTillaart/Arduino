#pragma once
//
//    FILE: HX710AB.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: Arduino library for the HX710A and HX710B 24-Bit ADC.
//    DATE: 2024-11-08
//     URL: https://github.com/RobTillaart/HX710AB


#include "Arduino.h"

#define HX710AB_LIB_VERSION              (F("0.1.0"))


///////////////////////////////////////
//
//  HX710A CLASS
//
class HX710A
{
public:
  HX710A(uint8_t dataPin, uint8_t clockPin)
  {
    _data = dataPin;
    _clock = clockPin;
    _value = 0;
  }


  void begin()
  {
    pinMode(_data, INPUT);
    pinMode(_clock, OUTPUT);
    digitalWrite(_clock, LOW);
  }


  int32_t read(bool differential = true)
  {
    //  force powerUp
    digitalWrite(_clock, LOW);

    //  blocking wait for data goes LOW
    while (digitalRead(_data))
    {
      yield();
    };

    //  read 24 bits data
    _value = 0;
    for (int i = 0; i < 24; i++) 
    {
      digitalWrite(_clock, HIGH);
      _value <<= 1;
      digitalWrite(_clock, LOW);
      if (digitalRead(_data)) _value++;
    }

    //  pulses for next read
    //  25 = Differential Input, 10 Hz
    //  26 = Temperature, 40 Hz
    digitalWrite(_clock, HIGH);
    digitalWrite(_clock, LOW);
    if (differential == false)
    {
      //  Temperature out, 40 Hz
      digitalWrite(_clock, HIGH);
      digitalWrite(_clock, LOW);
    }

    //  extend sign if needed
    if (_value & 0x800000) _value |= 0xFF000000;
    return _value;
  }


  int32_t lastRead()
  {
    return _value;
  };


  void powerDown()
  {
    digitalWrite(_clock, HIGH);
  };


  void powerUp()
  {
    digitalWrite(_clock, LOW);
  };


protected:
  uint8_t _data;
  uint8_t _clock;
  int32_t _value;
};



///////////////////////////////////////
//
//  HX710B CLASS
//
class HX710B
{
public:
  HX710B(uint8_t dataPin, uint8_t clockPin)
  {
    _data = dataPin;
    _clock = clockPin;
    _value = 0;
  }


  void begin()
  {
    pinMode(_data, INPUT);
    pinMode(_clock, OUTPUT);
    digitalWrite(_clock, LOW);
  }


  int32_t read(bool differential = true)
  {
    //  force powerUp
    digitalWrite(_clock, LOW);

    //  blocking wait for data goes LOW
    while (digitalRead(_data))
    {
      yield();
    };

    //  read 24 bits data
    _value = 0;
    for (int i = 0; i < 24; i++) 
    {
      digitalWrite(_clock, HIGH);
      digitalWrite(_clock, LOW);
      _value <<= 1;
      if (digitalRead(_data)) _value++;
    }

    //  pulses for next read
    //  26 = DVDD-AVDD (HX710B), 40 Hz
    //  27 = Differential Input, 40 Hz
    digitalWrite(_clock, HIGH);
    digitalWrite(_clock, LOW);
    digitalWrite(_clock, HIGH);
    digitalWrite(_clock, LOW);
    if (differential)
    {
      digitalWrite(_clock, HIGH);
      digitalWrite(_clock, LOW);
    }

    //  extend sign if needed
    if (_value & 0x800000) _value |= 0xFF000000;
    return _value;
  }


  int32_t lastRead()
  {
    return _value;
  };


  void powerDown()
  {
    digitalWrite(_clock, HIGH);
  };


  void powerUp()
  {
    digitalWrite(_clock, LOW);
  };
  

protected:
  uint8_t _data;
  uint8_t _clock;
  int32_t _value;
};


//  -- END OF FILE --

