#pragma once
//
//    FILE: PulsePattern.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.7
//    DATE: 2012-11-23
// PURPOSE: Arduino Library to generate repeating pulse patterns
//          sends a pulse pattern to a digital pin (continuously)
// HISTORY: See PulsePattern.cpp
//

#if !defined(__AVR__)
  #error "Only support for AVR boards"
#endif


#include "Arduino.h"


#define PULSEPATTERN_LIB_VERSION        (F("0.1.7"))

//  RUNNING STATES
#define NOTINIT                         -1
#define STOPPED                         0
#define RUNNING                         1

//  PRESCALER CONSTANTS
#define NO_CLOCK                        0   //  timer off
#define PRESCALE_1                      1
#define PRESCALE_8                      2
#define PRESCALE_64                     3
#define PRESCALE_256                    4
#define PRESCALE_1024                   5
#define EXT_T1_FALLING                  6   //  external clock
#define EXT_T2_RISING                   7   //  external clock

//  RUNNING MODE
#define PP_ONCE                         1
#define PP_CONTINUOUS                   0xFFFFFFFF


class PulsePattern
{
public:
  PulsePattern();

  void  init(const uint8_t pin,
             const uint16_t * ar, const uint8_t size,
             const uint8_t level, const uint8_t prescaler);

  void  setFactor(float perc) { _factor = round(4096 * (1 + perc)); };
  float getFactor()           { return _factor / 4096.0 - 1; };
  void  start(uint32_t times = PP_CONTINUOUS);
  void  cont();
  void  stop();
  bool  isRunning() const { return _state == RUNNING; };

  void  worker();

private:
  void  stopTimer();
  void  setTimer(const uint16_t cc) const;

  uint32_t   _factor = 4096;
  uint16_t * _ar;
  uint8_t    _size;
  uint8_t    _pin;
  uint8_t    _pinbit;
  volatile uint8_t * _pinout;
  uint8_t           _prescaler;
  volatile uint8_t  _level;
  volatile int8_t   _state;
  volatile uint8_t  _cnt;

  uint32_t          _times = PP_CONTINUOUS;
};

extern PulsePattern PPGenerator;


//  -- END OF FILE --
