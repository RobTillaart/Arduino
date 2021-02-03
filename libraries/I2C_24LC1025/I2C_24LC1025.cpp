//
//    FILE: I2C_24LC1025.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.3
// PURPOSE: I2C_24LC1025 library for Arduino with EEPROM I2C_24LC1025 et al.
//
//  HISTORY:
//  0.1.0   2019-12-11  initial version (not tested)
//  0.1.1   2021-01-20  major redo 
//  0.1.2   2021-01-31  fix reading over 64K block border
//  0.1.3   2021-02-02  add updateBlock();


#include "I2C_24LC1025.h"


//  TWI buffer needs max 2 bytes for eeprom address
//  1 byte for eeprom register address is available in txbuffer
#if defined(ESP32) || defined(ESP8266)
#define I2C_BUFFERSIZE           128
#else
#define I2C_BUFFERSIZE           30   //  AVR, STM 
#endif


////////////////////////////////////////////////////////////////////
//
// PUBLIC FUNCTIONS
//
I2C_24LC1025::I2C_24LC1025(uint8_t deviceAddress, TwoWire * wire)
{
  _deviceAddress = deviceAddress;
  _deviceSize = I2C_DEVICESIZE_24LC512;
  _pageSize = I2C_24LC1025_PAGESIZE;
  _wire = wire;
}


#if defined (ESP8266) || defined(ESP32)
bool I2C_24LC1025::begin(uint8_t sda, uint8_t scl)
{
  if ((sda < 255) && (scl < 255))
  {
    _wire->begin(sda, scl);
  }
  else
  {
    _wire->begin();
  }
  _lastWrite = 0;
  return isConnected();
}
#endif


bool I2C_24LC1025::begin()
{
  _wire->begin();
  _lastWrite = 0;
  return isConnected();
}


bool I2C_24LC1025::isConnected()
{
  _wire->beginTransmission(_deviceAddress);
  return (_wire->endTransmission() == 0);
}


int I2C_24LC1025::writeByte(const uint32_t memoryAddress, const uint8_t value)
{
  int rv = _WriteBlock(memoryAddress, &value, 1);
  return rv;
}


int I2C_24LC1025::setBlock(const uint32_t memoryAddress, const uint8_t data, const uint32_t length)
{
  uint8_t buffer[I2C_BUFFERSIZE];
  for (uint8_t i = 0; i < I2C_BUFFERSIZE; i++)
  {
    buffer[i] = data;
  }
  int rv = _pageBlock(memoryAddress, buffer, length, false);
  return rv;
}


int I2C_24LC1025::writeBlock(const uint32_t memoryAddress, const uint8_t* buffer, const uint32_t length)
{
  int rv = _pageBlock(memoryAddress, buffer, length, true);
  return rv;
}


uint8_t I2C_24LC1025::readByte(const uint32_t memoryAddress)
{
  uint8_t rdata;
  _ReadBlock(memoryAddress, &rdata, 1);
  return rdata;
}


uint32_t I2C_24LC1025::readBlock(const uint32_t memoryAddress, uint8_t* buffer, const uint32_t length)
{
  uint32_t addr = memoryAddress;
  uint32_t len = length;
  uint32_t rv = 0;

  if ((addr < 0x10000) && ((addr + len) > 0x10000))
  {
    uint32_t sublen = 0x10000 - addr;
    rv = readBlock(addr, (uint8_t *) buffer, sublen);
    rv += readBlock(0x10000, (uint8_t *) &buffer[sublen], len - sublen);
    return rv;
  }

  while (len > 0)
  {
    uint8_t cnt = I2C_BUFFERSIZE;
    if (cnt > len) cnt = len;
    rv     += _ReadBlock(addr, buffer, cnt);
    addr   += cnt;
    buffer += cnt;
    len    -= cnt;
    yield();    // For OS scheduling etc
  }
  return rv;
}


int I2C_24LC1025::updateByte(const uint32_t memoryAddress, const uint8_t data)
{
  if (data == readByte(memoryAddress)) return 0;
  return writeByte(memoryAddress, data);
}


