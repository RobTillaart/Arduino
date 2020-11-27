//
//    FILE: I2C_eeprom.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 1.3.0
// PURPOSE: Arduino Library for external I2C EEPROM 24LC256 et al.
//     URL: https://github.com/RobTillaart/I2C_EEPROM.git
//
// HISTORY:
// 0.1.00 - 2011-01-21 initial version
// 0.1.01 - 2011-02-07 added setBlock function
// 0.2.00 - 2011-02-11 fixed 64 bit boundary bug
// 0.2.01 - 2011-08-13 _readBlock made more robust + return value
// 1.0.00 - 2013-06-09 support for Arduino 1.0.x
// 1.0.01 - 2013-11-01 fixed writeBlock bug, refactor
// 1.0.02 - 2013-11-03 optimize internal buffers, refactor
// 1.0.03 - 2013-11-03 refactor 5 millis() write-latency
// 1.0.04 - 2013-11-03 fix bug in readBlock, moved waitEEReady()
//                     -> more efficient.
// 1.0.05 - 2013-11-06 improved waitEEReady(),
//                     added determineSize()
// 1.1.00 - 2013-11-13 added begin() function (Note breaking interface)
//                     use faster block Wire.write()
//                     int casting removed
// 1.2.00 - 2014-05-21 Added support for Arduino DUE ( thanks to Tyler F.)
// 1.2.01 - 2014-05-21 Refactoring
// 1.2.02 - 2015-03-06 stricter interface
// 1.2.03 - 2015-05-15 bugfix in _pageBlock & example (thanks ifreislich )
// 1.2.4    2017-04-19 remove timeout - issue #63
// 1.2.5    2017-04-20 refactor the removed timeout (Thanks to Koepel)
// 1.2.6    2019-02-01 fix issue #121
// 1.2.7    2019-09-03 fix issue #113 and #128
// 1.3.0    2020-06-19 refactor; removed pre 1.0 support; added ESP32 support.
//

#include <I2C_eeprom.h>


I2C_eeprom::I2C_eeprom(const uint8_t deviceAddress)
{
    I2C_eeprom(deviceAddress, I2C_EEPROM_PAGESIZE);
}

I2C_eeprom::I2C_eeprom(const uint8_t deviceAddress, const unsigned int deviceSize)
{
    _deviceAddress = deviceAddress;

    // Chips 16Kbit (2048 Bytes) or smaller only have one-word addresses.
    // Also try to guess page size from device size (going by Microchip 24LCXX datasheets here).
    if (deviceSize <= 256)
    {
        this->_isAddressSizeTwoWords = false;
        this->_pageSize = 8;
    }
    else if (deviceSize <= 256 * 8)
    {
        this->_isAddressSizeTwoWords = false;
        this->_pageSize = 16;
    }
    else
    {
        this->_isAddressSizeTwoWords = true;
        this->_pageSize = 32;
    }
}

#if defined (ESP8266) || defined(ESP32)
void I2C_eeprom::begin(uint8_t sda, uint8_t scl)
{
  Wire.begin(sda, scl);
  _lastWrite = 0;
}
#endif

void I2C_eeprom::begin()
{
  Wire.begin();
  _lastWrite = 0;
}

int I2C_eeprom::writeByte(const uint16_t memoryAddress, const uint8_t data)
{
  int rv = _WriteBlock(memoryAddress, &data, 1);
  return rv;
}

int I2C_eeprom::setBlock(const uint16_t memoryAddress, const uint8_t data, const uint16_t length)
{
  uint8_t buffer[I2C_TWIBUFFERSIZE];
  for (uint8_t i = 0; i < I2C_TWIBUFFERSIZE; i++)
  {
    buffer[i] = data;
  }
  int rv = _pageBlock(memoryAddress, buffer, length, false);
  return rv;
}

int I2C_eeprom::writeBlock(const uint16_t memoryAddress, const uint8_t* buffer, const uint16_t length)
{
  int rv = _pageBlock(memoryAddress, buffer, length, true);
  return rv;
}

uint8_t I2C_eeprom::readByte(const uint16_t memoryAddress)
{
  uint8_t rdata;
  _ReadBlock(memoryAddress, &rdata, 1);
  return rdata;
}

