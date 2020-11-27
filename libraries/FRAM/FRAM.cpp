//
//    FILE: FRAM.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.1
//    DATE: 2018-01-24
// PURPOSE: Arduino library for I2C FRAM
//     URL: https://github.com/RobTillaart/FRAM_I2C
//
// HISTORY:
// 0.1.0    2018-01-24 initial version
// 0.1.1    2019-07-31 added suppport for Fujitsu 64Kbit MB85RC64T (kudos ysoyipek)
// 0.2.0    2020-04-30 refactor, add writeProtectPin code
// 0.2.1    2020-06-10 fix library.json

#include "FRAM.h"

const uint8_t FRAM_SLAVE_ID_= 0x7C;

/////////////////////////////////////////////////////
//
// PUBLIC
//
FRAM::FRAM()
{}

int FRAM::begin(uint8_t address, int8_t writeProtectPin)
{
  if (address < 0x50 || address > 0x57)
  {
    return FRAM_ERROR_ADDR;
  }

  _address = address;
  Wire.begin();

  if (writeProtectPin > -1)
  {
    _writeProtectPin = writeProtectPin;
    pinMode(_writeProtectPin, OUTPUT);
  }
  return FRAM_OK;
}

void FRAM::write8(uint16_t memaddr, uint8_t value)
{
  uint8_t val = value;
  writeBlock(memaddr, (uint8_t *)&val, 1);
}

void FRAM::write16(uint16_t memaddr, uint16_t value)
{
  uint16_t val = value;
  writeBlock(memaddr, (uint8_t *)&val, 2);
}

void FRAM::write32(uint16_t memaddr, uint32_t value)
{
  uint32_t val = value;
  writeBlock(memaddr, (uint8_t *)&val, 4);
}

void FRAM::write(uint16_t memaddr, uint8_t * obj, uint16_t size)
{
  const int blocksize = 24;
  uint8_t * p = obj;
  while (size >= blocksize)
  {
    writeBlock(memaddr, p, blocksize);
    memaddr += blocksize;
    p += blocksize;
    size -= blocksize;
  }
  // remaining
  if (size > 0)
  {
    writeBlock(memaddr, p, size);
  }
}

uint8_t FRAM::read8(uint16_t memaddr)
{
  uint8_t val;
  readBlock(memaddr, (uint8_t *)&val, 1);
  return val;
}

uint16_t FRAM::read16(uint16_t memaddr)
{
  uint16_t val;
  readBlock(memaddr, (uint8_t *)&val, 2);
  return val;
}

uint32_t FRAM::read32(uint16_t memaddr)
{
  uint32_t val;
  readBlock(memaddr, (uint8_t *)&val, 4);
  return val;
}

void FRAM::read(uint16_t memaddr, uint8_t * obj, uint16_t size)
{
  const uint8_t blocksize = 24;
  uint8_t * p = obj;
  while (size >= blocksize)
  {
    readBlock(memaddr, p, blocksize);
    memaddr += blocksize;
    p += blocksize;
    size -= blocksize;
  }
  // remainder
  if (size > 0)
  {
    readBlock(memaddr, p, size);
  }
}

bool FRAM::setWriteProtect(bool b)
{
  if (_writeProtectPin == -1) return false;
  digitalWrite(_writeProtectPin, b ? HIGH : LOW);
  return true;
}

uint16_t FRAM::getManufacturerID()
{
  return getMetaData(0);
}

uint16_t FRAM::getProductID()
{
  return getMetaData(1);
}

uint16_t FRAM::getSize()
{
  uint16_t val = getMetaData(2);  // density bits
  if (val > 0) return 1 << val;
  return 0;
}

///////////////////////////////////////////////////////////
//
// PRIVATE
//

// metadata is packed as  [....MMMM][MMMMDDDD][PPPPPPPP]
// M = manufacturerID
// D = density => memsize = 2^D KB
// P = product ID (together with D)
uint16_t FRAM::getMetaData(uint8_t field)
{
  if (field > 2) return 0;

  Wire.beginTransmission(FRAM_SLAVE_ID_);
  Wire.write(_address << 1);
  Wire.endTransmission(false);
  int x = Wire.requestFrom(FRAM_SLAVE_ID_, (uint8_t)3);
  if (x != 3) return -1;

  uint32_t value = 0;
  value = Wire.read();
  value |= Wire.read();
  value |= Wire.read();
  // MANUFACTURER
  if (field == 0) return (value >> 12) & 0xFF;
  // PRODUCT ID
  if (field == 1) return value & 0x0FFF;
  // DENSITY
  if (field == 2) return (value >> 8) & 0x0F;
  return 0;
}

void FRAM::writeBlock(uint16_t memaddr, uint8_t * obj, uint8_t size)
{
  // TODO constrain size < 30 ??
  Wire.beginTransmission(_address);
  Wire.write(memaddr >> 8);
  Wire.write(memaddr & 0xFF);
  uint8_t * p = obj;
  for (uint8_t i = 0; i < size; i++)
  {
    Wire.write(*p++);
  }
  Wire.endTransmission();
}

void FRAM::readBlock(uint16_t memaddr, uint8_t * obj, uint8_t size)
{
  Wire.beginTransmission(_address);
  Wire.write(memaddr >> 8);
  Wire.write(memaddr & 0xFF);
  Wire.endTransmission();
  Wire.requestFrom(_address, size);
  uint8_t * p = obj;
  for (uint8_t i = 0; i < size; i++)
  {
    *p++ = Wire.read();
  }
}

// -- END OF FILE --
