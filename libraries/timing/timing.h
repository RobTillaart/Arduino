#pragma once
// 
//    FILE: timing.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.4
// PURPOSE: Arduino library with wrapper classes for seconds millis micros 
//     URL: https://github.com/RobTillaart/timing


#define TIMING_LIB_VERSION        (F("0.2.4"))


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
  uint32_t now()                  { return millis() / 1000UL - _offset; }
  void set(uint32_t value = 0UL)  { _offset = millis() / 1000UL - value; }
  uint32_t getOffset()            { return _offset; };

private:
    uint32_t _offset = 0UL;
};


// -- END OF FILE --