uint16_t I2C_eeprom::readBlock(const uint16_t memoryAddress, uint8_t* buffer, const uint16_t length)
{
  uint16_t addr = memoryAddress;
  uint16_t len = length;
  uint16_t rv = 0;
  while (len > 0)
  {
    uint8_t cnt = I2C_TWIBUFFERSIZE;
    if (cnt > len) cnt = len;
    rv     += _ReadBlock(addr, buffer, cnt);
    addr   += cnt;
    buffer += cnt;
    len    -= cnt;
  }
  return rv;
}

// returns 64, 32, 16, 8, 4, 2, 1, 0
// 0 is smaller than 1K
int I2C_eeprom::determineSize()
{
  int rv = 0;  // unknown
  uint8_t orgValues[8];
  uint16_t addr;

  // try to read a byte to see if connected
  rv += _ReadBlock(0x00, orgValues, 1);
  if (rv == 0) return -1;

  // remember old values, non destructive
  for (uint8_t i = 0; i < 8; i++)
  {
    addr = (512 << i) + 1;
    orgValues[i] = readByte(addr);
  }

  // scan page folding
  for (uint8_t i = 0; i < 8; i++)
  {
    rv = i;
    uint16_t addr1 = (512 << i) + 1;
    uint16_t addr2 = (512 << (i+1)) + 1;
    writeByte(addr1, 0xAA);
    writeByte(addr2, 0x55);
    if (readByte(addr1) == 0x55) // folded!
    {
      break;
    }
  }

  // restore original values
  for (uint8_t i = 0; i < 8; i++)
  {
    uint16_t addr = (512 << i) + 1;
    writeByte(addr, orgValues[i]);
  }
  return 0x01 << (rv - 1);
}

////////////////////////////////////////////////////////////////////
//
// PRIVATE
//

// _pageBlock aligns buffer to page boundaries for writing.
// and to TWI buffer size
// returns 0 = OK otherwise error
int I2C_eeprom::_pageBlock(const uint16_t memoryAddress, const uint8_t* buffer, const uint16_t length, const bool incrBuffer)
{
  uint16_t addr = memoryAddress;
  uint16_t len = length;
  while (len > 0)
  {
    uint8_t bytesUntilPageBoundary = this->_pageSize - addr % this->_pageSize;

    uint8_t cnt = I2C_TWIBUFFERSIZE;
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

// supports one and 2 bytes addresses
void I2C_eeprom::_beginTransmission(const uint16_t memoryAddress)
{
  Wire.beginTransmission(_deviceAddress);

  if (this->_isAddressSizeTwoWords)
  {
    // Address High Byte
    Wire.write((memoryAddress >> 8));
  }

  // Address Low Byte (or only byte for chips 16K or smaller that only have one-word addresses)
  Wire.write((memoryAddress & 0xFF));
}

// pre: length <= this->_pageSize  && length <= I2C_TWIBUFFERSIZE;
// returns 0 = OK otherwise error
int I2C_eeprom::_WriteBlock(const uint16_t memoryAddress, const uint8_t* buffer, const uint8_t length)
{
  _waitEEReady();

  this->_beginTransmission(memoryAddress);
  Wire.write(buffer, length);
  int rv = Wire.endTransmission();

  _lastWrite = micros();
  return rv;
}

// pre: buffer is large enough to hold length bytes
// returns bytes read
uint8_t I2C_eeprom::_ReadBlock(const uint16_t memoryAddress, uint8_t* buffer, const uint8_t length)
{
  _waitEEReady();

  this->_beginTransmission(memoryAddress);
  int rv = Wire.endTransmission();
  if (rv != 0) return 0;  // error

  // readbytes will always be equal or smaller to length
  uint8_t readBytes = Wire.requestFrom(_deviceAddress, length);
  uint8_t cnt = 0;
  while (cnt < readBytes)
  {
    buffer[cnt++] = Wire.read();
  }
  return readBytes;
}

void I2C_eeprom::_waitEEReady()
{
#define I2C_WRITEDELAY  5000

  // Wait until EEPROM gives ACK again.
  // this is a bit faster than the hardcoded 5 milliSeconds
  while ((micros() - _lastWrite) <= I2C_WRITEDELAY)
  {
    Wire.beginTransmission(_deviceAddress);
    int x = Wire.endTransmission();
    if (x == 0) return;
    yield();
  }
  return;
}

// -- END OF FILE --
