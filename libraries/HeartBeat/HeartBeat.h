#pragma once
//
//    FILE: HeartBeat.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.2
// PURPOSE: Arduino library for HeartBeat with frequency and dutyCycle
//    DATE: 2019-06-12
//     URL: https://github.com/RobTillaart/HeartBeat


#include "Arduino.h"

#define HEARTBEAT_LIB_VERSION       (F("0.1.2"))

class HeartBeat
{
public:
  HeartBeat();

  void  begin(const uint8_t pin, float frequency = 1.0);
  void  setFrequency(float frequency = 1.0);
  void  setDutyCycle(float dutyCycle = 50);


  inline void enable()  { _running = true;  };
  inline void disable() { _running = false; };

  void  beat();

  // OBSOLETE in next release
  void  set(float frequency = 1.0) { setFrequency(frequency); };

protected:
  void     _setFreqDuty();
  float    _frequency;
  float    _dutyCycle;
  uint32_t _lastHeartBeat;
  uint32_t _dutyCycleHigh;
  uint32_t _dutyCycleLow;
  bool     _running;
  uint8_t  _pin;
};

// -- END OF FILE --
