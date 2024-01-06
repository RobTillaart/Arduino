#pragma once
//    FILE: PinInGroup.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.10
//    DATE: 2017-04-26
// PURPOSE: PinInGroup library for Arduino
//     URL: https://github.com/RobTillaart/PinInGroup
//
// Note: ESP32 has some dedicated IO pins that cannot be used in a group.
//       FLASH: pin 6 - 11  (maybe more)


#include "Arduino.h"


#define PININGROUP_LIB_VERSION        (F("0.1.10"))


//  smaller MAXSIZE will reduce memory footprint with ditto bytes.
#ifndef PININGROUP_MAXSIZE
#define PININGROUP_MAXSIZE            16
#endif

#define PININGROUP_ERROR_PIN          0xFF


class PinInGroup
{
public:
  PinInGroup();

  //  enables one to reset the pinGroup and repopulate it
  void      clear();


  //  adds a predefined array of pin numbers to the PinInGroup
  //  sets all to either INPUT (default) or INPUT_PULLUP.
  uint8_t   add(uint8_t size, uint8_t * pinArray, uint8_t mode = INPUT);
  //  adds a single pin to the PinInGroup
  uint8_t   add(uint8_t pin, uint8_t mode = INPUT);


  //  counts how often a pin is in the group
  uint8_t   isInGroup(uint8_t pin);
  uint8_t   size()       { return _size; };
  uint8_t   getMaxSize() { return PININGROUP_MAXSIZE; };
  //  check how many "slots" are available
  uint8_t   available()  { return PININGROUP_MAXSIZE - _size; };


  //  read up to 16 pins "simultaneously" in one call.
  uint16_t  read();
  //  read specific index.
  uint16_t  read(uint8_t index);


  uint8_t   getPin(uint8_t index);
  uint8_t   getIndex(uint8_t pin);  //  returns first occurrence!


  //  OBSOLETE in next release
  //  uint8_t   getIdx(uint8_t pin)      { return getIndex(pin); };

private:
  uint8_t   _pins[PININGROUP_MAXSIZE];
  uint8_t   _size = 0;
};


//  -- END OF FILE --

