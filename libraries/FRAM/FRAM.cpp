//
//    FILE: FRAM.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
// PURPOSE: Class for FRAM memory
//     URL:
//
// HISTORY:
// 0.1.0 initial version
// 0.1.1 added suppport for Fujitsu 64Kbit MB85RC64T (kudos ysoyipek)

#include "FRAM.h"

#define FRAM_SLAVE_ID_         0x7C

/////////////////////////////////////////////////////
//
// PUBLIC
//
FRAM::FRAM()
{}

int FRAM::begin(int address = 0X50)
{
  if (address < 0x50 || address > 0x57)
  {
    return FRAM_ERROR_ADDR;
  }

  _address = address;
  Wire.begin();

  uint16_t mid = getManufacturerID();
  uint16_t pid = getProductID();
  _size = 0;                          // UNKNOWN
  if (mid == 0x000A)                  // fujitsu
  {
    // note pid's are from fujitsu       SIZE    TYPE
    if (pid == 0x0358) _size = 8;     // 8KB     MB85RC64T
    if (pid == 0x0510) _size = 32;    // 32KB    MB85RC256V
    if (pid == 0x0658) _size = 64;    // 64KB    MB85RC512T
    if (pid == 0x0758) _size = 128;   // 128KB   MB85RC1MT
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
  const int blocksize = 24;
  uint8_t * p = obj;
  while (size >= blocksize)
  {
    readBlock(memaddr, p, blocksize);
    memaddr += blocksize;
    p += blocksize;
    size -= blocksize;
  }
  if (size > 0)
  {
    readBlock(memaddr, p, size);
  }
}

uint16_t FRAM::getManufacturerID()
{
  uint16_t value = 0;
  Wire.beginTransmission(FRAM_SLAVE_ID_);
  Wire.write(_address << 1);
  Wire.endTransmission(false);
  int x = Wire.requestFrom(FRAM_SLAVE_ID_, 2);
  if (x != 2) return -1;
  value = Wire.read() << 4;
  value |= Wire.read() >> 4;
  return value;
}

uint16_t FRAM::getProductID()
{
  uint16_t value = 0;
  Wire.beginTransmission(FRAM_SLAVE_ID_);
  Wire.write(_address << 1);
  Wire.endTransmission(false);
  int x = Wire.requestFrom(FRAM_SLAVE_ID_, 3);
  if (x != 3) return -1;
  Wire.read();
  value = (Wire.read() & 0x0F) << 8;
  value |= Wire.read();
  return value;
}

///////////////////////////////////////////////////////////
//
// PRIVATE
//
void FRAM::writeBlock(uint16_t memaddr, uint8_t * obj, uint16_t size)
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

void FRAM::readBlock(uint16_t memaddr, uint8_t * obj, uint16_t size)
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

// END OF FILE
