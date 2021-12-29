#pragma once
// 
//    FILE: timing.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.3
// PURPOSE: Arduino library with wrapper classes for seconds millis micros 
//     URL: https://github.com/RobTillaart/timing
//
//  HISTORY: 
//  0.1.00  2011-01-04   initial version
//  0.1.01  2011-07-19   lib version
//  0.1.02  2015-03-02   move all to mymillis.h file so compiler can optimize
//  0.2.0   2020-07-07   renamed to timing.h
//  0.2.1   2021-01-09   added Arduino-CI + unit test
//  0.2.2   2021-05-27   added Arduino-lint
//  0.2.3   2021-12-29   update library.json, license, minor edits


#define TIMING_LIB_VERSION        (F("0.2.3"))


class microSeconds
{
public:
  microSeconds()                  { set(0); }
  uint32_t now()                  { return micros() - _offset; }
  void set(uint32_t value = 0UL)  { _offset = micros() - value; }
  uint32_t getOffset()            { return _offset; };

private:
  uint32_t _offset = 0UL;
};


class milliSeconds
{
public:
  milliSeconds()                  { set(0); };
  uint32_t now()                  { return millis() - _offset; };
  void set(uint32_t value = 0UL)  { _offset = millis() - value; };
  uint32_t getOffset()            { return _offset; };

private:
  uint32_t _offset = 0UL;
};


class seconds
{
public:
  seconds()                       { set(0); }
  uint32_t now()                  { return millis()/1000UL - _offset; }
  void set(uint32_t value = 0UL)  { _offset = millis()/1000UL - value; }
  uint32_t getOffset()            { return _offset; };

private:
    uint32_t _offset = 0UL;
};


// -- END OF FILE --