int I2C_24LC1025::updateBlock(const uint32_t memoryAddress, const uint8_t* buffer, const uint32_t length)
{
  uint32_t addr = memoryAddress;
  uint32_t len = length;
  uint32_t rv = 0;
  while (len > 0)
  {
    uint8_t buf[I2C_BUFFERSIZE];
    uint8_t cnt = I2C_BUFFERSIZE;
    
    if (cnt > len) cnt = len;
    rv     += _ReadBlock(addr, buf, cnt);
    if (memcmp(buffer, buf, cnt) != 0)
    {
      _pageBlock(addr, buffer, cnt, true);
    }
    addr   += cnt;
    buffer += cnt;
    len    -= cnt;
    yield();    // For OS scheduling etc
  }
  return rv;
}



////////////////////////////////////////////////////////////////////
//
// PRIVATE
//

// _pageBlock aligns buffer to page boundaries for writing.
// and to TWI buffer size
// returns 0 = OK otherwise error
int I2C_24LC1025::_pageBlock(uint32_t memoryAddress, const uint8_t * buffer, const uint16_t length, const bool incrBuffer)
{
  uint32_t addr = memoryAddress;
  uint16_t len = length;
  while (len > 0)
  {
    uint8_t bytesUntilPageBoundary = this->_pageSize - addr % this->_pageSize;

    uint8_t cnt = I2C_BUFFERSIZE;
    if (cnt > len) cnt = len;
    if (cnt > bytesUntilPageBoundary) cnt = bytesUntilPageBoundary;

    int rv = _WriteBlock(addr, buffer, cnt);
    if (rv != 0) return rv;

    addr += cnt;
    if (incrBuffer) buffer += cnt;
    len -= cnt;
  }
  return 0;
}


void I2C_24LC1025::_beginTransmission(uint32_t memoryAddress)
{
  // chapter 5+6 - datasheet - need three bytes for address
  _actualAddress = _deviceAddress;
  if (memoryAddress >= 0x10000) _actualAddress |= 0x04;  // addresbit 16

#define I2C_WRITEDELAY  5000

  // Wait until EEPROM gives ACK again.
  // this is a bit faster than the hardcoded 5 milliSeconds  // chapter 7 
  while ( (micros() - _lastWrite) <= I2C_WRITEDELAY )
  {
    _wire->beginTransmission(_actualAddress);
    if (_wire->endTransmission() == 0) break;
    yield();
    delayMicroseconds(50);
  }
   uint16_t memAddr = (memoryAddress & 0xFFFF);
  _wire->beginTransmission(_actualAddress);      // device addres + bit 16
  _wire->write((memAddr >> 8) & 0xFF);   // highByte
  _wire->write(memAddr & 0xFF);          // lowByte
}


// pre: length <= this->_pageSize  && length <= I2C_BUFFERSIZE;
// returns 0 = OK otherwise error
int I2C_24LC1025::_WriteBlock(uint32_t memoryAddress, const uint8_t* buffer, const uint8_t length)
{
  yield();

  this->_beginTransmission(memoryAddress);
  _wire->write(buffer, length);
  int rv = _wire->endTransmission();
  _lastWrite = micros();
  if (rv != 0)
  {
    if (_debug)
    {
      Serial.print("mem addr w: ");
      Serial.print(memoryAddress, HEX);
      Serial.print("\t");
      Serial.println(rv);
    }
    return -(abs(rv));  // error
  }
  return rv;
}


// pre: buffer is large enough to hold length bytes
// returns bytes read
int I2C_24LC1025::_ReadBlock(uint32_t memoryAddress, uint8_t* buffer, const uint8_t length)
{
  yield();

  this->_beginTransmission(memoryAddress);
  int rv = _wire->endTransmission();
  if (rv != 0)
  {
    if (_debug)
    {
      Serial.print("mem addr r: ");
      Serial.print(memoryAddress, HEX);
      Serial.print("\t");
      Serial.println(rv);
    }
    return -(abs(rv));  // error
  }

  // readbytes will always be equal or smaller to length
  uint8_t readBytes = _wire->requestFrom(_actualAddress, length);
  uint8_t cnt = 0;
  while (cnt < readBytes)
  {
    buffer[cnt++] = _wire->read();
    yield();
  }
  return readBytes;
}


// -- END OF FILE --
