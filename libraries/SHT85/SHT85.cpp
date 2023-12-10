//
//    FILE: SHT85.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.6.0
//    DATE: 2021-02-10
// PURPOSE: Arduino library for the SHT85 temperature and humidity sensor
//          https://nl.rs-online.com/web/p/temperature-humidity-sensor-ics/1826530
//     URL: https://github.com/RobTillaart/SHT85



#include "SHT85.h"


//  SUPPORTED COMMANDS - single shot mode only
#define SHT_READ_STATUS       0xF32D
#define SHT_CLEAR_STATUS      0x3041

#define SHT_SOFT_RESET        0x30A2
#define SHT_HARD_RESET        0x0006

#define SHT_MEASUREMENT_FAST  0x2416    //  page 10 datasheet
#define SHT_MEASUREMENT_SLOW  0x2400    //  no clock stretching

#define SHT_HEAT_ON           0x306D
#define SHT_HEAT_OFF          0x3066
#define SHT_HEATER_TIMEOUT    180000UL  //  milliseconds

#define SHT_GET_SERIAL        0x3682


SHT::SHT(uint8_t address, TwoWire *wire)
{
  _address           = address;
  _wire              = wire;
  _lastRead          = 0;
  _rawTemperature    = 0;
  _rawHumidity       = 0;
  _heatTimeout       = 0;
  _heaterStart       = 0;
  _heaterStop        = 0;
  _heaterOn          = false;
  _error             = SHT_OK;
  _type              = 0;
  _temperatureOffset = 0;
  _humidityOffset    = 0;
}


bool SHT::begin()
{
  if ((_address != 0x44) && (_address != 0x45))
  {
    return false;
  }
  return reset();
}


uint8_t SHT::getAddress()
{
  return _address;
};


uint8_t SHT::getType()
{
  return _type;
};


///////////////////////////////////////////////////
//
//  SYNCHRONUOUS interface
//
bool SHT::read(bool fast)
{
  //  prevent error on failed request.
  if (requestData(fast) == false)
  {
    return false;
  }
  while(dataReady(fast) == false) yield();
  return readData(fast);
}


///////////////////////////////////////////////////
//
//  ASYNCHRONUOUS interface
//
bool SHT::requestData(bool fast)
{
  if (writeCmd(fast ? SHT_MEASUREMENT_FAST : SHT_MEASUREMENT_SLOW) == false)
  {
    return false;
  }
  _lastRequest = millis();
  return true;
}


bool SHT::dataReady(bool fast)
{
  return ((millis() - _lastRequest) > (fast ? 4 : 15));
}


bool SHT::readData(bool fast)
{
  uint8_t buffer[6];
  if (readBytes(6, (uint8_t*) &buffer[0]) == false)
  {
    return false;
  }

  if (!fast)
  {
    if (buffer[2] != crc8(buffer, 2))
    {
      _error = SHT_ERR_CRC_TEMP;
      return false;
    }
    if (buffer[5] != crc8(buffer + 3, 2))
    {
      _error = SHT_ERR_CRC_HUM;
      return false;
    }
  }

  _rawTemperature = (buffer[0] << 8) + buffer[1];
  _rawHumidity    = (buffer[3] << 8) + buffer[4];

  _lastRead = millis();

  _error = SHT_OK;
  return true;
}


uint32_t SHT::lastRequest()
{
  return _lastRequest;
};


///////////////////////////////////////////////////
//
//  STATUS
//
bool SHT::isConnected()
{
  _wire->beginTransmission(_address);
  int rv = _wire->endTransmission();
  if (rv != 0)
  {
    _error = SHT_ERR_NOT_CONNECT;
    return false;
  }
  _error = SHT_OK;
  return true;
}


#ifdef doc
//  bit - description
//  ==================
//  15  Alert pending status
//        '0': no pending alerts
//        '1': at least one pending alert - default
//  14  Reserved ‘0’
//  13  Heater status
//        '0’ : Heater OFF - default
//        '1’ : Heater ON
//  12  Reserved '0’
//  11  Humidity tracking alert
//        '0’ : no alert - default
//        '1’ : alert
//  10  Temp tracking alert
//        '0’ : no alert - default
//        '1’ : alert
//  9:5 Reserved '00000’
//  4   System reset detected
//        '0': no reset since last ‘clear status register’ command
//        '1': reset detected (hard or soft reset command or supply fail) - default
//  3:2 Reserved ‘00’
//  1   Command status
//        '0': last command executed successfully
//        '1': last command not processed. Invalid or failed checksum
//  0   Write data checksum status
//        '0': checksum of last write correct
//        '1': checksum of last write transfer failed
#endif


uint16_t SHT::readStatus()
{
  uint8_t status[3] = { 0, 0, 0 };
  //  page 13 datasheet
  if (writeCmd(SHT_READ_STATUS) == false)
  {
    return 0xFFFF;
  }
  //  16 bit status + CRC
  if (readBytes(3, (uint8_t*) &status[0]) == false)
  {
    return 0xFFFF;
  }

  if (status[2] != crc8(status, 2))
  {
    _error = SHT_ERR_CRC_STATUS;
    return 0xFFFF;
  }
  return (uint16_t) (status[0] << 8) + status[1];
}


uint32_t SHT::lastRead()
{
  return _lastRead;
};


