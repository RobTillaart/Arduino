//
//    FILE: SHT2x.cpp
//  AUTHOR: Rob Tillaart, Viktor Balint
// VERSION: 0.1.0
//    DATE: 2021-09-25
// PURPOSE: Arduino library for the SHT2x temperature and humidity sensor
//     URL: https://github.com/RobTillaart/SHT2x
//

//  HISTORY:
//  0.1.0   2021-09-25  initial version


#include "SHT2x.h"


//  SUPPORTED COMMANDS
#define SHT2x_GET_TEMPERATURE_NO_HOLD   0xF3
#define SHT2x_GET_HUMIDITY_NO_HOLD      0xF5
#define SHT2x_SOFT_RESET                0xFE
#define SHT2x_WRITE_USER_REGISTER       0xE6
#define SHT2x_READ_USER_REGISTER        0xE7

#define SHT2x_HEATER_TIMEOUT            180000UL  // milliseconds

#define SHT2x_ADDRESS                   0x40


SHT2x::SHT2x()
{
  _lastRead       = 0;
  _rawTemperature = 0;
  _rawHumidity    = 0;
  _heatTimeout    = 0;
  _heaterStart    = 0;
  _heaterStop     = 0;
  _heaterOn       = false;
  _error          = SHT2x_OK;
  _status         = 0;
}


#if defined(ESP8266) || defined(ESP32)
bool SHT2x::begin(const uint8_t dataPin, const uint8_t clockPin)
{
  _wire = &Wire;
  if ((dataPin < 255) && (clockPin < 255))
  {
    _wire->begin(dataPin, clockPin);
  } else {
    _wire->begin();
  }
  return reset();
}
#endif


bool SHT2x::begin(TwoWire *wire)
{
  _wire = wire;
  _wire->begin();
  return reset();
}


bool SHT2x::isConnected()
{
  _wire->beginTransmission(SHT2x_ADDRESS);
  int rv = _wire->endTransmission();
  if (rv != 0) _error = SHT2x_ERR_NOT_CONNECT;
  return (rv == 0);
}


bool SHT2x::read()
{
  uint8_t buffer[3];

  //  TEMPERATURE
  writeCmd(SHT2x_GET_TEMPERATURE_NO_HOLD);
  delay(70);
  if (readBytes(3, (uint8_t*) &buffer[0], 90) == false)
  {
    _error = SHT2x_ERR_READBYTES;
    return false;
  }
  // TODO CRC8 check
  // error = SHT2x_ERR_CRC_TEMP;
  _rawTemperature = buffer[0] << 8;
  _rawTemperature += buffer[1];
  _rawTemperature &= 0xFFFC;

  _status = buffer[1] & 0x0003;
  if (_status == 0xFF)
  {
    _error = SHT2x_ERR_READBYTES;
    return false;
  }

  //  HUMIDITY
  writeCmd(SHT2x_GET_HUMIDITY_NO_HOLD);
  delay(30);
  if (readBytes(3, (uint8_t*) &buffer[0], 30) == false)
  {
    return false;
  }
  // TODO CRC8 check
  // _error = SHT2x_ERR_CRC_HUM;
  _rawHumidity = buffer[0] << 8;
  _rawHumidity += buffer[1];
  _rawHumidity &= 0xFFFC; 

  _status = buffer[1] & 0x0003;
  if (_status == 0xFF)
  {
    _error = SHT2x_ERR_READBYTES;
    return false;
  }

  _error = SHT2x_OK;
  _lastRead = millis();
  return true;
}


float SHT2x::getTemperature()
{
  // par 6.2
  return -46.85 + (175.72 / 65536.0) * _rawTemperature;
}


float SHT2x::getHumidity()
{
  // par  6.1
  return -6.0 + (125.0 / 65536.0) * _rawHumidity;
}


bool SHT2x::reset()
{
  bool b = writeCmd(SHT2x_SOFT_RESET);
  if (b == false) return false;
  return true;
}


uint8_t SHT2x::getStatus()
{
  return _status;   // TODO meaning
}


