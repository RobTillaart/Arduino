#pragma once
//    FILE: PinInGroup.h
//  AUTHOR: Rob dot Tillaart at gmail dot com
// VERSION: 0.1.4
//    DATE: 2017-04-26
// PURPOSE: PinInGroup library for Arduino
// HISTORY: See PinInGroup.cpp
//
// Note: ESP32 has some dedicated IO pins that cannot be used in a group.
//       FLASH: pin 6 - 11  (maybe more)


#include "Arduino.h"


#define PININGROUP_LIB_VERSION      (F("0.1.4"))


// smaller MAXSIZE will reduce memory footprint with ditto bytes.
#ifndef PININGROUP_MAXSIZE
#define PININGROUP_MAXSIZE          16
#endif


class PinInGroup
{
public:
  PinInGroup();

  // enables one to reset the pinGroup and repopulate it
  void      clear();

  // adds a predefined array of pin numbers to the PinInGroup
  // sets all to either INPUT (default) or INPUT_PULLUP.
  uint8_t    add(uint8_t sz, uint8_t * ar, uint8_t mode = INPUT);
  // adds a single pin to the PinInGroup
  uint8_t    add(uint8_t pin, uint8_t mode = INPUT);

  // counts how often a pin is in the group
  uint8_t    isInGroup(uint8_t pin);

  // read up to 16 pins "simultaneously" in one call.
  uint16_t  read();

  // read specific index.
  uint16_t  read(uint8_t idx);

  uint8_t   size() { return _size; };

  // check how many "slots" are available
  uint8_t   available() { return PININGROUP_MAXSIZE - _size; };

  uint8_t   getPin(uint8_t idx);
  uint8_t   getIdx(uint8_t pin);

private:
  uint8_t   _pins[PININGROUP_MAXSIZE];
  uint8_t   _size = 0;
};

// -- END OF FILE --