bool SHT::reset(bool hard)
{
  bool b = writeCmd(hard ? SHT_HARD_RESET : SHT_SOFT_RESET);
  if (b == false)
  {
    return false;
  }
  delay(1);     //  table 4 datasheet
  return true;
}


int SHT::getError()
{
  int rv = _error;
  _error = SHT_OK;
  return rv;
}


///////////////////////////////////////////////////
//
//  HEATER
//
void SHT::setHeatTimeout(uint8_t seconds)
{
  _heatTimeout = seconds;
  if (_heatTimeout > 180) _heatTimeout = 180;
}


uint8_t SHT::getHeatTimeout()
{
  return _heatTimeout;
};


bool SHT::heatOn()
{
  if (isHeaterOn()) return true;
  if ((_heaterStop > 0) && (millis() - _heaterStop < SHT_HEATER_TIMEOUT))
  {
    _error = SHT_ERR_HEATER_COOLDOWN;
    return false;
  }
  if (writeCmd(SHT_HEAT_ON) == false)
  {
    _error = SHT_ERR_HEATER_ON;  //  more specific error!
    return false;
  }
  _heaterStart = millis();
  _heaterOn    = true;
  return true;
}


bool SHT::heatOff()
{
  //  always switch off the heater - ignore _heaterOn flag.
  if (writeCmd(SHT_HEAT_OFF) == false)
  {
    _error = SHT_ERR_HEATER_OFF;   //  can be serious!
    return false;
  }
  _heaterStop = millis();
  _heaterOn   = false;
  return true;
}


bool SHT::isHeaterOn()
{
  if (_heaterOn == false)
  {
    return false;
  }
  //  did not exceed time out
  if (millis() - _heaterStart < (_heatTimeout * 1000UL))
  {
    return true;
  }
  heatOff();
  return false;
}


//////////////////////////////////////////////////////////
//
//  TEMPERATURE & HUMIDITY
//
float SHT::getHumidity()
{
  float hum = _rawHumidity * (100.0 / 65535);
  if (_humidityOffset != 0) hum += _humidityOffset;
  return hum;
}


float SHT::getTemperature()
{
  float temp = _rawTemperature * (175.0 / 65535) - 45;
  if (_temperatureOffset != 0) temp += _temperatureOffset;
  return temp;
}


float SHT::getFahrenheit()
{
  float temp = _rawTemperature * (63.0 / 13107.0) - 49;
  if (_temperatureOffset != 0) temp += _temperatureOffset * 1.8;
  return temp;
}


uint16_t SHT::getRawHumidity()
{
  return _rawHumidity;
}


uint16_t SHT::getRawTemperature()
{
  return _rawTemperature;
}


void  SHT::setTemperatureOffset(float offset)
{
  _temperatureOffset = offset;
}


float SHT::getTemperatureOffset()
{
  return _temperatureOffset;
}


void  SHT::setHumidityOffset(float offset)
{
  _humidityOffset = offset;
}


float SHT::getHumidityOffset()
{
  return _humidityOffset;
}


//////////////////////////////////////////////////////////
//
//  PROTECTED
//
uint8_t SHT::crc8(const uint8_t *data, uint8_t len)
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


bool SHT::writeCmd(uint16_t cmd)
{
  _wire->beginTransmission(_address);
  _wire->write(cmd >> 8 );
  _wire->write(cmd & 0xFF);
  if (_wire->endTransmission() != 0)
  {
    _error = SHT_ERR_WRITECMD;
    return false;
  }
  _error = SHT_OK;
  return true;
}


bool SHT::readBytes(uint8_t n, uint8_t *val)
{
  int rv = _wire->requestFrom(_address, (uint8_t) n);
  if (rv != n)
  {
    _error = SHT_ERR_READBYTES;
    return false;
  }
  for (uint8_t i = 0; i < n; i++)
  {
    val[i] = _wire->read();
  }
  _error = SHT_OK;
  return true;
}


////////////////////////////////////////////////////////
//
//  DERIVED CLASSES
//
SHT30::SHT30(uint8_t address, TwoWire *wire) : SHT(address, wire)
{
  _type = 30;
}


SHT31::SHT31(uint8_t address, TwoWire *wire) : SHT(address, wire)
{
  _type = 31;
}


SHT35::SHT35(uint8_t address, TwoWire *wire) : SHT(address, wire)
{
  _type = 35;
}


SHT85::SHT85(uint8_t address, TwoWire *wire) : SHT(address, wire)
{
  _type = 85;
}


bool SHT85::begin()
{
  if (_address != 0x44) return false;
  return SHT::begin();
}


uint32_t SHT85::GetSerialNumber()
{
  uint8_t bytes[6];

  if (writeCmd(SHT_GET_SERIAL) == false)
  {
    return 0xFFFFFFF0;
  }
  delayMicroseconds(500);  //  timing sensitive.
  if (readBytes(6, (uint8_t*) &bytes[0]) == false)
  {
    _error = SHT_ERR_SERIAL;
    return 0xFFFFFFFF;
  }
  //  check CRC
  //  todo
  //  combine bytes to serial.
  uint32_t serial = bytes[0];
  serial <<= 8;
  serial += bytes[1];
  serial <<= 8;
  serial += bytes[3];
  serial <<= 8;
  serial += bytes[4];
  return serial;
}


//  -- END OF FILE --

