#pragma once
//
//    FILE: HX710AB.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.2
// PURPOSE: Arduino library for the HX710A and HX710B 24-Bit ADC.
//    DATE: 2024-11-08
//     URL: https://github.com/RobTillaart/HX710AB
//     URL: https://github.com/RobTillaart/HX711_MP
//     URL: https://github.com/RobTillaart/HX711


#include "Arduino.h"

#define HX710AB_LIB_VERSION              (F("0.2.2"))


//////////////////////////////////////////////////////////////////////////////
//
//  HX710AB BASE CLASS
//
class HX710AB
{
public:
  HX710AB(uint8_t dataPin, uint8_t clockPin)
  {
    _dataPin = dataPin;
    _clockPin = clockPin;
    _value = 0;
    _lastTimeRead = 0;
    _fastProcessor = false;
    _offset = 0;
    _scale = 1;
  };

  void begin(bool fastProcessor = false)
  {
    pinMode(_dataPin, INPUT_PULLUP);
    pinMode(_clockPin, OUTPUT);
    digitalWrite(_clockPin, LOW);
    _fastProcessor = fastProcessor;
  };


  ////////////////////////////////////////////////////
  //
  //  READ
  //
  void request()
  {
    //  force powerUp
    digitalWrite(_clockPin, LOW);
  };

  bool is_ready()
  {
    //  ready == data goes LOW
    return (digitalRead(_dataPin) == LOW);
  };

  //  actual worker.
  virtual int32_t fetch(bool differential = true)
  {
    //  virtual function must have some implementation in base class.
    return differential ? 1 : 0;
  }

  int32_t read(bool differential = true)
  {
    request();
    while (! is_ready()) yield();
    return fetch(differential);
  }

  uint32_t last_time_read()
  {
    return _lastTimeRead;
  }

  uint32_t last_value_read()
  {
    return _value;
  }


  ////////////////////////////////////////////////////
  //
  //  CALIBRATED READ
  //
  float get_units(uint8_t n)
  {
    float x = 0;
    for (int i = 0; i < n; i++)
    {
      x += fetch();
    }
    x /= n;
    return (x - _offset) * _scale;
  }


  ////////////////////////////////////////////////////
  //
  //  TWO POINT CALIBRATION
  //
  //  keep offset scale "compatible" with HX711 library.
  //
  bool calibrate(int32_t x1, float y1, int32_t x2, float y2)
  {
    if ((x1 == x2) || (y2 == y1)) return false;
    _scale = (y2 - y1) / (x2 - x1);
    _offset = x1 - (y1 / _scale);
    return true;
  }

  void set_offset(float offset)
  {
    _offset = offset;
  }

  float get_offset()
  {
    return _offset;
  }

  bool set_scale(float scale)
  {
    if (scale == 0) return false;
    _scale = 1.0 / scale;
    return true;
  }

  float get_scale()
  {
    return 1.0 / _scale;
  }


  ///////////////////////////////////////////////
  //
  //  POWER
  //
  void power_down()
  {
    digitalWrite(_clockPin, HIGH);
  }

  void power_up()
  {
    digitalWrite(_clockPin, LOW);
  }


protected:
  void clock_pulse()
  {
    digitalWrite(_clockPin, HIGH);
    if (_fastProcessor) delayMicroseconds(1);
    digitalWrite(_clockPin, LOW);
    if (_fastProcessor) delayMicroseconds(1);
  }

  uint8_t  _dataPin;
  uint8_t  _clockPin;
  uint32_t _lastTimeRead;
  int32_t  _value;
  bool     _fastProcessor;
  float    _offset;
  float    _scale;
};


//////////////////////////////////////////////////////////////////////////////
//
//  HX710A CLASS
//
class HX710A : public HX710AB
{
public:
  HX710A(uint8_t dataPin, uint8_t clockPin) : HX710AB(dataPin, clockPin)
  {
  }


  int32_t fetch(bool differential = true)
  {
    //  read 24 bits data
    _value = 0;
    for (int i = 0; i < 24; i++)
    {
      clock_pulse();
      _value <<= 1;
      if (digitalRead(_dataPin)) _value++;
    }

    //  pulses for next read
    //  25 = Differential Input, 10 Hz
    //  26 = Temperature, 40 Hz
    clock_pulse();  //  25
    if (differential == false)
    {
      //  Temperature out, 40 Hz
      clock_pulse();  //  26
    }

    _lastTimeRead = millis();
    //  extend sign if needed
    if (_value & 0x800000) _value |= 0xFF000000;
    return _value;
  }

  //  TODO getTemperature()
};


//////////////////////////////////////////////////////////////////////////////
//
//  HX710B CLASS
//
class HX710B : public HX710AB
{
public:
  HX710B(uint8_t dataPin, uint8_t clockPin) : HX710AB(dataPin, clockPin)
  {
  }


  int32_t fetch(bool differential = true)
  {
    //  read 24 bits data
    _value = 0;
    for (int i = 0; i < 24; i++)
    {
      clock_pulse();
      _value <<= 1;
      if (digitalRead(_dataPin)) _value++;
    }

    //  pulses for next read
    //  26 = DVDD-AVDD (HX710B), 40 Hz
    //  27 = Differential Input, 40 Hz
    clock_pulse();  //  25
    clock_pulse();  //  26
    if (differential)
    {
      clock_pulse();  //  27
    }

    _lastTimeRead = millis();
    //  extend sign if needed
    if (_value & 0x800000) _value |= 0xFF000000;
    return _value;
  }

  //  TODO getVoltage()
};


//  -- END OF FILE --

