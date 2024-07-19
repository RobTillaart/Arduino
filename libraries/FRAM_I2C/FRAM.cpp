//
//    FILE: FRAM.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.8.1
//    DATE: 2018-01-24
// PURPOSE: Arduino library for I2C FRAM
//     URL: https://github.com/RobTillaart/FRAM_I2C


#include "FRAM.h"


//  DENSITY CODES

#define FRAM_MB85RC64                 0x03
#define FRAM_MB85RC256                0x05
#define FRAM_MB85RC512                0x06
#define FRAM_MB85RC1M                 0x07


//  used for metadata and sleep
const uint8_t FRAM_SLAVE_ID_ = 0x7C;  //  == 0xF8
const uint8_t FRAM_SLEEP_CMD = 0x86;  //


/////////////////////////////////////////////////////////////////////////////
//
// FRAM PUBLIC
//
FRAM::FRAM(TwoWire *wire)
{
  _wire            = wire;
  _address         = 0x50;
  _writeProtectPin = -1;
  _sizeBytes       = 0;
}


int FRAM::begin(const uint8_t address,
                const int8_t writeProtectPin)
{
  if ((address < 0x50) || (address > 0x57)) return FRAM_ERROR_ADDR;

  _address = address;
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


void FRAM::write8(uint16_t memAddr, uint8_t value)
{
  uint8_t val = value;
  _writeBlock(memAddr, (uint8_t *)&val, sizeof(uint8_t));
}


void FRAM::write16(uint16_t memAddr, uint16_t value)
{
  uint16_t val = value;
  _writeBlock(memAddr, (uint8_t *)&val, sizeof(uint16_t));
}


void FRAM::write32(uint16_t memAddr, uint32_t value)
{
  uint32_t val = value;
  _writeBlock(memAddr, (uint8_t *)&val, sizeof(uint32_t));
}


void FRAM::write64(uint16_t memAddr, uint64_t value)
{
  uint64_t val = value;
  _writeBlock(memAddr, (uint8_t *)&val, sizeof(uint64_t));
}


void FRAM::writeFloat(uint16_t memAddr, float value)
{
  float val = value;
  _writeBlock(memAddr, (uint8_t *)&val, sizeof(float));
}


void FRAM::writeDouble(uint16_t memAddr, double value)
{
  double val = value;
  _writeBlock(memAddr, (uint8_t *)&val, sizeof(double));
}


void FRAM::write(uint16_t memAddr, uint8_t * obj, uint16_t size)
{
  const int blocksize = 24;
  uint8_t * p = obj;
  while (size >= blocksize)
  {
    _writeBlock(memAddr, p, blocksize);
    memAddr += blocksize;
    p += blocksize;
    size -= blocksize;
  }
  //  remaining
  if (size > 0)
  {
    _writeBlock(memAddr, p, size);
  }
}


uint8_t FRAM::read8(uint16_t memAddr)
{
  uint8_t val;
  _readBlock(memAddr, (uint8_t *)&val, sizeof(uint8_t));
  return val;
}


uint16_t FRAM::read16(uint16_t memAddr)
{
  uint16_t val;
  _readBlock(memAddr, (uint8_t *)&val, sizeof(uint16_t));
  return val;
}


uint32_t FRAM::read32(uint16_t memAddr)
{
  uint32_t val;
  _readBlock(memAddr, (uint8_t *)&val, sizeof(uint32_t));
  return val;
}


uint64_t FRAM::read64(uint16_t memAddr)
{
  uint64_t val;
  _readBlock(memAddr, (uint8_t *)&val, sizeof(uint64_t));
  return val;
}


float FRAM::readFloat(uint16_t memAddr)
{
  float val;
  _readBlock(memAddr, (uint8_t *)&val, sizeof(float));
  return val;
}


double FRAM::readDouble(uint16_t memAddr)
{
  double val;
  _readBlock(memAddr, (uint8_t *)&val, sizeof(double));
  return val;
}


void FRAM::read(uint16_t memAddr, uint8_t * obj, uint16_t size)
{
  const uint8_t blocksize = 24;
  uint8_t * p = obj;
  while (size >= blocksize)
  {
    _readBlock(memAddr, p, blocksize);
    memAddr += blocksize;
    p += blocksize;
    size -= blocksize;
  }
  //  remainder
  if (size > 0)
  {
    _readBlock(memAddr, p, size);
  }
}


////////////////////////////////////////////////////////////////////////


int32_t FRAM::readUntil(uint16_t memAddr, char * buffer, uint16_t bufferLength, char separator)
{
  //  read and fill the buffer at once.
  read(memAddr, (uint8_t *)buffer, bufferLength);
  for (uint16_t length = 0; length < bufferLength; length++)
  {
    if (buffer[length] == separator)
    {
      //  replace separator => \0 EndChar
      buffer[length] = 0;
      return length;
    }
  }
  //  entry does not fit in given buffer.
  return (int32_t)-1;
}


int32_t FRAM::readLine(uint16_t memAddr, char * buffer, uint16_t bufferLength)
{
  //  read and fill the buffer at once.
  read(memAddr, (uint8_t *)buffer, bufferLength);
  for (uint16_t length = 0; length < bufferLength-1; length++)
  {
    if (buffer[length] == '\n')
    {
      //  add \0 EndChar after '\n'
      buffer[length + 1] = 0;
      return length + 1;
    }
  }
  //  entry does not fit in given buffer.
  return (int32_t)-1;
}


////////////////////////////////////////////////////////////////////////


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


////////////////////////////////////////////////////////////////
//
//  MANUFACTURER  PRODUCTID  SIZE
//
uint16_t FRAM::getManufacturerID()
{
  uint32_t value = _getMetaData();
  return (value >> 12) & 0x0FFF;
}


uint16_t FRAM::getProductID()
{
  uint32_t value = _getMetaData();
  return value & 0x0FFF;
}


#define FRAM_MANU_FUJITSU     0x0A
#define FRAM_MANU_CYPRESS     0x04

//  DENSITY  Fujitsu data sheet
//  3 =>     MB85RC64 = 64 Kbit.
//  5 =>     MB85RC256
//  6 =>     MB85RC512
//  7 =>     MB85RC1M
//
//  DENSITY  Cypress / Infineon data sheet
//  3 =>     FM24V05 = 64 KByte.
//  4 =>     FM24V10 = 128 KByte.
//
//  NOTE: returns the size in kiloBYTE (0 is read error)
uint16_t FRAM::getSize()
{
  uint32_t value = _getMetaData();
  if (value == 0xFFFFFFFF) return 0;

  uint16_t manufacturer = (value >> 12) & 0x0FFF;

  if (manufacturer == FRAM_MANU_CYPRESS)
  {
    uint16_t density = (value >> 8) & 0x0F;
    uint16_t size = (1UL << density) * 8;  //  KB
    _sizeBytes = size * 1024UL;
    return size;
  }
  //  default FRAM_MANU_FUJITSU
  uint16_t density = (value >> 8) & 0x0F;
  uint16_t size = (1UL << density) * 1;  //  KB
  _sizeBytes = size * 1024UL;
  return size;
}


uint32_t FRAM::getSizeBytes()
{
  return _sizeBytes;
}


//  override to be used when getSize() fails == 0
void FRAM::setSizeBytes(uint32_t value)
{
  _sizeBytes = value;
}


uint32_t FRAM::clear(uint8_t value)
{
  uint8_t buffer[16];
  for (uint8_t i = 0; i < 16; i++) buffer[i] = value;
  uint32_t start = 0;
  uint32_t end = _sizeBytes;
  for (uint32_t address = start; address < end; address += 16)
  {
    _writeBlock(address, buffer, 16);
  }
  return end - start;
}


//  EXPERIMENTAL - to be confirmed
//  page 12 datasheet
//  command = S 0xF8 A address A S 86 A P  (A = Ack from slave )
void FRAM::sleep()
{
  _wire->beginTransmission(FRAM_SLAVE_ID_);       //  S 0xF8
  _wire->write(_address << 1);                    //  address << 1
  _wire->endTransmission(false);                  //  no stoP
  _wire->beginTransmission(FRAM_SLEEP_CMD >> 1);  //  S 0x86
  _wire->endTransmission(true);                   //  stoP
}


//  page 12 datasheet   trec <= 400us
bool FRAM::wakeup(uint32_t timeRecover)
{
  //  wakeup
  bool b = isConnected();
  if (timeRecover == 0) return b;
  //  wait recovery time
  delayMicroseconds(timeRecover);
  //  check recovery OK
  return isConnected();
}


/////////////////////////////////////////////////////////////////////////////
//
// FRAM PROTECTED
//

//  metadata is packed as  [MMMMMMMM][MMMMDDDD][PPPPPPPP]
//  M = manufacturerID
//  D = density => memory size = 2^D KB
//  P = product ID (together with D)
//  P part might be proprietary
uint32_t FRAM::_getMetaData()
{
  _wire->beginTransmission(FRAM_SLAVE_ID_);
  _wire->write(_address << 1);
  _wire->endTransmission(false);
  int x = _wire->requestFrom(FRAM_SLAVE_ID_, (uint8_t)3);
  if (x != 3) return 0xFFFFFFFF;

  uint32_t value = 0;
  value = _wire->read();
  value = value << 8;
  value |= _wire->read();
  value = value << 8;
  value |= _wire->read();

  return value;
}


void FRAM::_writeBlock(uint16_t memAddr, uint8_t * obj, uint8_t size)
{
  _wire->beginTransmission(_address);
  _wire->write((uint8_t) (memAddr >> 8));
  _wire->write((uint8_t) (memAddr & 0xFF));
  uint8_t * p = obj;
  for (uint8_t i = size; i > 0; i--)
  {
    _wire->write(*p++);
  }
  _wire->endTransmission();
}


void FRAM::_readBlock(uint16_t memAddr, uint8_t * obj, uint8_t size)
{
  _wire->beginTransmission(_address);
  _wire->write((uint8_t) (memAddr >> 8));
  _wire->write((uint8_t) (memAddr & 0xFF));
  _wire->endTransmission();
  _wire->requestFrom(_address, size);
  uint8_t * p = obj;
  for (uint8_t i = size; i > 0; i--)
  {
    *p++ = _wire->read();
  }
}


/////////////////////////////////////////////////////////////////////////////
//
//  FRAM32  PUBLIC
//
FRAM32::FRAM32(TwoWire *wire) : FRAM(wire)
{
}


void FRAM32::write8(uint32_t memAddr, uint8_t value)
{
  uint8_t val = value;
  _writeBlock(memAddr, (uint8_t *)&val, sizeof(uint8_t));
}


void FRAM32::write16(uint32_t memAddr, uint16_t value)
{
  uint16_t val = value;
  _writeBlock(memAddr, (uint8_t *)&val, sizeof(uint16_t));
}


void FRAM32::write32(uint32_t memAddr, uint32_t value)
{
  uint32_t val = value;
  _writeBlock(memAddr, (uint8_t *)&val, sizeof(uint32_t));
}


void FRAM32::write64(uint32_t memAddr, uint64_t value)
{
  uint64_t val = value;
  _writeBlock(memAddr, (uint8_t *)&val, sizeof(uint64_t));
}


void FRAM32::writeFloat(uint32_t memAddr, float value)
{
  float val = value;
  _writeBlock(memAddr, (uint8_t *)&val, sizeof(float));
}


void FRAM32::writeDouble(uint32_t memAddr, double value)
{
  double val = value;
  _writeBlock(memAddr, (uint8_t *)&val, sizeof(double));
}


void FRAM32::write(uint32_t memAddr, uint8_t * obj, uint16_t size)
{
  const int blocksize = 24;
  uint8_t * p = obj;
  while (size >= blocksize)
  {
    _writeBlock(memAddr, p, blocksize);
    memAddr += blocksize;
    p += blocksize;
    size -= blocksize;
  }
  //  remaining
  if (size > 0)
  {
    _writeBlock(memAddr, p, size);
  }
}


uint8_t FRAM32::read8(uint32_t memAddr)
{
  uint8_t val;
  _readBlock(memAddr, (uint8_t *)&val, sizeof(uint8_t));
  return val;
}


uint16_t FRAM32::read16(uint32_t memAddr)
{
  uint16_t val;
  _readBlock(memAddr, (uint8_t *)&val, sizeof(uint16_t));
  return val;
}


uint32_t FRAM32::read32(uint32_t memAddr)
{
  uint32_t val;
  _readBlock(memAddr, (uint8_t *)&val, sizeof(uint32_t));
  return val;
}


uint64_t FRAM32::read64(uint32_t memAddr)
{
  uint64_t val;
  _readBlock(memAddr, (uint8_t *)&val, sizeof(uint64_t));
  return val;
}


float FRAM32::readFloat(uint32_t memAddr)
{
  float val;
  _readBlock(memAddr, (uint8_t *)&val, sizeof(float));
  return val;
}


double FRAM32::readDouble(uint32_t memAddr)
{
  double val;
  _readBlock(memAddr, (uint8_t *)&val, sizeof(double));
  return val;
}


void FRAM32::read(uint32_t memAddr, uint8_t * obj, uint16_t size)
{
  const uint8_t blocksize = 24;
  uint8_t * p = obj;
  while (size >= blocksize)
  {
    _readBlock(memAddr, p, blocksize);
    memAddr += blocksize;
    p += blocksize;
    size -= blocksize;
  }
  // remainder
  if (size > 0)
  {
    _readBlock(memAddr, p, size);
  }
}


int32_t FRAM32::readUntil(uint32_t memAddr, char * buffer, uint16_t bufferLength, char separator)
{
  //  read and fill the buffer at once.
  read(memAddr, (uint8_t *)buffer, bufferLength);
  for (uint16_t length = 0; length < bufferLength; length++)
  {
    if (buffer[length] == separator)
    {
      //  replace separator => \0 EndChar
      buffer[length] = 0;
      return length;
    }
  }
  //  entry does not fit in given buffer.
  return (int32_t)-1;
}


int32_t FRAM32::readLine(uint32_t memAddr, char * buffer, uint16_t bufferLength)
{
  //  read and fill the buffer at once.
  read(memAddr, (uint8_t *)buffer, bufferLength);
  for (uint16_t length = 0; length < bufferLength-1; length++)
  {
    if (buffer[length] == '\n')
    {
      //  add \0 EndChar after '\n'
      buffer[length + 1] = 0;
      return length + 1;
    }
  }
  //  entry does not fit in given buffer.
  return (int32_t)-1;
}


uint32_t FRAM32::clear(uint8_t value)
{
  uint8_t buffer[16];
  for (uint8_t i = 0; i < 16; i++) buffer[i] = value;
  uint32_t start = 0;
  uint32_t end = _sizeBytes;
  for (uint32_t addr = start; addr < end; addr += 16)
  {
    _writeBlock(addr, buffer, 16);
  }
  return end - start;
}


/////////////////////////////////////////////////////////////////////////////
//
//  FRAM32  PROTECTED
//
void FRAM32::_writeBlock(uint32_t memAddr, uint8_t * obj, uint8_t size)
{
  uint8_t _addr = _address;
  if (memAddr & 0xFFFE0000) return;  //  ignore invalid memory addresses
  if ((memAddr & 0x00010000) == 0x00010000) _addr += 0x01;

  _wire->beginTransmission(_addr);
  _wire->write((uint8_t) (memAddr >> 8));
  _wire->write((uint8_t) (memAddr & 0xFF));
  uint8_t * p = obj;
  for (uint8_t i = size; i > 0; i--)
  {
    _wire->write(*p++);
  }
  _wire->endTransmission();
}


void FRAM32::_readBlock(uint32_t memAddr, uint8_t * obj, uint8_t size)
{
  uint8_t _addr = _address;
  if (memAddr & 0xFFFE0000) return;  //  ignore invalid memory addresses
  if ((memAddr & 0x00010000) == 0x00010000) _addr += 0x01;

  _wire->beginTransmission(_addr);
  _wire->write((uint8_t) (memAddr >> 8));
  _wire->write((uint8_t) (memAddr & 0xFF));
  _wire->endTransmission();
  _wire->requestFrom(_addr, size);
  uint8_t * p = obj;
  for (uint8_t i = size; i > 0; i--)
  {
    *p++ = _wire->read();
  }
}


/////////////////////////////////////////////////////////////////////////////
//
//  FRAM11
//
FRAM11::FRAM11(TwoWire *wire) : FRAM(wire)
{
  _sizeBytes = 2048;
}


int FRAM11::begin(const uint8_t address, const int8_t writeProtectPin)
{
  int rv = FRAM::begin(address, writeProtectPin);
  _sizeBytes = 2048;
  return rv;
}


uint16_t FRAM11::getSize()
{
  return _sizeBytes / 1024;
}


/////////////////////////////////////////////////////////////////////////////
//
//  FRAM11  PROTECTED
//
void FRAM11::_writeBlock(uint16_t memAddr, uint8_t * obj, uint8_t size)
{
  //  Device uses Address Pages
  uint8_t  DeviceAddrWithPageBits = _address | ((memAddr & 0x0700) >> 8);
  _wire->beginTransmission(DeviceAddrWithPageBits);
  _wire->write((uint8_t) (memAddr & 0xFF));

  uint8_t * p = obj;
  for (uint8_t i = size; i > 0; i--)
  {
    _wire->write(*p++);
  }
  _wire->endTransmission();
}


void FRAM11::_readBlock(uint16_t memAddr, uint8_t * obj, uint8_t size)
{
  //  Device uses Address Pages
  uint8_t DeviceAddrWithPageBits = _address | ((memAddr & 0x0700) >> 8);
  _wire->beginTransmission(DeviceAddrWithPageBits);
  _wire->write((uint8_t) (memAddr & 0xFF));
  _wire->endTransmission();
  _wire->requestFrom(DeviceAddrWithPageBits, size);

  uint8_t * p = obj;
  for (uint8_t i = size; i > 0; i--)
  {
    *p++ = _wire->read();
  }
}


/////////////////////////////////////////////////////////////////////////////
//
//  FRAM9
//
FRAM9::FRAM9(TwoWire *wire) : FRAM(wire)
{
  _sizeBytes = 512;
}


int FRAM9::begin(const uint8_t address, const int8_t writeProtectPin)
{
  int rv = FRAM::begin(address, writeProtectPin);
  _sizeBytes = 512;
  return rv;
}


uint16_t FRAM9::getSize()
{
  return _sizeBytes / 1024;  //  == 0.
}


/////////////////////////////////////////////////////////////////////////////
//
//  FRAM9  PROTECTED
//
void FRAM9::_writeBlock(uint16_t memAddr, uint8_t * obj, uint8_t size)
{
  //  Device uses Address Pages
  uint8_t DeviceAddrWithPageBits = _address | ((memAddr & 0x0100) >> 8);
  _wire->beginTransmission(DeviceAddrWithPageBits);
  _wire->write((uint8_t) (memAddr & 0xFF));

  uint8_t * p = obj;
  for (uint8_t i = size; i > 0; i--)
  {
    _wire->write(*p++);
  }
  _wire->endTransmission();
}


void FRAM9::_readBlock(uint16_t memAddr, uint8_t * obj, uint8_t size)
{
  //  Device uses Address Pages
  uint8_t DeviceAddrWithPageBits = _address | ((memAddr & 0x0100) >> 8);
  _wire->beginTransmission(DeviceAddrWithPageBits);
  _wire->write((uint8_t) (memAddr & 0xFF));
  _wire->endTransmission();
  _wire->requestFrom(DeviceAddrWithPageBits, size);

  uint8_t * p = obj;
  for (uint8_t i = size; i > 0; i--)
  {
    *p++ = _wire->read();
  }
}


//  -- END OF FILE --

