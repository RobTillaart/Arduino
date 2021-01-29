//
//    FILE: SHT31.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.0
//    DATE: 2019-02-08
// PURPOSE: Arduino library for the SHT31 temperature and humidity sensor
//          https://www.adafruit.com/product/2857
//     URL: https://github.com/RobTillaart/SHT31
//

//  HISTORY:
//  0.1.0   2019-02-08  initial version
//  0.1.1   2019-02-18  add description readStatus(),
//                      async interface
//  0.1.2   2019-03-05  fix issue #123 - error in humidity
//                      stable version
//  0.2.0   2020-05-12  made humidity & temperature private;
//                      support ESP32 I2C
//  0.2.1   2020-06-19  fix library.json
//  0.2.2   2020-07-05  fix compiling for ESP
//  0.2.3   2020-07-19  added CRC by PetrDa (thanks); cleanup
//  0.2.4   2020-11-29  added isConnected()
//  0.2.5   2020-12-02  added isHeaterOn() + unittest + arduino-ci
//  0.2.6   2021-01-01  patch version 0.2.6
//
//  0.3.0   2021-01-04  arduino-ci 


#include "SHT31.h"


// SUPPORTED COMMANDS - single shot mode only
#define SHT31_READ_STATUS       0xF32D
#define SHT31_CLEAR_STATUS      0x3041

#define SHT31_SOFT_RESET        0x30A2
#define SHT31_HARD_RESET        0x0006

#define SHT31_MEASUREMENT_FAST  0x2416    // page 10 datasheet
#define SHT31_MEASUREMENT_SLOW  0x2400    // no clock stretching

#define SHT31_HEAT_ON           0x306D
#define SHT31_HEAT_OFF          0x3066


SHT31::SHT31()
{
  _addr        = 0;
  _lastRead    = 0;
  temperature  = 0;
  humidity     = 0;
  _heaterStart = 0;
  _error       = SHT31_OK;
}


#if defined(ESP8266) || defined(ESP32)
bool SHT31::begin(const uint8_t address, const uint8_t dataPin, const uint8_t clockPin)
{
  if ((address != 0x44) && (address != 0x45))
  {
    return false;
  }
  _addr = address;

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


bool SHT31::begin(const uint8_t address)
{
  return begin(address, &Wire);
}


bool SHT31::begin(const uint8_t address,  TwoWire *wire)
{
  if ((address != 0x44) && (address != 0x45))
  {
    return false;
  }
  _addr = address;
  _wire = wire;
  _wire->begin();
  return reset();
}


bool SHT31::read(bool fast)
{
  if (writeCmd(fast ? SHT31_MEASUREMENT_FAST : SHT31_MEASUREMENT_SLOW) == false)
  {
    return false;
  }
  delay(fast ? 4 : 15); // table 4 datasheet
  return readData(fast);
}


bool SHT31::isConnected()
{
  _wire->beginTransmission(_addr);
  int rv = _wire->endTransmission();
  if (rv != 0) _error = SHT31_ERR_NOT_CONNECT;
  return (rv == 0);
}

#ifdef doc
// bit - description
// ==================
// 15 Alert pending status
//    '0': no pending alerts
//    '1': at least one pending alert - default
// 14 Reserved ‘0’
// 13 Heater status
//    '0’ : Heater OFF - default
//    '1’ : Heater ON
// 12 Reserved '0’
// 11 Humidity tracking alert
//    '0’ : no alert - default
//    '1’ : alert
// 10 Temp tracking alert
//    '0’ : no alert - default
//    '1’ : alert
// 9:5 Reserved '00000’
// 4 System reset detected
//    '0': no reset since last ‘clear status register’ command
//    '1': reset detected (hard or soft reset command or supply fail) - default
// 3:2 Reserved ‘00’
// 1 Command status
//    '0': last cmd executed successfully
//    '1': last cmd not processed. Invalid or failed checksum
// 0 Write data checksum status
//    '0': checksum of last write correct
//    '1': checksum of last write transfer failed
#endif


uint16_t SHT31::readStatus()
{
  uint8_t status[3] = { 0, 0, 0 };
  // page 13 datasheet
  if (writeCmd(SHT31_READ_STATUS) == false)
  {
    return 0xFFFF;
  }
  // 16 bit status + CRC
  if (readBytes(3, (uint8_t*) &status[0]) == false)
  {
    return 0xFFFF;
  }

  if (status[2] != crc8(status, 2)) 
  {
    _error = SHT31_ERR_CRC_STATUS;
    return 0xFFFF;
  }

  return (uint16_t) (status[0] << 8) + status[1];
}


bool SHT31::reset(bool hard)
{
  bool b = writeCmd(hard ? SHT31_HARD_RESET : SHT31_SOFT_RESET);
  if (b == false)
  {
    return false;
  }
  delay(1);  // table 4 datasheet
  return true;
}


void SHT31::setHeatTimeout(uint8_t seconds)
{
  _heatTimeOut = seconds;
  if (_heatTimeOut > 180) _heatTimeOut = 180;
}


bool SHT31::heatOn()
{
  if (writeCmd(SHT31_HEAT_ON) == false)
  {
    return false;
  }
  _heaterStart = millis();
  return true;
}


bool SHT31::heatOff()
{
  if (writeCmd(SHT31_HEAT_OFF) == false)
  {
    _error = SHT31_ERR_HEATER_OFF;  // can be serious!
    return false;
  }
  _heaterStart = 0;
  return true;
}


bool SHT31::isHeaterOn()
{
  if (_heaterStart == 0)
  {
    return false;
  }
  // did not exceed time out
  if (millis() - _heaterStart < (_heatTimeOut * 1000UL))
  {
    return true;
  }
  heatOff();     // should this be done here?
  return false;
}


bool SHT31::requestData()
{
  if (writeCmd(SHT31_MEASUREMENT_SLOW) == false)
  {
    return false;
  }
  _lastRequest = millis();
  return true;
}


bool SHT31::dataReady()
{
  return ((millis() - _lastRequest) > 15);  // TODO MAGIC NR
}


bool SHT31::readData(bool fast)
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
      _error = SHT31_ERR_CRC_TEMP;
      return false;
    }
    if (buffer[5] != crc8(buffer + 3, 2)) 
    {
      _error = SHT31_ERR_CRC_HUM;
      return false;
    }
  }

  uint16_t raw = (buffer[0] << 8) + buffer[1];
  temperature = raw * (175.0 / 65535) - 45;
  raw = (buffer[3] << 8) + buffer[4];
  humidity = raw * (100.0 / 65535);

  _lastRead = millis();

  return true;
}


int SHT31::getError()
{
  int rv = _error;
  _error = SHT31_OK;
  return rv;
}


//////////////////////////////////////////////////////////

uint8_t SHT31::crc8(const uint8_t *data, uint8_t len) 
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


bool SHT31::writeCmd(uint16_t cmd)
{
  _wire->beginTransmission(_addr);
  _wire->write(cmd >> 8 );
  _wire->write(cmd & 0xFF);
  if (_wire->endTransmission() != 0)
  {
    _error = SHT31_ERR_WRITECMD;
    return false;
  }
  return true;
}


bool SHT31::readBytes(uint8_t n, uint8_t *val)
{
  int rv = _wire->requestFrom(_addr, (uint8_t) n);
  if (rv == n)
  {
    for (uint8_t i = 0; i < n; i++)
    {
      val[i] = _wire->read();
    }
    return true;
  }
  _error = SHT31_ERR_READBYTES;
  return false;
}

// -- END OF FILE --
