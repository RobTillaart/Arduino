#pragma once
//
//    FILE: DEVRANDOM.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.2
// PURPOSE: Arduino library for a /dev/random stream - usefull for testing
//     URL: https://github.com/RobTillaart/DEVRANDOM
//
//  HISTORY:
//  0.1.0   2020-06-23  initial version
//  0.1.1   2020-12-18  add arduino-ci + unit tests
//                      + getMode() + flush()
//  0.1.2   2021-01-15  add constructors with seed.


#include "Arduino.h"


#define  DEVRANDOM_LIB_VERSION      (F("0.1.2"))


#define  DEVRANDOM_MODE_SW           0
#define  DEVRANDOM_MODE_HW           1
#define  DEVRANDOM_MODE_AR           2


class DEVRANDOM : public Stream
{
public:
  DEVRANDOM()
  {
    _seed = 0;
    _next = random(256);
    _mode = 0;
    _pin = 0;
  };

  DEVRANDOM(const char * str)
  {
    this->print(str);
    _next = random(256);
    _mode = 0;
    _pin = 0;
  };

  DEVRANDOM(const uint32_t val)
  {
     this->print(val);
    _next = random(256);
    _mode = 0;
    _pin = 0;
  };

  DEVRANDOM(const float val)
  {
    this->print(val, 6);
    _next = random(256);
    _mode = 0;
    _pin = 0;
  };


  int available() { return 1; };


  int peek()      { return _next; };
  int read()      
  {
    uint8_t x = _next;
    _next = _rnd();
    return x;
  };


  // keep CI happy as parent class flush is virtual.
  void flush() {};  


  size_t write(const uint8_t data)
  {
    _seed = (_seed << 8) + data;
    randomSeed(_seed);
    return 1;
  };


  void useAR(uint8_t pin) { _mode = 2; _pin = pin; };
  void useHW(uint8_t pin) { _mode = 1; _pin = pin; pinMode(_pin, INPUT); };
  void useSW()            { _mode = 0; };


  uint8_t getMode() { return _mode; };


private:
  uint8_t  _next;
  uint32_t _seed;
  uint8_t  _mode;
  uint8_t  _pin;


  int _rnd()
  {
    if (_mode == 0 ) return random(256);
    if (_mode == 1 ) return _hardware();
    if (_mode == 2 ) return _analog();
    return 0;
  }


  int _hardware()
  {
    uint8_t val = 0;
    for (uint8_t i = 0; i < 8; i++)
    {
      val <<= 1;
      // TODO register optimized read for speed? ==> Not portable
      if (digitalRead(_pin)) val++;  
    }
    return val ^ _seed;
  }


  int _analog()
  {
    uint8_t val = 0;
    for (uint8_t i = 0; i < 8; i++)
    {
      val <<= 1;
      if (analogRead(_pin) & 1) val++;
    }
    return val ^ _seed;
  }
};

// TODO alternative random nummer generator so all platforms behave same.

// -- END OF FILE --
