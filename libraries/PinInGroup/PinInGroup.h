#ifndef PININGROUP_H
//    FILE: PinInGroup.h
//  AUTHOR: Rob dot Tillaart at gmail dot com
// VERSION: 0.1.0
// PURPOSE: PinInGroup library for Arduino
// HISTORY: See PinInGroup.cpp
//
// Released to the public domain
//
#include "Arduino.h"

#define PININGROUP_LIB_VERSION "0.1.0"
#define PININGROUP_MAXSIZE      16

//
// a PinInGroup is a group of up to sixteen input pins that can be read 
// by means of one read command and combined into one uint16_t.
// 
class PinInGroup
{
public:
  PinInGroup();
  
  // adds a predefined array of pinnumbers to the PinInGroup
  bool      add(uint8_t s, int* ar);
  // adds a single pin to the PinInGroup
  bool      add(uint8_t pin);

  // read up to 8 pins "simultaneously" into one byte.
  uint16_t   read();

  // get the current size of the PinInGroup.
  uint8_t   size() { return _size; };
  // check how many free slots there are...
  uint8_t   free() { return PININGROUP_MAXSIZE - _size; };
  
private:
  uint8_t   _pins[PININGROUP_MAXSIZE];    // should be malloced dynamically
  uint8_t   _size = 0;
};
#endif
