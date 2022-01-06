//
//    FILE: AM232X.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.4.0
// PURPOSE: AM232X library for AM2320 for Arduino.
//
// HISTORY:
//   0.1.0  2017-12-11  initial version
//   0.1.1  2017-12-12  added CRC checking
//   0.1.2  2017-12-12  get and set functions.
//   0.1.3  2017-12-19  added ESP8266 - issue #86
//                      tested by Viktor Balint
//   0.1.4  2018-10-24  fixed temperature formula - #114
//                      thanks to 9a4gl
//   0.1.5  2020-03-25  refactor, add read() to begin()
//   0.2.0  2020-05-03  made temperature + humidity private, add wrapper functions.
//   0.2.1  2020-05-06  fix temperature function (thanks Chade)
//   0.2.2  2020-05-12  added ESP32 support
//   0.2.3  2020-05-27  update library.json
//   0.2.4  2020-12-09  Arduino-CI
//   0.3.0  2021-01-12  isConnected() + Wire0..Wire5 support
//   0.3.1  2021-01-28  fix TODO's in code
//   0.3.2  2021-03-30  #13 - timeout to isConnected() + wakeUp() + readme.md
//   0.3.3  2021-10-19  update build-CI
//   0.3.4  2021-12-11  add unit test, update library.json, license
//   0.4.0  2022-01-06  add offset(), lastRead() and readDelay()
//                      refactor examples, update readme.md


#include "AM232X.h"


const uint8_t AM232X_ADDRESS = 0x5C;


////////////////////////////////////////////////////////////////////
//
// PUBLIC
//

AM232X::AM232X(TwoWire *wire)
{
  _wire        = wire;
  //  reset() or begin() ?
  _humidity    = 0.0;
  _temperature = 0.0;
  _humOffset   = 0.0;
  _tempOffset  = 0.0;
  _lastRead    = 0;
  _readDelay   = 2000;
}


#if defined (ESP8266) || defined(ESP32)
bool AM232X::begin(uint8_t sda, uint8_t scl)
{
  _wire = &Wire;
  _wire->begin(sda, scl);
  if (! isConnected()) return false;
  this->read();
  return true;
}
#endif


bool AM232X::begin()
{
  _wire->begin();
  if (! isConnected()) return false;
  this->read();
  return true;
}


bool AM232X::isConnected(uint16_t timeout)
{
  uint32_t start = micros();
  while (micros() - start < timeout)
  {
    _wire->beginTransmission(AM232X_ADDRESS);
    if ( _wire->endTransmission() == 0) return true;
    yield();
    delayMicroseconds(100);
  }
  return false;
}


int AM232X::read()
{
  if (_readDelay == 0) _readDelay = 2000;  // reset
  if (millis() - _lastRead < _readDelay)
  {
    return AM232X_READ_TOO_FAST;
  }
  // READ HUMIDITY AND TEMPERATURE REGISTERS
  int rv = _readRegister(0x00, 4);
  if (rv < 0) return rv;

  // CONVERT AND STORE
  _humidity = (bits[2] * 256 + bits[3]) * 0.1;
  _temperature = ((bits[4] & 0x7F) * 256 + bits[5]) * 0.1;

  if (bits[4] & 0x80)
  {
    _temperature = -_temperature;
  }
  return AM232X_OK;
}


float AM232X::getHumidity()
{
  if (_humOffset == 0.0) return _humidity;
  return _humidity + _humOffset;
};


float AM232X::getTemperature()
{
  if (_tempOffset == 0.0) return _temperature;
  return _temperature + _tempOffset;
};


int AM232X::getModel()
{
  int rv = _readRegister(0x08, 2);
  if (rv < 0) return rv;

  return (bits[2] * 256) + bits[3];
}


int AM232X::getVersion()
{
  int rv = _readRegister(0x0A, 1);
  if (rv < 0) return rv;

  return bits[2];
}


uint32_t AM232X::getDeviceID()
{
  int rv = _readRegister(0x0B, 4);
  if (rv < 0) return rv;

  uint32_t _deviceID = (bits[2] * 256) + bits[3];
  _deviceID = _deviceID * 256 + bits[4];
  _deviceID = _deviceID * 256 + bits[5];
  return _deviceID;
}


