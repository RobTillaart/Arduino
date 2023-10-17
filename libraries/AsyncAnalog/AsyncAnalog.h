#pragma once
//
//    FILE: AsyncAnalog.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.6
//    DATE: 2018-09-05
// PURPOSE: Async version of analogRead for AVR
//     URL: https://github.com/RobTillaart/AsyncAnalog


#if !defined(ARDUINO_ARCH_AVR)

  #error “AsyncAnalog library only supports boards with an AVR processor .”

#else

// (ARDUINO_ARCH_SAM) future
// (ARDUINO_ARCH_ESP32) future
// (ARDUINO_ARCH_ESP8266) future


#include "Arduino.h"
#include "wiring_private.h"
#include "pins_arduino.h"

#define ASYNCANALOG_LIB_VERSION       (F("0.1.6"))


class AsyncAnalog
{
public:
  AsyncAnalog(const uint8_t pin);

  void start();
  bool ready();
  int  value();

private:
  uint8_t  _pin;
  //  uint16_t _lastValue;
};

#endif  //  defined(ARDUINO_ARCH_AVR)


//  -- END OF FILE --
