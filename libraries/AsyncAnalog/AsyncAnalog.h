#pragma once
//
//    FILE: AsyncAnalog.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.0
//    DATE: 2018-09-05
// PURPOSE: Async version of analogRead for AVR
//     URL: https://github.com/RobTillaart/AsyncAnalog


#define ASYNCANALOG_LIB_VERSION       (F("0.2.0"))


#if defined(ARDUINO_ARCH_AVR)


#include "Arduino.h"
#include "wiring_private.h"
#include "pins_arduino.h"


class AsyncAnalog
{
public:
  AsyncAnalog(const uint8_t pin);

  void      start();
  bool      ready();
  uint16_t  value();

private:
  uint8_t  _pin;
  uint16_t _lastValue;
};

// #elif defined(ARDUINO_ARCH_SAM)
// #elif defined(ARDUINO_ARCH_ESP32)
// #elif defined(ARDUINO_ARCH_ESP8266)


#else

#error “AsyncAnalog library only supports boards with an AVR processor .”


/*
#include "Arduino.h"

//  fall back for other platforms?

class AsyncAnalog
{
public:
  AsyncAnalog(const uint8_t pin)
  {
    _pin = pin;
    _lastValue = 0;
  }

  void      start() { _lastValue = analogRead(_pin); };
  bool      ready() { return true; };
  uint16_t  value() { return _lastValue; };

private:
  uint8_t  _pin;
  uint16_t _lastValue;
};
*/


#endif  //  defined(ARDUINO_ARCH_AVR)


//  -- END OF FILE --
