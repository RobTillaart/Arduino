#pragma once
//
//    FILE: simon.h
//  AUTHOR: Rob Tillaart
//    DATE: 2022-05-26
// VERSION: 0.1.3
// PURPOSE: Arduino library for SIMON
//     URL: https://github.com/RobTillaart/SIMON


#include "Arduino.h"

#define SIMON_LIB_VERSION        (F("0.1.3"))


#ifndef SIMON_MAXSIZE
#define SIMON_MAXSIZE             10
#endif


class SIMON
{
public:
  SIMON();

  //  returns false if count > max size or array == NULL
  bool    setSequence(uint8_t * array, uint8_t length);
  //  returns true if success.
  bool    generateSequence(uint8_t length, uint8_t minimum, uint8_t maximum);
  //  returns the length of array (which is filled)
  uint8_t getSequence(uint8_t * array);


  //  add next element to answer
  void    add(uint8_t value);
  //  clears the current answer
  void    clear();
  //  check if answer matches the sequence
  bool    verify();
  //  check if array matches the sequence
  bool    verify(uint8_t * array, uint8_t length);


  //  returns the length of the answer so far
  uint8_t length();
  //  returns the size of the "hidden" sequence
  uint8_t size();
  //  returns the maximum size of the "hidden" sequence
  uint8_t maxSize();


private:
  uint8_t _sequence[SIMON_MAXSIZE];
  uint8_t _answer[SIMON_MAXSIZE];
  uint8_t _idx   = 0;      //  how far is the answer filled?
  uint8_t _size  = 0;      //  size of the sequence

  const uint8_t _maxSize = SIMON_MAXSIZE;
};


//  -- END OF FILE --

