#pragma once
//    FILE: PinOutGroup.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.8
//    DATE: 2017-04-26
// PURPOSE: PinOutGroup library for Arduino
//     URL: https://github.com/RobTillaart/PinOutGroup


#include "Arduino.h"


#define PINOUTGROUP_LIB_VERSION         (F("0.1.8"))


//  smaller MAXSIZE will reduce memory footprint with ditto bytes.
#ifndef PINOUTGROUP_MAXSIZE
#define PINOUTGROUP_MAXSIZE            16
#endif


#define PINOUTGROUP_ERROR_PIN          0xFF


class PinOutGroup
{
public:
  PinOutGroup();

  //  enables one to reset at he pinGroup and repopulate it
  void      clear();

  //  adds a predefined array of pin numbers to the PinOutGroup
  //  sets all to (LOW, HIGH)
  uint8_t   add(uint8_t size, uint8_t* pinArray, uint8_t value = LOW);
  //  adds a single pin to the PinOutGroup, default to LOW.
  uint8_t   add(uint8_t pin, uint8_t value = LOW);

  //  returns count of pin in the group => only 0 or 1 makes sense
  uint8_t   isInGroup(uint8_t pin);

  //  set up to 16 pins "simultaneously" in one call.
  uint8_t   write(uint16_t value);
  //  write to a single pin while maintaining internal admin
  uint8_t   write(uint8_t index, uint8_t value);
  void      allLOW();
  void      allHIGH();

  //  retrieve the last set value
  uint16_t  read() { return _lastValue; };

  uint8_t   size() { return _size; };
  //  check how many free "slots" there are...
  uint8_t   available() { return PINOUTGROUP_MAXSIZE - _size; };
  uint8_t   getMaxSize() { return PINOUTGROUP_MAXSIZE; };

  uint8_t   getPin(uint8_t index);
  uint8_t   getIndex(uint8_t pin);

  //  obsolete
  //  uint8_t   getIdx(uint8_t pin) { return getIndex(pin); };


private:
  uint16_t  _lastValue = 0;
  uint8_t   _pins[PINOUTGROUP_MAXSIZE];
  uint8_t   _size = 0;
};


//  -- END OF FILE --

