#pragma once
//
//    FILE: HX710AB.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
// PURPOSE: Arduino library for the HX710A and HX710B 24-Bit ADC.
//    DATE: 2024-11-08
//     URL: https://github.com/RobTillaart/HX710AB
//     URL: https://github.com/RobTillaart/HX711_MP
//     URL: https://github.com/RobTillaart/HX711


#include "Arduino.h"

#define HX710AB_LIB_VERSION              (F("0.1.1"))


///////////////////////////////////////
//
//  HX710A CLASS
//
class HX710A
{
public:
  HX710A(uint8_t dataPin, uint8_t clockPin)
  {
    _dataPin = dataPin;
    _clockPin = clockPin;
    _value = 0;
    _lastTimeRead = 0;
    _fastProcessor = false;
  }


  void begin(bool fastProcessor = false)
  {
    pinMode(_dataPin, INPUT);
    pinMode(_clockPin, OUTPUT);
    digitalWrite(_clockPin, LOW);
    _fastProcessor = fastProcessor;
  }


  int32_t read(bool differential = true)
  {
    //  force powerUp
    digitalWrite(_clockPin, LOW);

    //  blocking wait for data goes LOW
    while (digitalRead(_dataPin))
    {
      yield();
    };

    //  read 24 bits data
    _value = 0;
    for (int i = 0; i < 24; i++) 
    {
      clockPulse();
      _value <<= 1;
      if (digitalRead(_dataPin)) _value++;
    }

    //  pulses for next read
    //  25 = Differential Input, 10 Hz
    //  26 = Temperature, 40 Hz
    clockPulse();  //  25
    if (differential == false)
    {
      //  Temperature out, 40 Hz
      clockPulse();  //  26
    }

    _lastTimeRead = millis();
    //  extend sign if needed
    if (_value & 0x800000) _value |= 0xFF000000;
    return _value;
  }


  uint32_t lastTimeRead()
  {
    return _lastTimeRead;
  };


  void powerDown()
  {
    digitalWrite(_clockPin, HIGH);
  };


  void powerUp()
  {
    digitalWrite(_clockPin, LOW);
  };


protected:
  void clockPulse()
  {
    digitalWrite(_clockPin, HIGH);
    if (_fastProcessor) delayMicroseconds(1);
    digitalWrite(_clockPin, LOW);
    if (_fastProcessor) delayMicroseconds(1);
  };

  uint8_t  _dataPin;
  uint8_t  _clockPin;
  uint32_t _lastTimeRead;
  int32_t  _value;
  bool     _fastProcessor;
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
    _dataPin = dataPin;
    _clockPin = clockPin;
    _value = 0;
    _lastTimeRead = 0;
    _fastProcessor = false;
  }


  void begin(bool fastProcessor = false)
  {
    pinMode(_dataPin, INPUT);
    pinMode(_clockPin, OUTPUT);
    digitalWrite(_clockPin, LOW);
    _fastProcessor = fastProcessor;
  }


  int32_t read(bool differential = true)
  {
    //  force powerUp
    digitalWrite(_clockPin, LOW);

    //  blocking wait for data goes LOW
    while (digitalRead(_dataPin))
    {
      yield();
    };

    //  read 24 bits data
    _value = 0;
    for (int i = 0; i < 24; i++) 
    {
      clockPulse();
      _value <<= 1;
      if (digitalRead(_dataPin)) _value++;
    }

    //  pulses for next read
    //  26 = DVDD-AVDD (HX710B), 40 Hz
    //  27 = Differential Input, 40 Hz
    clockPulse();  //  25
    clockPulse();  //  26
    if (differential)
    {
      clockPulse();  //  27
    }

    _lastTimeRead = millis();
    //  extend sign if needed
    if (_value & 0x800000) _value |= 0xFF000000;
    return _value;
  }


  uint32_t lastTimeRead()
  {
    return _lastTimeRead;
  };


  uint32_t lastValueRead()
  {
    return _value;
  };


  void powerDown()
  {
    digitalWrite(_clockPin, HIGH);
  };


  void powerUp()
  {
    digitalWrite(_clockPin, LOW);
  };
  

protected:
  void clockPulse()
  {
    digitalWrite(_clockPin, HIGH);
    if (_fastProcessor) delayMicroseconds(1);
    digitalWrite(_clockPin, LOW);
    if (_fastProcessor) delayMicroseconds(1);
  };

  uint8_t  _dataPin;
  uint8_t  _clockPin;
  uint32_t _lastTimeRead;
  int32_t  _value;
  bool     _fastProcessor;
};


/*
///////////////////////////////////////
//
//  HX710B CLASS
//
class HX710B_ASYNC
{
public:
  HX710B_ASYNC(uint8_t dataPin, uint8_t clockPin)
  {
    _dataPin = dataPin;
    _clockPin = clockPin;
    _value = 0;
    _lastTimeRead = 0;
    _fastProcessor = false;
  }


  void begin(bool fastProcessor = false)
  {
    pinMode(_dataPin, INPUT);
    pinMode(_clockPin, OUTPUT);
    digitalWrite(_clockPin, LOW);
    _fastProcessor = fastProcessor;
  }


  void request()
  {
    //  force powerUp
    digitalWrite(_clockPin, LOW);
  }

  bool isReady()
  {
    //  ready == data goes LOW
    return (digitalRead(_dataPin) == LOW);
  }

  int32_t fetch(bool differential = true)
  {
    //  read 24 bits data
    _value = 0;
    for (int i = 0; i < 24; i++) 
    {
      clockPulse();
      _value <<= 1;
      if (digitalRead(_dataPin)) _value++;
    }

    //  pulses for next read
    //  26 = DVDD-AVDD (HX710B), 40 Hz
    //  27 = Differential Input, 40 Hz
    clockPulse();  //  25
    clockPulse();  //  26
    if (differential)
    {
      clockPulse();  //  27
    }

    _lastTimeRead = millis();
    //  extend sign if needed
    if (_value & 0x800000) _value |= 0xFF000000;
    return _value;
  }


  int32_t read(bool differential = true)
  {
    request();
    while (! isReady()) yield();
    return fetch(differential);
  }


  uint32_t lastTimeRead()
  {
    return _lastTimeRead;
  };


  uint32_t lastValueRead()
  {
    return _value;
  };


  void powerDown()
  {
    digitalWrite(_clockPin, HIGH);
  };


  void powerUp()
  {
    digitalWrite(_clockPin, LOW);
  };
  

protected:
  void clockPulse()
  {
    digitalWrite(_clockPin, HIGH);
    if (_fastProcessor) delayMicroseconds(1);
    digitalWrite(_clockPin, LOW);
    if (_fastProcessor) delayMicroseconds(1);
  };

  uint8_t  _dataPin;
  uint8_t  _clockPin;
  uint32_t _lastTimeRead;
  int32_t  _value;
  bool     _fastProcessor;
};
*/


//  -- END OF FILE --

