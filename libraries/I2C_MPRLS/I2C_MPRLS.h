#pragma once
//
//    FILE: I2C_MPRLS.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
//    DATE: 2025-09-03
// PURPOSE: Arduino library for MPRLS pressure sensors. (Honeywell).
//     URL: https://github.com/RobTillaart/MPRLS
//          https://github.com/RobTillaart/pressure (conversions)
//
//  I2C only


#include "Arduino.h"
#include "Wire.h"

#define I2C_MPRLS_LIB_VERSION              (F("0.1.1"))


//  ADDRESS = 0x30  fixed?


//  ERROR CODES
const int I2C_MPRLS_OK            =  1;
const int I2C_MPRLS_INIT          =  0;
const int I2C_MPRLS_READ_ERROR    = -1;
const int I2C_MPRLS_WRITE_ERROR   = -2;
const int I2C_MPRLS_CONNECT_ERROR = -3;
//  const int I2C_MPRLS_STATE_ERROR   = -99;  //  TODO


//  STATUS BIT MASKS
const uint8_t I2C_MPRLS_NONE    = 0x00;
const uint8_t I2C_MPRLS_POWER   = 0x40;
const uint8_t I2C_MPRLS_BUSY    = 0x20;
const uint8_t I2C_MPRLS_MEMTEST = 0x04;
const uint8_t I2C_MPRLS_MATH    = 0x01;


class I2C_MPRLS
{
public:
  I2C_MPRLS(uint8_t address, TwoWire *wire = &Wire)
  {
    reset();
    _address     = address;
    _wire        = wire;
  }

  bool begin(float maxPressure)
  {
    return begin(0, maxPressure);
  }

  bool begin(float minPressure, float maxPressure)
  {
    _minPressure = minPressure;
    _maxPressure = maxPressure;
    reset();
    if (! isConnected())
    {
      _error = I2C_MPRLS_CONNECT_ERROR;
      return false;
    }
    _error = I2C_MPRLS_OK;
    return true;
  }

  void reset()
  {
    _errorCount = 0;
    _lastRead   = 0;
    _pressure   = 0;
    _error      = I2C_MPRLS_INIT;
    _state      = I2C_MPRLS_NONE;
  }

  uint8_t getAddress()
  {
    return _address;
  }

  bool isConnected()
  {
    _wire->beginTransmission(_address);
    return (_wire->endTransmission() == 0);
  }


  //  TRANSFER FUNCTION
  void setTransferFunction(char tff)
  {
    _transferFunction = tff;
  }

  char getTransferFunction()
  {
    return _transferFunction;
  }


  //  ASYNC API == work in progress
  int request()
  {
    _wire->beginTransmission(_address);
    _wire->write(0xAA);
    _wire->write(0x00);
    _wire->write(0x00);
    int n = _wire->endTransmission();
    if (n != 0)
    {
      //  handle n ...
      _errorCount++;
      _error = I2C_MPRLS_WRITE_ERROR;
      return _error;
    }
    _error = I2C_MPRLS_OK;
    return _error;
  }


  //  check status field
  bool conversionReady()
  {
    _wire->requestFrom(_address, (uint8_t)1);
    if (_wire->available() != 1)
    {
      _errorCount++;
      _error = I2C_MPRLS_READ_ERROR;
      return false;
    }
    //  READ STATUS
    _error = I2C_MPRLS_OK;
    _state = _wire->read();
    //  need to check power flag too?
    return (_state & I2C_MPRLS_BUSY) > 0;
  }


  //  use EOC pin (not supported yet)
  //  bool endOfConversion()
  //  {
  //    return digitalRead(_EOC) == HIGH / LOW;
  //  }


  //  status + pressure field
  int getData()
  {
    _wire->requestFrom(_address, (uint8_t)4);
    if (_wire->available() != 4)
    {
      _errorCount++;
      _error = I2C_MPRLS_READ_ERROR;
      return _error;
    }

    //  READ STATUS & PRESSURE BYTES
    _state = _wire->read();
    _rpc = _wire->read();
    _rpc <<= 8;
    _rpc += _wire->read();
    _rpc <<= 8;
    _rpc += _wire->read();

    //  TODO check state here  (user can always do that)
    //  - int readData(&state, &pressure) ?
    //  - add error code
    //  - set pressure to something or not ?


    //  _transferFunction is default A.
    _pressure = 0;
    switch (_transferFunction)
    {
      case 'C':  //  20% - 80%
        //  reference: (can be optimized)
        _pressure = (_rpc - 3355444) * (_maxPressure - _minPressure) /  10066330.0;
        if (_minPressure != 0) _pressure += _minPressure;
        break;
      case 'B':  //  2.5% - 22.5%
        //  reference: (can be optimized)
        _pressure = (_rpc - 419430) * (_maxPressure - _minPressure) /  3355444.0;
        if (_minPressure != 0) _pressure += _minPressure;
        break;
      case 'A':  //  10% - 90%
      default:
         //  reference: (can be optimized)
        _pressure = (_rpc - 1677722) * (_maxPressure - _minPressure) /  13421772.0;
        if (_minPressure != 0) _pressure += _minPressure;
        break;
    }

    //  update status
    _lastRead = millis();
    _error = I2C_MPRLS_OK;
    return _error;
  }


  //  BLOCKING API
  int read()
  {
    //  new read() invalidates last state.
    _state = I2C_MPRLS_NONE;

    //  REQUEST CONVERSION
    request();
    if (_error != I2C_MPRLS_OK) return _error;

    //  CONVERSION READY
    //  hard coded delay 5 milliseconds (see datasheet)
    //  EOC (end of conversion) pin check is a future option.
    delay(5);

    getData();
    return _error;
  }


  //  returns same value with each call until read() is called.
  float getPressure() { return _pressure; };

  //  timestamp of last good read
  uint32_t lastRead() { return _lastRead; };

  //  get the last state
  uint8_t  getState() { return _state; };

  //  ERROR
  int getLastError()
  {
    int e = _error;
    _error = I2C_MPRLS_OK;
    return e;
  };

  //  # errors since last reset
  uint16_t errorCount() { return _errorCount; };

  //  debugging / own conversion.
  int   rawPressureCount() { return _rpc; };
  float getMinPressure() { return _minPressure; };
  float getMaxPressure() { return _maxPressure; };


protected:
  uint8_t  _address;
  TwoWire*  _wire;

  float    _minPressure;
  float    _maxPressure;
  float    _pressure;
  int      _rpc;  //  raw counter for debugging.

  uint8_t  _state;
  int      _error;
  uint16_t _errorCount;
  uint32_t _lastRead;

  char     _transferFunction = 'A';
};


//  -- END OF FILE --