void SHT2x::setHeatTimeout(uint8_t seconds)
{
  _heatTimeout = seconds;
  if (_heatTimeout > 180) _heatTimeout = 180;
}


bool SHT2x::heatOn()
{
  if (isHeaterOn()) return true;
  if ((_heaterStop > 0) && (millis() - _heaterStop < SHT2x_HEATER_TIMEOUT))
  {
    _error = SHT2x_ERR_HEATER_COOLDOWN;
    return false;
  }

  uint8_t userReg = 0x00;
  writeCmd(SHT2x_READ_USER_REGISTER);
  if (readBytes(1, (uint8_t *) &userReg, 5) == false)
  {
    _error = SHT2x_ERR_READBYTES;
    return false;
  }
  userReg |= 0x04;      // HEAT BIT ON

  if (writeCmd(SHT2x_READ_USER_REGISTER, userReg) == false)
  {
    _error = SHT2x_ERR_HEATER_ON;
    return false;
  }
  _heaterStart = millis();
  _heaterOn    = true;
  return true;
}


bool SHT2x::heatOff()
{
  uint8_t userReg = 0x00;
  writeCmd(SHT2x_READ_USER_REGISTER);
  if (readBytes(1, (uint8_t *) &userReg, 5) == false)
  {
    _error = SHT2x_ERR_READBYTES;
    return false;
  }
  userReg &= ~0x04;      // HEAT BIT OFF
  if (writeCmd(SHT2x_READ_USER_REGISTER, userReg) == false)
  {
    _error = SHT2x_ERR_HEATER_OFF;  // can be serious!
    return false;
  }
  _heaterStop = millis();
  _heaterOn   = false;
  return true;
}


bool SHT2x::isHeaterOn()
{
  if (_heaterOn == false)
  {
    return false;
  }
  // did not exceed time out
  if (millis() - _heaterStart < (_heatTimeout * 1000UL))
  {
    return true;
  }
  heatOff();
  return false;
}


int SHT2x::getError()
{
  int rv = _error;
  _error = SHT2x_OK;
  return rv;
}


//////////////////////////////////////////////////////////
//
//  PRIVATE
//
uint8_t SHT2x::crc8(const uint8_t *data, uint8_t len) 
{
  // CRC-8 formula from page 14 of SHT spec pdf
  const uint8_t POLY(0x31);
  uint8_t crc(0xFF);

  for (uint8_t j = len; j; --j) 
  {
    crc ^= *data++;

    for (uint8_t i = 8; i; --i) 
    {
      crc = (crc & 0x80) ? (crc << 1) ^ POLY : (crc << 1);
    }
  }
  return crc;
}


bool SHT2x::writeCmd(uint8_t cmd)
{
  _wire->beginTransmission(SHT2x_ADDRESS);
  _wire->write(cmd);
  if (_wire->endTransmission() != 0)
  {
    _error = SHT2x_ERR_WRITECMD;
    return false;
  }
  return true;
}


bool SHT2x::writeCmd(uint8_t cmd, uint8_t value)
{
  _wire->beginTransmission(SHT2x_ADDRESS);
  _wire->write(cmd);
  _wire->write(value);
  if (_wire->endTransmission() != 0)
  {
    _error = SHT2x_ERR_WRITECMD;
    return false;
  }
  return true;
}


bool SHT2x::readBytes(uint8_t n, uint8_t *val, uint8_t maxDuration)
{
  _wire->requestFrom((uint8_t)SHT2x_ADDRESS, (uint8_t) n);
  uint32_t start = millis();
  while (_wire->available() < n)
  {
    if (millis() - start > maxDuration) 
    {
      _error = SHT2x_ERR_READBYTES;
      return false;
    }
    yield();
  }

  for (uint8_t i = 0; i < n; i++)
  {
    val[i] = _wire->read();
  }
  _error = SHT2x_OK;
  return true;
}


////////////////////////////////////////////////////////
//
// DERIVED
//
SHT20::SHT20()
{
};


SHT21::SHT21()
{
};


SHT25::SHT25()
{
};



// -- END OF FILE --
