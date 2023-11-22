#pragma once
//
//    FILE: timing.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.6
// PURPOSE: Arduino library with wrapper classes for seconds millis micros
//     URL: https://github.com/RobTillaart/timing


#define TIMING_LIB_VERSION        (F("0.2.6"))


class microSeconds
{
public:
  microSeconds()                  { set(0); };
  uint32_t now()                  { return micros() - _offset; };
  void set(uint32_t value = 0UL)  { _offset = micros() - value; };
  void add(uint32_t value)        { _offset -= value; };
  uint32_t getOffset()            { return _offset; };
  double toSeconds()              { return (millis() - _offset) * 0.000001; };

private:
  uint32_t _offset = 0UL;
};


class milliSeconds
{
public:
  milliSeconds()                  { set(0); };
  uint32_t now()                  { return millis() - _offset; };
  void set(uint32_t value = 0UL)  { _offset = millis() - value; };
  void add(uint32_t value)        { _offset -= value; };
  uint32_t getOffset()            { return _offset; };
  double toSeconds()              { return (millis() - _offset) * 0.001; };

private:
  uint32_t _offset = 0UL;
};


class seconds
{
public:
  seconds()                       { set(0); };
  uint32_t now()                  { return millis() / 1000UL - _offset; };
  void set(uint32_t value = 0UL)  { _offset = millis() / 1000UL - value; };
  void add(uint32_t value)        { _offset -= value; };
  uint32_t getOffset()            { return _offset; };
  //  for completeness
  double toSeconds()              { return millis() * 0.001 - _offset; };

  //  experimental
  //  does not include days (beyond 99 hrs)
  char * toClock()
  {
    static char buf[12];
    uint32_t _now = now();
    int hh = _now / 3600;
    _now = _now - hh * 3600;
    int mm  = _now / 60;
    int ss = _now - mm * 60;
    //  ESP32 warning breaks Arduino build. next line.
    sprintf(buf, "%02d:%02d:%02d", hh, mm, ss);
    return buf;
  }


private:
  uint32_t _offset = 0UL;
};


//  -- END OF FILE --

