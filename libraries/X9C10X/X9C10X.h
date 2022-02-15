#pragma once
//
//    FILE: X9C10X.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
// PURPOSE: Arduino Library for X9C10X series digital potentiometer.
//


#include "Arduino.h"

#define X9C10X_LIB_VERSION        (F("0.1.1"))


class X9C10X
{
public:
  //  ohm can be actual measured value e.g 9950 ohm (calibration)
  X9C10X(uint32_t ohm = 10000);

  void begin(uint8_t pulsePin, uint8_t directionPin, uint8_t selectPin, uint8_t position = 0);

  //  position = 0..99
  void     setPosition(uint8_t position);
  uint8_t  getPosition() { return _position; };

  //  step size 1.
  void     incr();
  void     decr();

  //  use with care
  uint8_t  store();

  //  current resistance in ohm.
  //  Q: rounding needed?
  uint32_t getOhm() { return (_ohm * _position) / 99; };
  // misc
  uint32_t getMaxOhm() { return _ohm; };

  //  Q: needed?
  uint16_t getType() { return _type; };


protected:
  uint8_t  _pulsePin;
  uint8_t  _directionPin;
  uint8_t  _selectPin;

  uint32_t _ohm;
  uint8_t  _position;
  uint16_t _type = 0;   // needed?

  void     _move(uint8_t direction, uint8_t steps = 1);
};


/////////////////////////////////////////////////////////
//
// DERIVED
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




// -- END OF FILE --

