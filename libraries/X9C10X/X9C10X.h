#pragma once
//
//    FILE: X9C10X.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.3
// PURPOSE: Arduino Library for X9C10X series digital potentiometer.
//     URL: https://github.com/RobTillaart/X9C10X


#include "Arduino.h"

#define X9C10X_LIB_VERSION        (F("0.2.3"))


/////////////////////////////////////////////////////////
//
//  X9C MINIMAL BASE CLASS
//
class X9C
{
public:

  X9C();

  void begin(uint8_t pulsePin, uint8_t directionPin, uint8_t selectPin);

  //  step size 1.
  //  return false if end of range reached.
  bool     incr();
  bool     decr();

  //  use with care
  void     store();

protected:
  uint8_t  _pulsePin;
  uint8_t  _directionPin;
  uint8_t  _selectPin;

  void     _move(uint8_t direction, uint8_t steps = 1);
};


/////////////////////////////////////////////////////////
//
//  X9C10X BASE CLASS
//
class X9C10X : public X9C
{
public:
  //  ohm can be actual measured value e.g 9950 ohm (calibration)
  X9C10X(uint32_t maxOhm = 10000);

  //  position = 0..99
  //             values > 99 are truncated.
  //  forced = true will ignore the cached position
  //           takes up to 150 steps as one cannot read the position from device.
  //  forced = default false as that is safer and backwards compatible.
  //  returns new position 0..99
  uint8_t  setPosition(uint8_t position, bool forced = false);
  uint8_t  getPosition();

  //  step size 1.
  //  return false if end of range reached.
  bool     incr();
  bool     decr();

  //  use with care
  //  returns new position 0..99
  uint8_t  store();
  //  note: restoreInternalPosition() is not available in X9C base class.
  //  position = 0..99
  //             values > 99 are truncated.
  //  returns new position 0..99
  uint8_t  restoreInternalPosition(uint8_t position);

  //  current resistance in ohm.
  uint32_t getOhm();
  uint32_t getMaxOhm();
  uint8_t  Ohm2Position(uint32_t value, bool invert = false);

  //  returns 0 as it is unknown for X9C10X
  uint16_t getType();


protected:
  uint32_t _maxOhm   = 0;
  uint8_t  _position = 0;
  uint16_t _type     = 0;
};


/////////////////////////////////////////////////////////
//
//  SPECIFIC DERIVED DEVICE CLASSES
//
class X9C102 : public X9C10X
{
public:
  X9C102(uint32_t ohm = 1000);
};


class X9C103 : public X9C10X
{
public:
  X9C103(uint32_t ohm = 10000);
};


class X9C104 : public X9C10X
{
public:
  X9C104(uint32_t ohm = 100000);
};


class X9C503 : public X9C10X
{
public:
  X9C503(uint32_t ohm = 50000);
};


//  -- END OF FILE --

