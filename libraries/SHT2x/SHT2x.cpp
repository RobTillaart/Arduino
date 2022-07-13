//
//    FILE: SHT2x.cpp
//  AUTHOR: Rob Tillaart, Viktor Balint
// VERSION: 0.2.0
//    DATE: 2021-09-25
// PURPOSE: Arduino library for the SHT2x temperature and humidity sensor
//     URL: https://github.com/RobTillaart/SHT2x
//

//  HISTORY:
//  0.1.0   2021-09-25  initial version
//  0.1.1   2021-09-28  Add HTU2x derived classes,
//                      update readme.md + add some status info
//  0.1.2   2021-09-29  Add Si70xx derived classes
//                      add getEIDA(), getEIDB(), getFirmwareVersion()
//                      update build-CI, readme.md badges
//  0.1.3   2021-12-28  update library.json, license, minor edits
//  0.1.4   2022-06-21  Fix #9 ESP32 wire.begin()
//                      Fix getEIDB() bug.
//
//  0.2.0   2022-07-10  Fix #11 RawTemp + rawHum (kudos to theandy94)
//                      add experimental getResolution() + setResolution()
//                      adjust read delay
//                      add experimental batteryOK()
//                      add CRC in read() - no fail.


#include "SHT2x.h"


//  SUPPORTED COMMANDS
#define SHT2x_GET_TEMPERATURE_NO_HOLD   0xF3
#define SHT2x_GET_HUMIDITY_NO_HOLD      0xF5
#define SHT2x_SOFT_RESET                0xFE
#define SHT2x_WRITE_USER_REGISTER       0xE6
#define SHT2x_READ_USER_REGISTER        0xE7

#define SHT2x_HEATER_TIMEOUT            180000UL  // milliseconds

#define SHT2x_ADDRESS                   0x40


#define SHT2x_USRREG_RESOLUTION         0x81
#define SHT2x_USRREG_BATTERY            0x20
#define SHT2x_USRREG_HEATER             0x04


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
  _resolution     = 0;
}


#if defined(ESP8266) || defined(ESP32)
bool SHT2x::begin(const int dataPin, const int clockPin)
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
  //  table 7 
  if      (_resolution == 3) delay(11);  //  11 bit
  else if (_resolution == 1) delay(22);  //  12 bit
  else if (_resolution == 2) delay(43);  //  13 bit
  else                       delay(85);  //  14 bit

  if (readBytes(3, (uint8_t*) &buffer[0], 90) == false)
  {
    _error = SHT2x_ERR_READBYTES;
    return false;
  }
  if (crc8(buffer, 2) != buffer[2])
  {
    _error = SHT2x_ERR_CRC_TEMP;
  //  return false;  // do not fail yet
  }
  _rawTemperature  = buffer[0] << 8;
  _rawTemperature += buffer[1];
  _rawTemperature &= 0xFFFC;

  _status = buffer[1] & 0x0003;
  if (_status == 0xFF)  // TODO  != 0x01  (need HW to test)
  {
    _error = SHT2x_ERR_READBYTES;
    return false;
  }

  //  HUMIDITY
  writeCmd(SHT2x_GET_HUMIDITY_NO_HOLD);
  //  table 7 
  if      (_resolution == 1) delay(4);   //   8 bit
  else if (_resolution == 2) delay(9);   //  10 bit
  else if (_resolution == 3) delay(15);  //  11 bit
  else                       delay(29);  //  12 bit

  if (readBytes(3, (uint8_t*) &buffer[0], 30) == false)
  {
    return false;
  }
  if (crc8(buffer, 2) != buffer[2])
  {
    _error = SHT2x_ERR_CRC_HUM;
  //    return false;  // do not fail yet
  }
  _rawHumidity  = buffer[0] << 8;
  _rawHumidity += buffer[1];
  _rawHumidity &= 0xFFFC;     //  TODO is this mask OK? as humidity is max 12 bit..

  _status = buffer[1] & 0x0003;
  if (_status == 0xFF)        //  TODO  != 0x02  (need HW to test)
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
  return b;
}


uint8_t SHT2x::getStatus()
{
  return _status;
}


//  HEATER

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

  //  HEAT BIT ON
  userReg |= SHT2x_USRREG_HEATER;

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

  //  HEAT BIT OFF
  userReg &= ~SHT2x_USRREG_HEATER;

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


