#pragma once
//
//    FILE: HeartBeat.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.1
// PURPOSE: Arduino library for HeartBeat with frequency and dutyCycle
//    DATE: 2019-06-12
//     URL: https://github.com/RobTillaart/HeartBeat


#include "Arduino.h"

#define HEARTBEAT_LIB_VERSION       (F("0.2.1"))


class HeartBeat
{
public:
  HeartBeat();

  void   begin(const uint8_t pin, float frequency = 1.0);
  
  void   setFrequency(float frequency = 1.0);
  void   setDutyCycle(float dutyCycle = 50);
  float  getFrequency() { return _frequency; };
  float  getDutyCycle() { return _dutyCycle; };

  inline void enable()  { _running = true;  };
  inline void disable() { _running = false; };

  void    beat();
  uint8_t getState()    { return _state; };

protected:
  void     _setFreqDuty();

  float    _frequency      = 1.0;
  float    _dutyCycle      = 50;

  uint32_t _lastHeartBeat  = 0;
  uint32_t _dutyCycleHigh  = 500;
  uint32_t _dutyCycleLow   = 500;

  bool     _running        = false;
  uint8_t  _pin            = 255;
  uint8_t  _state          = LOW;
};


// -- END OF FILE --
