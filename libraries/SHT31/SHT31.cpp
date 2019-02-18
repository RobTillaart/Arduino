//
//    FILE: SHT31.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2019-02-08
// PURPOSE: Class for SHT31 I2C temperature humidity sensor
//          https://www.adafruit.com/product/2857
//
// HISTORY:
// 0.1.0 - 2019-02-08 initial version
//
// Released to the public domain
//

#include "SHT31.h"

#define SHT31_READ_STATUS       0xF32D
#define SHT31_CLEAR_STATUS      0x3041
#define SHT31_RESET             0x30A2
#define SHT31_MEASUREMENT_FAST  0x2416
#define SHT31_MEASUREMENT_SLOW  0x2400
#define SHT31_HEAT_ON           0x306D
#define SHT31_HEAT_OFF          0x3066


SHT31::SHT31()
{
  _addr = 0;
  _lastRead = 0;
  temperature = 0;
  humidity = 0;
}

bool SHT31::begin(const uint8_t address)
{
  if (address != 0x44 && address != 0x45) return false;
  _addr = address;
  reset();
  return true;
}

bool SHT31::read(bool fast)
{
  bool rv = true;
  uint8_t buffer[6];

  if (fast)
  {
    writeCmd(SHT31_MEASUREMENT_FAST);
    delay(4);  // table 4 datasheet
  }
  else
  {
    writeCmd(SHT31_MEASUREMENT_SLOW);
    delay(15);  // table 4 datasheet
  }
  readBytes(6, (uint8_t*) &buffer[0]);

  if (!fast)
  {
    // TODO 5 read bytes would be sufficient when not fast...
    // TODO check CRC here
    // TODO rv = false;
  }
  float raw = (buffer[0] << 8) + buffer[1];
  temperature = raw * (175.0 / 65535) - 45;
  raw = (buffer[3] << 8) + buffer[4];
  humidity = raw * (100.0 / 65535);

  _lastRead = millis();

  return rv;
}

uint16_t SHT31::readStatus()
{
  uint32_t status = 0;

  writeCmd(SHT31_READ_STATUS);
  readBytes(3, (uint8_t*) &status);
  return status;
}

// hard reset 0x0006 on addr 0x00 see datasheet
void SHT31::reset()
{
  writeCmd(SHT31_RESET);
  delay(1);  // table 4 datasheet
}

void SHT31::heatOn()
{
  writeCmd(SHT31_HEAT_ON);
}

void SHT31::heatOff()
{
  writeCmd(SHT31_HEAT_OFF);
}

//////////////////////////////////////////////////////////

void SHT31::writeCmd(uint16_t cmd)
{
  Wire.beginTransmission(_addr);
  Wire.write(cmd >> 8 );
  Wire.write(cmd & 0xFF);
  Wire.endTransmission();
}

void SHT31::readBytes(uint8_t n, uint8_t *val)
{
  Wire.requestFrom(_addr, (uint8_t) n);
  for (uint8_t i = 0; i < n; i++)
  {
    val[i] = Wire.read();
  }
}
// -- END OF FILE --