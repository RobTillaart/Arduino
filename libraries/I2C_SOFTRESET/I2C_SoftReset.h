#pragma once
//
//    FILE: I2C_SoftReset.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2025-02-03
// PURPOSE: Arduino library for I2C_SoftReset, to reset stuck devices.
//     URL: https://github.com/RobTillaart/I2C_SoftReset
//
//  based upon description in Puya P24C08C datasheet.


#include "Arduino.h"

#define I2C_SOFTRESET_LIB_VERSION     (F("0.1.0"))



/////////////////////////////////////////////
//
//  CLASS
//
class I2C_SOFTRESET
{
public:
  I2C_SOFTRESET(uint8_t SDA, uint8_t SCL)
  {
    _sda = SDA;
    _scl = SCL;
    _lastReset = 0;
  };

  void reset()
  {
    pinMode(_scl, OUTPUT);
    pinMode(_sda, OUTPUT);

    //  START
    digitalWrite(_scl, HIGH);
    digitalWrite(_sda, LOW);
    delayMicroseconds(10);
    digitalWrite(_scl, LOW);
    digitalWrite(_sda, HIGH);
    delayMicroseconds(10);

    for (int i = 0; i < 9; i++)
    {
      digitalWrite(_scl, HIGH);
      delayMicroseconds(10);
      digitalWrite(_scl, LOW);
      delayMicroseconds(10);
    }

    //  START
    digitalWrite(_scl, HIGH);
    digitalWrite(_sda, LOW);
    delayMicroseconds(10);
    digitalWrite(_scl, LOW);
    delayMicroseconds(10);
    //  STOP
    digitalWrite(_scl, HIGH);
    digitalWrite(_sda, HIGH);
    delayMicroseconds(10);
    digitalWrite(_scl, LOW);
    delayMicroseconds(10);

    _lastReset = millis();
  };

  uint32_t lastReset()
  {
    return _lastReset;
  };

private:
  uint8_t  _scl = 255;
  uint8_t  _sda = 255;
  uint32_t _lastReset = 0;
};


/////////////////////////////////////////////
//
//  FUNCTION
//
void I2CSoftReset(uint8_t SDA, uint8_t SCL)
{
  pinMode(SDA, OUTPUT);
  pinMode(SCL, OUTPUT);

  //  START
  digitalWrite(SCL, HIGH);
  digitalWrite(SDA, LOW);
  delayMicroseconds(10);
  digitalWrite(SCL, LOW);
  digitalWrite(SDA, HIGH);
  delayMicroseconds(10);

  for (int i = 0; i < 9; i++)
  {
    digitalWrite(SCL, HIGH);
    delayMicroseconds(10);
    digitalWrite(SCL, LOW);
    delayMicroseconds(10);
  }

  //  START
  digitalWrite(SCL, HIGH);
  digitalWrite(SDA, LOW);
  delayMicroseconds(10);
  digitalWrite(SCL, LOW);
  delayMicroseconds(10);
  //  STOP
  digitalWrite(SCL, HIGH);
  digitalWrite(SDA, HIGH);
  delayMicroseconds(10);
  digitalWrite(SCL, LOW);
  delayMicroseconds(10);
};


//  -- END OF FILE --

