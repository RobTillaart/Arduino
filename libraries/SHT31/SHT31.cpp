//
//    FILE: SHT31.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.2
//    DATE: 2019-02-08
// PURPOSE: Arduino library for the SHT31 temperature and humidity sensor
//          https://www.adafruit.com/product/2857
//     URL: https://github.com/RobTillaart/SHT31
//
// HISTORY:
// 0.1.0   2019-02-08 initial version
// 0.1.1   2019-02-18 add description readStatus(),
//                    async interface
// 0.1.2   2019-03-05 fix issue #123 - error in humidity
//                    stable version
// 0.2.0   2020-05-12 made humidity & temperature private;
//                    support ESP32 I2C
// 0.2.1   2020-06-19 fix library.json
// 0.2.2   2020-07-05 fix compiling for ESP


#include "SHT31.h"

// SUPPORTED COMMANDS - single shot mode only
#define SHT31_READ_STATUS       0xF32D
#define SHT31_CLEAR_STATUS      0x3041

#define SHT31_SOFT_RESET        0x30A2
#define SHT31_HARD_RESET        0x0006

#define SHT31_MEASUREMENT_FAST  0x2416	// page 10 datasheet
#define SHT31_MEASUREMENT_SLOW  0x2400	// no clock stretching

#define SHT31_HEAT_ON           0x306D
#define SHT31_HEAT_OFF          0x3066


SHT31::SHT31()
{
  _addr = 0;
  _lastRead = 0;
  temperature = 0;
  humidity = 0;
  _heaterStart = 0;
}

#if defined(ESP8266) || defined(ESP32)
bool SHT31::begin(const uint8_t address, const uint8_t dataPin, const uint8_t clockPin)
{
  if (address != 0x44 && address != 0x45) return false;
  _addr = address;

  _wire = &Wire;
  if ((dataPin < 255) && (clockPin < 255))
  {
    _wire->begin(dataPin, clockPin);
  } else {
    _wire->begin();
  }
  reset();
  return true;
}
#endif

bool SHT31::begin(const uint8_t address)
{
  return begin(address, &Wire);
}

bool SHT31::begin(const uint8_t address,  TwoWire *wire)
{
  if (address != 0x44 && address != 0x45) return false;
  _addr = address;
  _wire = wire;
  _wire->begin();
  reset();
  return true;
}

bool SHT31::read(bool fast)
{
  writeCmd(fast ? SHT31_MEASUREMENT_FAST : SHT31_MEASUREMENT_SLOW);
  delay(fast ? 4 : 15); // table 4 datasheet
  return readData(fast);
}

uint16_t SHT31::readStatus()
{
  uint32_t status = 0;
  writeCmd(SHT31_READ_STATUS);        // page 13 datasheet
  readBytes(3, (uint8_t*) &status);   // 16 bit status + CRC
  // TODO CRC check

  return (uint16_t) (status >> 8);

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
}

void SHT31::reset(bool hard)
{
  if (hard)
  {
    writeCmd(SHT31_HARD_RESET);
  } else {
    writeCmd(SHT31_SOFT_RESET);
  }
  delay(1);  // table 4 datasheet
}

void SHT31::setHeatTimeout(uint8_t seconds)
{
  _heatTimeOut = seconds;
  if (_heatTimeOut > 180) _heatTimeOut = 180;
}

void SHT31::heatOn()
{
  writeCmd(SHT31_HEAT_ON);
  _heaterStart = millis();
}

void SHT31::heatOff()
{
  writeCmd(SHT31_HEAT_OFF);
  _heaterStart = 0;
}

bool SHT31::heatUp()
{
  if (_heaterStart == 0) return false;
  // did not exceed time out
  if (millis() - _heaterStart < (_heatTimeOut * 1000UL)) return true;
  heatOff();
  return false;
}

void SHT31::requestData()
{
  writeCmd(SHT31_MEASUREMENT_SLOW);
  _lastRequest = millis();
}

bool SHT31::dataReady()
{
  return ((millis() - _lastRequest) > 15);
}

bool SHT31::readData(bool fast)
{
  uint8_t buffer[6];
  readBytes(6, (uint8_t*) &buffer[0]);

  if (!fast)
  {
    if (buffer[2] != crc8(buffer, 2) ||
        buffer[5] != crc8(buffer + 3, 2)) 
    {
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

//////////////////////////////////////////////////////////

uint8_t SHT31::crc8(const uint8_t *data, int len) 
{
  // CRC-8 formula from page 14 of SHT spec pdf
  const uint8_t POLY(0x31);
  uint8_t crc(0xFF);

  for (int j = len; j; --j) 
  {
    crc ^= *data++;

    for (int i = 8; i; --i) 
    {
      crc = (crc & 0x80) ? (crc << 1) ^ POLY : (crc << 1);
    }
  }
  return crc;
}

void SHT31::writeCmd(uint16_t cmd)
{
  _wire->beginTransmission(_addr);
  _wire->write(cmd >> 8 );
  _wire->write(cmd & 0xFF);
  _wire->endTransmission();
}

void SHT31::readBytes(uint8_t n, uint8_t *val)
{
  _wire->requestFrom(_addr, (uint8_t) n);
  for (uint8_t i = 0; i < n; i++)
  {
    val[i] = _wire->read();
  }
}

// -- END OF FILE --
