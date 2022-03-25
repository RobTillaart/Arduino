//
//    FILE: FRAM.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.5
//    DATE: 2018-01-24
// PURPOSE: Arduino library for I2C FRAM
//     URL: https://github.com/RobTillaart/FRAM_I2C
//
//  HISTORY: see CHANGELOG.md


#include "FRAM.h"


// DENSITY CODES

#define FRAM_MB85RC64                 0x03
#define FRAM_MB85RC256                0x05
#define FRAM_MB85RC512                0x06
#define FRAM_MB85RC1M                 0x07


// used for metadata
const uint8_t FRAM_SLAVE_ID_= 0x7C;


/////////////////////////////////////////////////////
//
// PUBLIC
//
FRAM::FRAM(TwoWire *wire)
{
  _wire            = wire;
  _address         = 0x50;
  _writeProtectPin = -1;
  _sizeBytes       = 0;
}


#if defined (ESP8266) || defined(ESP32)
int FRAM::begin(uint8_t sda, uint8_t scl, const uint8_t address, int8_t writeProtectPin)
{
  if ((address < 0x50) || (address > 0x57)) return FRAM_ERROR_ADDR;

  _wire = &Wire;
  _address = address;
  if ((sda < 255) && (scl < 255))
  {
    _wire->begin(sda, scl);
  } else {
    _wire->begin();
  }

  if (writeProtectPin > -1)
  {
    _writeProtectPin = writeProtectPin;
    pinMode(_writeProtectPin, OUTPUT);
  }
  if (! isConnected()) return FRAM_ERROR_CONNECT;
  getSize();
  return FRAM_OK;
}
#endif


int FRAM::begin(uint8_t address, int8_t writeProtectPin)
{
  if ((address < 0x50) || (address > 0x57)) return FRAM_ERROR_ADDR;

  _address = address;
  _wire->begin();

  if (writeProtectPin > -1)
  {
    _writeProtectPin = writeProtectPin;
    pinMode(_writeProtectPin, OUTPUT);
  }
  if (! isConnected()) return FRAM_ERROR_CONNECT;
  getSize();
  return FRAM_OK;
}


bool FRAM::isConnected()
{
  _wire->beginTransmission(_address);
  return (_wire->endTransmission() == 0);
}


void FRAM::write8(uint16_t memaddr, uint8_t value)
{
  uint8_t val = value;
  _writeBlock(memaddr, (uint8_t *)&val, 1);
}


void FRAM::write16(uint16_t memaddr, uint16_t value)
{
  uint16_t val = value;
  _writeBlock(memaddr, (uint8_t *)&val, 2);
}


void FRAM::write32(uint16_t memaddr, uint32_t value)
{
  uint32_t val = value;
  _writeBlock(memaddr, (uint8_t *)&val, 4);
}


void FRAM::write(uint16_t memaddr, uint8_t * obj, uint16_t size)
{
  const int blocksize = 24;
  uint8_t * p = obj;
  while (size >= blocksize)
  {
    _writeBlock(memaddr, p, blocksize);
    memaddr += blocksize;
    p += blocksize;
    size -= blocksize;
  }
  // remaining
  if (size > 0)
  {
    _writeBlock(memaddr, p, size);
  }
}


uint8_t FRAM::read8(uint16_t memaddr)
{
  uint8_t val;
  _readBlock(memaddr, (uint8_t *)&val, 1);
  return val;
}


uint16_t FRAM::read16(uint16_t memaddr)
{
  uint16_t val;
  _readBlock(memaddr, (uint8_t *)&val, 2);
  return val;
}


uint32_t FRAM::read32(uint16_t memaddr)
{
  uint32_t val;
  _readBlock(memaddr, (uint8_t *)&val, 4);
  return val;
}


void FRAM::read(uint16_t memaddr, uint8_t * obj, uint16_t size)
{
  const uint8_t blocksize = 24;
  uint8_t * p = obj;
  while (size >= blocksize)
  {
    _readBlock(memaddr, p, blocksize);
    memaddr += blocksize;
    p += blocksize;
    size -= blocksize;
  }
  // remainder
  if (size > 0)
  {
    _readBlock(memaddr, p, size);
  }
}


bool FRAM::setWriteProtect(bool b)
{
  if (_writeProtectPin < 0) return false;
  digitalWrite(_writeProtectPin, b ? HIGH : LOW);
  return true;
}


bool FRAM::getWriteProtect()
{
  if (_writeProtectPin < 0) return false;
  return (digitalRead(_writeProtectPin) == HIGH);
}


uint16_t FRAM::getManufacturerID()
{
  return _getMetaData(0);
}


uint16_t FRAM::getProductID()
{
  return _getMetaData(1);
}


// NOTE: returns the size in kiloBYTE
uint16_t FRAM::getSize()
{
  uint16_t density = _getMetaData(2);
  uint16_t size = 0;
  if (density > 0) size = (1UL << density);
  _sizeBytes = size * 1024UL;
  return size;
}


//  override to be used when getSize() fails == 0
void FRAM::setSizeBytes(uint32_t value)
{
  _sizeBytes = value;
}


uint32_t FRAM::clear(uint8_t value)
{
  uint8_t buf[16];
  for (uint8_t i = 0; i < 16; i++) buf[i] = value;
  uint32_t start = 0;
  uint32_t end = _sizeBytes;
  for (uint32_t addr = start; addr < end; addr += 16)
  {
    _writeBlock(addr, buf, 16);
  }
  return end - start;
}


///////////////////////////////////////////////////////////
//
// PRIVATE
//

//  metadata is packed as  [....MMMM][MMMMDDDD][PPPPPPPP]
//  M = manufacturerID
//  D = density => memory size = 2^D KB
//  P = product ID (together with D)
uint16_t FRAM::_getMetaData(uint8_t field)
{
  if (field > 2) return 0;

  _wire->beginTransmission(FRAM_SLAVE_ID_);
  _wire->write(_address << 1);
  _wire->endTransmission(false);
  int x = _wire->requestFrom(FRAM_SLAVE_ID_, (uint8_t)3);
  if (x != 3) return -1;

  uint32_t value = 0;
  value = _wire->read();
  value = value << 8;
  value |= _wire->read();
  value = value << 8;
  value |= _wire->read();

  // MANUFACTURER
  if (field == 0) return (value >> 12) & 0xFF;
  // PRODUCT ID
  if (field == 1) return value & 0x0FFF;
  // DENSITY
  // 3 => MB85RC64
  // 5 => MB85RC256
  // 6 => MB85RC512
  // 7 => MB85RC1M
  if (field == 2) return (value >> 8) & 0x0F;
  return 0;
}


void FRAM::_writeBlock(uint16_t memaddr, uint8_t * obj, uint8_t size)
{
  _wire->beginTransmission(_address);
  _wire->write(memaddr >> 8);
  _wire->write(memaddr & 0xFF);
  uint8_t * p = obj;
  for (uint8_t i = 0; i < size; i++)
  {
    _wire->write(*p++);
  }
  _wire->endTransmission();
}


void FRAM::_readBlock(uint16_t memaddr, uint8_t * obj, uint8_t size)
{
  _wire->beginTransmission(_address);
  _wire->write(memaddr >> 8);
  _wire->write(memaddr & 0xFF);
  _wire->endTransmission();
  _wire->requestFrom(_address, size);
  uint8_t * p = obj;
  for (uint8_t i = 0; i < size; i++)
  {
    *p++ = _wire->read();
  }
}


// -- END OF FILE --

