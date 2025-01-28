#pragma once
//
//    FILE: PIR8575.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2025-01-28
// PURPOSE: Arduino library for 16 channel PIR detection system based upon PCF8575
//          Also works (limited) with PCF8574.


#include "Arduino.h"
#include "Wire.h"

#define PIR8575_LIB_VERSION        (F("0.1.0"))

#define PIR8575_OK                  0x00
#define PIR8575_PIN_ERROR           0x81
#define PIR8575_I2C_ERROR           0x82


class PIR8575
{
public:
  //  CONSTRUCTOR
  //  pins to set.
  PIR8575(uint8_t address, TwoWire * wire = &Wire)
  {
    _address = address;
    _wire = wire;
  };

  bool     begin()
  {
    if (! isConnected()) return false;
    return true;
  };

  bool     isConnected()
  {
    _wire->beginTransmission(_address);
    return ( _wire->endTransmission() == 0);
  };

  uint8_t  getAddress()
  {
    return _address;
  };

  uint16_t read16()
  {
    if (_wire->requestFrom(_address, (uint8_t)2) != 2)
    {
      _error = PIR8575_I2C_ERROR;
      return _dataIn;                   //  last value
    }
    _dataIn = _wire->read();            //  low 8 bits
    _dataIn |= (_wire->read() << 8);    //  high 8 bits
    return _dataIn;
  };

  uint16_t read(uint8_t pir)
  {
    if (pir > 15)
    {
      _error = PIR8575_PIN_ERROR;
      return 0;
    }
    read16();
    return (_dataIn & (1 << pir)) > 0;
  };

  int lastError()
  {
    int e = _error;
    _error = PIR8575_OK;  //  reset error after read, is this wise?
    return e;
  };


protected:
  uint8_t   _address;
  TwoWire * _wire;
  uint16_t  _dataIn = 0;
  uint8_t   _error = PIR8575_OK;
};


//  -- END OF FILE --

