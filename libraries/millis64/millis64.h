#pragma once
//
//    FILE: millis64.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
//    DATE: 2025-01-17
// PURPOSE: Arduino library for millis64 micros64 millis32 micros32, time counters with optional offset.
//     URL: https://github.com/RobTillaart/millis64
//          https://forum.arduino.cc/t/arduino-millis-looping-after-45-5104-days/1343661/2


#include "Arduino.h"


#define MILLIS64_LIB_VERSION        (F("0.1.1"))


/////////////////////////////////////////////////////
//
//  64 bits MILLIS
//


//  call once per 20 days
uint64_t millis64(uint32_t offset = 0)
{
  static uint64_t now64 = 0;
  static bool flag = false;
  uint32_t now = millis();
  if ((now & 0x80000000) == 0)
  {
    if (flag)
    {
      flag = false;
      now64 += 0x100000000;  //  1 << 32;
    }
  }
  else
  {
    flag = true;
  }
  if (offset == 0) return (now64 | now);
  return (now64 | now) + offset;
}


//  call once per 49 days - slower
// uint64_t millis64(uint32_t offset = 0)
// {
  // static uint64_t now64 = 0;
  // static uint32_t previousTime = 0;
  // uint32_t now = millis();
  // if (now < previousTime)
  // {
    // now64 += 0x100000000;  //  1 << 32;
  // }
  // previousTime = now;
  // if (offset == 0) return (now64 | now);
  // return (now64 | now) + offset;
// }



/////////////////////////////////////////////////////
//
//  64 bits MICROS
//


//  call once per 30 minutes.
uint64_t micros64(uint32_t offset = 0)
{
  static uint64_t now64 = 0;
  static bool flag = false;
  uint32_t now = micros();
  if ((now & 0x80000000) == 0)
  {
    if (flag)
    {
      flag = false;
      now64 += 0x100000000;  //  1 << 32;
    }
  }
  else
  {
    flag = true;
  }
  if (offset == 0) return (now64 | now);
  return (now64 | now) + offset;
};


//  PATCH for ESP8266 as it already supports micros64().
//  call once per 30 minutes.
//  uint64_t micros64(uint32_t offset)
//  {
//    micros64() + offset;
//  }


//  call once per 70 minutes - slower
// uint64_t micros64(uint32_t offset = 0)
// {
  // static uint64_t now64 = 0;
  // static uint32_t previousTime = 0;
  // uint32_t now = micros();
  // if (now < previousTime)
  // {
    // now64 += 0x100000000;  //  1 << 32;
  // }
  // previousTime = now;
  // if (offset == 0) return (now64 | now);
  // return (now64 | now) + offset;
// }




/////////////////////////////////////////////////////
//
//  32 bits functions
//
uint32_t millis32(uint32_t offset = 0)
{
  return millis() + offset;
};

uint32_t micros32(uint32_t offset = 0)
{
  return micros() + offset;
};


//  -- END OF FILE --

