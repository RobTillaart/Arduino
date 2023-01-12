//
//    FILE: AM232X.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.4.5
// PURPOSE: AM232X library for AM2320 for Arduino.
//     URL: https://github.com/RobTillaart/AM232X


#include "AM232X.h"


const uint8_t AM232X_ADDRESS = 0x5C;


////////////////////////////////////////////////////////////////////
//
// PUBLIC
//
AM232X::AM232X(TwoWire *wire)
{
  _wire          = wire;
  //  reset() or begin() ?
  _humidity      = 0.0;
  _temperature   = 0.0;
  _humOffset     = 0.0;
  _tempOffset    = 0.0;
  _lastRead      = 0;
  _readDelay     = 2000;
  _suppressError = false;
}


#if defined (ESP8266) || defined(ESP32)
bool AM232X::begin(const uint8_t dataPin, const uint8_t clockPin)
{
  if ((dataPin < 255) && (clockPin < 255))
  {
    _wire->begin(dataPin, clockPin);
  } else {
    _wire->begin();
  }
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
  if (millis() - _lastRead < _readDelay)
  {
    return AM232X_READ_TOO_FAST;
  }
  _lastRead = millis();

  // READ HUMIDITY AND TEMPERATURE REGISTERS
  int rv = _readRegister(0x00, 4);
  if (rv < 0) return rv;

  if (rv != AM232X_OK)
  {
    if (_suppressError == false)
    {
      _humidity    = AM232X_INVALID_VALUE;
      _temperature = AM232X_INVALID_VALUE;
    }
    return rv;  // propagate error value
  }

  //  EXTRACT HUMIDITY AND TEMPERATURE
  _humidity = (_bits[2] * 256 + _bits[3]) * 0.1;
  int16_t t = ((_bits[4] & 0x7F) * 256 + _bits[5]);
  if (t == 0)
  {
    _temperature = 0.0;     // prevent -0.0;
  }
  else
  {
    _temperature = t * 0.1;
    if ((_bits[4] & 0x80) == 0x80 )
    {
      _temperature = -_temperature;
    }
  }

#ifdef AM232X_VALUE_OUT_OF_RANGE
  // TEST OUT OF RANGE
  if (_humidity > 100)
  {
    return AM232X_HUMIDITY_OUT_OF_RANGE;
  }
  if ((_temperature < -40) || (_temperature > 80))
  {
    return AM232X_TEMPERATURE_OUT_OF_RANGE;
  }
#endif

  return AM232X_OK;
}


float AM232X::getHumidity()
{
  float _hum = _humidity;
  if (_humOffset != 0.0) _hum += _humOffset;
  return _hum;
}


float AM232X::getTemperature()
{
  float _tem = _temperature;
  if (_tempOffset != 0.0) _tem += _tempOffset;
  return _tem;
}


void AM232X::setReadDelay(uint16_t rd)
{
  _readDelay = rd;
  if (_readDelay == 0)
  {
    _readDelay = 2000;  // reset
  }
};


int AM232X::getModel()
{
  int rv = _readRegister(0x08, 2);
  if (rv < 0) return rv;

  return (_bits[2] * 256) + _bits[3];
}


int AM232X::getVersion()
{
  int rv = _readRegister(0x0A, 1);
  if (rv < 0) return rv;

  return _bits[2];
}


uint32_t AM232X::getDeviceID()
{
  int rv = _readRegister(0x0B, 4);
  if (rv < 0) return rv;

  uint32_t _deviceID = (_bits[2] * 256) + _bits[3];
  _deviceID = _deviceID * 256 + _bits[4];
  _deviceID = _deviceID * 256 + _bits[5];
  return _deviceID;
}


int AM232X::getStatus()
{
  int rv = _readRegister(0x0F, 1);
  if (rv < 0) return rv;

  return _bits[2];
}


int AM232X::getUserRegisterA()
{
  int rv = _readRegister(0x10, 2);
  if (rv < 0) return rv;

  return (_bits[2] * 256) + _bits[3];
}


int AM232X::getUserRegisterB()
{
  int rv = _readRegister(0x12, 2);
  if (rv < 0) return rv;

  return (_bits[2] * 256) + _bits[3];
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
// PROTECTED
//
int AM232X::_readRegister(uint8_t reg, uint8_t count)
{
  // HANDLE PENDING IRQ
  yield();

  // WAKE UP the sensor
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
  _bits[0] = 0x10;
  _bits[1] = reg;
  _bits[2] = cnt;

  if (cnt == 2)
  {
    _bits[4] = value & 0xFF;
    _bits[3] = (value >> 8) & 0xFF;
  }
  else
  {
    _bits[3] = value & 0xFF;
  }

  // send data
  uint8_t length = cnt + 3;  // 3 = cmd, startReg, #bytes
  _wire->beginTransmission(AM232X_ADDRESS);
  for (int i = 0; i < length; i++)
  {
    _wire->write(_bits[i]);
  }
  // send the CRC
  uint16_t crc = _crc16(_bits, length);
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
  if (bytes == 0) return AM232X_ERROR_CONNECT;

  for (int i = 0; i < bytes; i++)
  {
    _bits[i] = _wire->read();
  }

  // ANALYZE ERRORS
  //   will not detect if we requested 1 byte as that will
  //   return 5 bytes as requested. E.g. getStatus()
  //   design a fix if it becomes a problem.
  if (bytes != length)
  {
    switch (_bits[3])
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
  uint16_t crc = _bits[bytes - 1] * 256 + _bits[bytes - 2];
  if (_crc16(&_bits[0], bytes - 2) != crc)
  {
    return AM232X_ERROR_CRC_2;  // read itself has wrong CRC
  }

  return AM232X_OK;
}


uint16_t AM232X::_crc16(uint8_t *ptr, uint8_t len)
{
  uint16_t crc = 0xFFFF;
  while(len--)
  {
    crc ^= *ptr++;
    for (uint8_t i = 0; i < 8; i++)
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



/////////////////////////////////////////////////////////////////////////////
//
// AM232X derived classes
//
AM2320::AM2320(TwoWire *wire) : AM232X(wire)
{
}


AM2321::AM2321(TwoWire *wire) : AM232X(wire)
{
}


AM2322::AM2322(TwoWire *wire) : AM232X(wire)
{
}



// -- END OF FILE --

