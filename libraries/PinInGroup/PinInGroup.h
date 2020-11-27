#pragma once
//    FILE: PinInGroup.h
//  AUTHOR: Rob dot Tillaart at gmail dot com
// VERSION: 0.1.2
//    DATE: 2017-04-26
// PURPOSE: PinInGroup library for Arduino
// HISTORY: See PinInGroup.cpp
//
// Note: ESP32 has some dedicated IO pins that cannot be used in a group.
//       FLASH: pin 6 - 11  (maybe more)
//

#include "Arduino.h"

#define PININGROUP_LIB_VERSION "0.1.2"

// smaller MAXSIZE will reduce memory footprint with ditto bytes.
#ifndef PININGROUP_MAXSIZE
#define PININGROUP_MAXSIZE    16
#endif


class PinInGroup
{
  public:
    PinInGroup();

    // enables one to reset the pinGroup and repopulate it
    void      clear();

    // adds a predefined array of pin numbers to the PinInGroup
    // sets all to either INPUT or INPUT_PULLUP.
    uint8_t    add(uint8_t sz, uint8_t * ar, uint8_t value = INPUT);

    // adds a single pin to the PinInGroup
    uint8_t    add(uint8_t pin, uint8_t value = INPUT);

    // read up to 16 pins "simultaneously" in one call.
    uint16_t  read();

    uint8_t   size() {
      return _size;
    };

    // check how many free "slots" there are...
    uint8_t   free() {
      return PININGROUP_MAXSIZE - _size;
    };

  private:
    uint8_t   _pins[PININGROUP_MAXSIZE];
    uint8_t   _size = 0;
};

// -- END OF FILE --