int AM232X::getStatus()
{
  int rv = _readRegister(0x0F, 1);
  if (rv < 0) return rv;

  return bits[2];
}


int AM232X::getUserRegisterA()
{
  int rv = _readRegister(0x10, 2);
  if (rv < 0) return rv;

  return (bits[2] * 256) + bits[3];
}


int AM232X::getUserRegisterB()
{
  int rv = _readRegister(0x12, 2);
  if (rv < 0) return rv;

  return (bits[2] * 256) + bits[3];
}


int AM232X::setStatus(uint8_t value)
{
  int rv = _writeRegister(0x0F, 1, value);
  if (rv < 0) return rv;

  return AM232X_OK;
}


int AM232X::setUserRegisterA(int value)
{
  int rv = _writeRegister(0x10, 2, value);
  if (rv < 0) return rv;

  return AM232X_OK;
}


int AM232X::setUserRegisterB(int value)
{
  int rv = _writeRegister(0x12, 2, value);
  if (rv < 0) return rv;

  return AM232X_OK;
}


////////////////////////////////////////////////////////////////////
//
// PRIVATE
//
int AM232X::_readRegister(uint8_t reg, uint8_t count)
{
  if (! wakeUp() ) return AM232X_ERROR_CONNECT;

  // request the data
  _wire->beginTransmission(AM232X_ADDRESS);
  _wire->write(0x03);
  _wire->write(reg);
  _wire->write(count);
  int rv = _wire->endTransmission();
  if (rv < 0) return rv;

  // request 4 extra, 2 for cmd + 2 for CRC
  rv = _getData(count + 4);
  return rv;
}


int AM232X::_writeRegister(uint8_t reg, uint8_t cnt, int16_t value)
{
  if (! wakeUp() ) return AM232X_ERROR_CONNECT;

  // prepare data to send
  bits[0] = 0x10;
  bits[1] = reg;
  bits[2] = cnt;

  if (cnt == 2)
  {
    bits[4] = value & 0xFF;
    bits[3] = (value >> 8) & 0xFF;
  }
  else
  {
    bits[3] = value & 0xFF;
  }

  // send data
  uint8_t length = cnt + 3;  // 3 = cmd, startReg, #bytes
  _wire->beginTransmission(AM232X_ADDRESS);
  for (int i = 0; i < length; i++)
  {
    _wire->write(bits[i]);
  }
  // send the CRC
  uint16_t crc = _crc16(bits, length);
  _wire->write(crc & 0xFF);
  _wire->write(crc >> 8);

  int rv = _wire->endTransmission();
  if (rv < 0) return rv;

  // wait for the answer
  rv = _getData(length);
  return rv;
}


int AM232X::_getData(uint8_t length)
{
  int bytes = _wire->requestFrom(AM232X_ADDRESS, length);

  for (int i = 0; i < bytes; i++)
  {
    bits[i] = _wire->read();
  }

  // ANALYZE ERRORS
  //   will not detect if we requested 1 byte as that will
  //   return 5 bytes as requested. E.g. getStatus()
  //   design a fix if it becomes a problem.
  if (bytes != length)
  {
    switch (bits[3])
    {
      case 0x80: return AM232X_ERROR_FUNCTION;
      case 0x81: return AM232X_ERROR_ADDRESS;
      case 0x82: return AM232X_ERROR_REGISTER;
      case 0x83: return AM232X_ERROR_CRC_1;  // previous write had a wrong CRC
      case 0x84: return AM232X_ERROR_WRITE_DISABLED;
      default:   return AM232X_ERROR_UNKNOWN;
    }
  }

  // CRC is LOW Byte first
  uint16_t crc = bits[bytes - 1] * 256 + bits[bytes - 2];
  if (_crc16(&bits[0], bytes - 2) != crc)
  {
    return AM232X_ERROR_CRC_2;  // read itself has wrong CRC
  }

  return AM232X_OK;
}


uint16_t AM232X::_crc16(uint8_t *ptr, uint8_t len)
{
  uint16_t crc = 0xFFFF;

  while (len--)
  {
    crc ^= *ptr++;
    for (int i = 0; i < 8; i++)
    {
      if (crc & 0x01)
      {
        crc >>= 1;
        crc ^= 0xA001;
      }
      else
      {
        crc >>= 1;
      }
    }
  }
  return crc;
}


// -- END OF FILE --

