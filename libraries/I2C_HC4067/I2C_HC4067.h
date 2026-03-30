#pragma once
//
//    FILE: I2C_I2C_HC4067.h
//  AUTHOR: Rob Tillaart
//    DATE: 2026-03-30
// VERSION: 0.1.0
// PURPOSE: Arduino library for CD74HC4067 1 x 16 channel multiplexer and compatibles.
//     URL: https://github.com/RobTillaart/I2C_HC4067


#include "Arduino.h"
#include "Wire.h"

#define I2C_HC4067_LIB_VERSION         (F("0.1.0"))


class I2C_HC4067
{
public:
  ////////////////////////////////////////////////////////////
  //
  //  Constructor
  //
  I2C_HC4067(uint8_t address, TwoWire *wire = &Wire)
  {
    _address = address;
    _wire = wire;

    _channel   = 0;
    //  to force write.
    _lastValue = 0x10;
  }

  bool begin()
  {
    if (! isConnected())
    {
      return false;
    }
    this->disable();
    return true;
  }

  bool isConnected()
  {
    _wire->beginTransmission(_address);
    return (_wire->endTransmission() == 0);
  }

  uint8_t getAddress()
  {
    return _address;
  }


  ////////////////////////////////////////////////////////////
  //
  //  HC4067 API
  //
  bool setChannel(uint8_t channel, bool disable = true)
  {
    if (channel > 15) return false;
    if (channel != _channel)
    {
      _channel = channel;
      if (disable) this->disable();  //  prevent ghost channels.
      this->_write();
      this->enable();
    }
    return true;
  }

  uint8_t getChannel()
  {
    return _channel;
  }

  void enable()
  {
    _enable = true;
    this->_write();
  }

  void disable()
  {
    _enable = false;
    this->_write();
  }

  bool isEnabled()
  {
    return _enable;
  }


private:
  int _write()
  {
    uint8_t value = _channel;
    if (_enable) value |= 0x10;

    //  no change.
    if (_lastValue == value) return 0;
    _lastValue = value;
    _wire->beginTransmission(_address);
    _wire->write(value);
    _error = _wire->endTransmission();
    return _error;
  }

  uint8_t  _address;
  TwoWire* _wire;

  bool     _enable;
  uint8_t  _channel;
  uint8_t  _lastValue;
  int      _error;
};


//  -- END OF FILE --

