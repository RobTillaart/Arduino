#pragma once
//    FILE: PinOutGroup.h
//  AUTHOR: Rob dot Tillaart at gmail dot com
// VERSION: 0.1.2
//    DATE: 2017-04-26
// PURPOSE: PinOutGroup library for Arduino
// HISTORY: See PinOutGroup.cpp
//

#include "Arduino.h"

#define PINOUTGROUP_LIB_VERSION "0.1.2"

// smaller MAXSIZE will reduce memory footprint with ditto bytes.
#ifndef PINOUTGROUP_MAXSIZE
#define PINOUTGROUP_MAXSIZE    16
#endif           


class PinOutGroup
{
public:
  PinOutGroup();
  
  // enables one to reset at he pinGroup and repopulate it
  void      clear();

  // adds a predefined array of pin numbers to the PinOutGroup
  // sets all to (LOW, HIGH)
  bool      add(uint8_t sz, uint8_t* ar, uint8_t value = LOW);
  
  // adds a single pin to the PinOutGroup, default to LOW.
  bool      add(uint8_t pin, uint8_t value = LOW);

  // set up to 16 pins "simultaneously" in one call.
  uint8_t   write(uint16_t value);
  
  // write to a single pin while maintaining internal admin
  uint8_t   write(uint8_t idx, uint8_t value);
  
  // retrieve the last set value
  uint16_t  read() { return _lastValue; };

  uint8_t   size() { return _size; };

  // check how many free "slots" there are...
  uint8_t   free() { return PINOUTGROUP_MAXSIZE - _size; };

private:
  uint16_t  _lastValue = 0;
  uint8_t   _pins[PINOUTGROUP_MAXSIZE];
  uint8_t   _size = 0;
};

// -- END OF FILE --
