#pragma once
//
//    FILE: AnalogPin.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.9
//    DATE: 2013-09-09
// PURPOSE: wrapper for analogRead with smoothing and noise filtering
//     URL: https://github.com/RobTillaart/AnalogPin


#include "Arduino.h"

#define ANALOGPIN_LIB_VERSION       (F("0.2.9"))


class AnalogPin
{
public:

  explicit AnalogPin(const uint8_t pin);

  //  pre-scale = { 2..7 }, 2 is bad, 3 is pretty noisy, 4 and 5 are acceptable, 
  //                        6 and 7 are good. Depends on project!!!
  //  time indication per analogRead for different pre-scale values on UNO
  //  2 => 14 uSec     5 => 38 uSec
  //  3 => 18 uSec     6 => 63 uSec
  //  4 => 24 uSec     7 => 120 uSec (default/normal)
  void    setPrescaler(const uint8_t prescaler = 7);
  inline uint8_t getPrescaler(void) const { return _prescaler; };

  //  noise 0..255; in practice only small values are used (0..10).
  inline void    setNoiseThreshold(const uint8_t noise = 0) { _noise = noise; };
  inline uint8_t getNoiseThreshold(void) const { return _noise; };

  //  alpha = 0..31;
  void    setSmoothWeight(const uint8_t alpha = 0);
  inline uint8_t getSmoothWeight(void) const { return _alpha; };

  //  twice=true to do analogRead twice to reduce noise
  int     read(const bool twice = false);
  int     readSmoothed();

  //  expose internal data as that might be useful.
  inline int readPrevious(void) const { return _prevValue; }
  inline int readLast(void) const { return _value; }


private:
  void    _rawRead();

  uint8_t _pin;
  uint8_t _alpha;
  uint8_t _noise;
  uint8_t _prescaler;
  int     _value;
  int     _prevValue;
};


//  -- END OF FILE --

