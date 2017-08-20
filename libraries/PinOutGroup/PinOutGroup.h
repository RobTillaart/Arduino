#ifndef PINOUTGROUP_H
//    FILE: PinOutGroup.h
//  AUTHOR: Rob dot Tillaart at gmail dot com
// VERSION: 0.1.0
// PURPOSE: PinOutGroup library for Arduino
// HISTORY: See pinGroup.cpp
//
// Released to the public domain
//
#include "Arduino.h"

#define PINOUTGROUP_LIB_VERSION "0.1.0"

// PINOUTGROUP_MAXSIZE = 16 ==> max value, smaller will reduce memory footprint with ditto bytes.
#define PINOUTGROUP_MAXSIZE      16             

//
// a pinGroup is a number of output pins that can be set by means of
// one set command. The pinGroup remembers the last set value per pin
// and will not do a digitalWrite() if the pin is already in the right
// state. If a pin is updated often this can save some cpu cycles
// however this feature has some overhead which is contra productive
// when you toggle a group of pins. So use with care.
//
// <performance intermezzo>
// On average 50% of the pins are in the right state (assumption) 
// This means that of a set only half the pins are changed, so 50%
// is the maximum theoretical gain we see on average.
// In testruns a gain of 20-25% is seen but this really depends on
// the data used. 
// 
class PinOutGroup
{
public:
  PinOutGroup();
  
  // adds a predefined array of pinnumbers to the PinOutGroup
  // sets all to (LOW, HIGH)
  bool      add(uint8_t s, int* ar, uint8_t value = LOW);
  // adds a single pin to the PinOutGroup, default to LOW.
  bool      add(uint8_t pin, uint8_t value = LOW);

  // set up to 16 pins "simultaneously" in one call.
  uint8_t   set(uint16_t value);
  // retrieve the last set value
  uint16_t  get() { return _lastValue; };
  // get the current size
  uint8_t   size() { return _size; };
  // check how many free "slots" there are...
  uint8_t   free() { return PINOUTGROUP_MAXSIZE - _size; };

private:
  uint16_t  _lastValue = 0;
  uint8_t   _pins[PINOUTGROUP_MAXSIZE];    // should be malloced dynamically
  uint8_t   _size = 0;
};
#endif