bool SHT2x::setHeaterLevel(uint8_t level)
{
  if (level > 15)
  {
    return false;
  }

  uint8_t heaterReg = 0;
  writeCmd(0x11);  // Read Heater Control Register
  if (readBytes(1, (uint8_t *) &heaterReg, 5) == false)
  {
    _error = SHT2x_ERR_READBYTES;
    return false;
  }
  heaterReg &= 0xF0;
  heaterReg |= level;
  if (writeCmd(0x51, heaterReg) == false)
  {
    _error = -1;
    return false;
  }
  return true;
}


bool SHT2x::getHeaterLevel(uint8_t & level)
{
  uint8_t heaterReg = 0;
  writeCmd(0x11);  // Read Heater Control Register
  if (readBytes(1, (uint8_t *) &heaterReg, 5) == false)
  {
    _error = SHT2x_ERR_READBYTES;
    return false;
  }
  level = heaterReg & 0x0F;
  return true;
}


int SHT2x::getError()
{
  int rv = _error;
  _error = SHT2x_OK;
  return rv;
}


//  Sensirion_Humidity_SHT2x_Electronic_Identification_Code_V1.1.pdf
uint32_t SHT2x::getEIDA()
{
  uint32_t id = 0;
  uint8_t buffer[8];
  writeCmd(0xFA, 0x0F);
  if (readBytes(8, (uint8_t *) buffer, 10) == false)
  {
    _error = SHT2x_ERR_READBYTES;
    return false;
  }
  //  skip CRC's
  for (uint8_t i = 0; i < 4; i++)
  {
    id <<= 8;
    id |= buffer[i*2];
  }
  return id;
}


//  Sensirion_Humidity_SHT2x_Electronic_Identification_Code_V1.1.pdf
uint32_t SHT2x::getEIDB()
{
  uint32_t id = 0;
  uint8_t buffer[8];
  writeCmd(0xFC, 0xC9);
  if (readBytes(8, (uint8_t *) buffer, 10) == false)
  {
    _error = SHT2x_ERR_READBYTES;
    return false;
  }
  //  skip CRC's
  id  = buffer[0];  //  SNC_1
  id <<= 8;
  id |= buffer[1];  //  SNC_0
  id <<= 8;
  id |= buffer[3];  //  SNA_1
  id <<= 8;
  id |= buffer[4];  //  SNA_0
  return id;
}


uint8_t SHT2x::getFirmwareVersion()
{
  uint8_t version = 0;
  writeCmd(0x84, 0xB8);
  if (readBytes(1, (uint8_t *) &version, 10) == false)
  {
    _error = SHT2x_ERR_READBYTES;
    return false;
  }
  return version;
}


bool SHT2x::setResolution(uint8_t res)
{
  if (res > 3) return false;

  uint8_t userReg = 0x00;
  writeCmd(SHT2x_READ_USER_REGISTER);
  if (readBytes(1, (uint8_t *) &userReg, 5) == false)
  {
    _error = SHT2x_ERR_READBYTES;
    return false;
  }

  //  clear old resolution and set new
  userReg &= ~SHT2x_USRREG_RESOLUTION;
  //  resolution is bit 7 and bit 0.
  userReg |= ((res & 0x02) << 6);
  userReg |= (res & 0x01);

  if (writeCmd(SHT2x_READ_USER_REGISTER, userReg) == false)
  {
    _error = SHT2x_ERR_RESOLUTION;
    return false;
  }
  _resolution = res;
  return true;
}


uint8_t SHT2x::getResolution()
{
  return _resolution;
};


bool SHT2x::batteryOK()
{
  uint8_t userReg = 0x00;
  writeCmd(SHT2x_READ_USER_REGISTER);
  if (readBytes(1, (uint8_t *) &userReg, 5) == false)
  {
    _error = SHT2x_ERR_READBYTES;
    return false;
  }
  return (userReg & SHT2x_USRREG_BATTERY) == 0;
}




//////////////////////////////////////////////////////////
//
//  PRIVATE
//
uint8_t SHT2x::crc8(const uint8_t *data, uint8_t len)
{
  // CRC-8 formula from page 14 of SHT spec pdf
  // Sensirion_Humidity_Sensors_SHT2x_CRC_Calculation.pdf
  const uint8_t POLY = 0x31;
  uint8_t crc = 0x00;

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
//  DERIVED SHT
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


////////////////////////////////////////////////////////
//
//  DERIVED HTU
//
HTU20::HTU20()
{
};


HTU21::HTU21()
{
};


////////////////////////////////////////////////////////
//
//  DERIVED Si70xx
//
Si7013::Si7013()
{
};


Si7020::Si7020()
{
};


Si7021::Si7021()
{
};



// -- END OF FILE --
