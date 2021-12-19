//
//    FILE: I2C_eeprom.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 1.5.2
// PURPOSE: Arduino Library for external I2C EEPROM 24LC256 et al.
//     URL: https://github.com/RobTillaart/I2C_EEPROM.git
//
//  HISTORY:
//  0.1.00  2011-01-21  initial version
//  0.1.01  2011-02-07  added setBlock function
//  0.2.00  2011-02-11  fixed 64 bit boundary bug
//  0.2.01  2011-08-13  _readBlock made more robust + return value
//  1.0.00  2013-06-09  support for Arduino 1.0.x
//  1.0.01  2013-11-01  fixed writeBlock bug, refactor
//  1.0.02  2013-11-03  optimize internal buffers, refactor
//  1.0.03  2013-11-03  refactor 5 millis() write-latency
//  1.0.04  2013-11-03  fix bug in readBlock, moved waitEEReady()
//                      -> more efficient.
//  1.0.05  2013-11-06  improved waitEEReady(),
//                      added determineSize()
//  1.1.00  2013-11-13  added begin() function (Note breaking interface)
//                      use faster block Wire.write()
//                      int casting removed
//  1.2.00  2014-05-21  Added support for Arduino DUE ( thanks to Tyler F.)
//  1.2.01  2014-05-21  Refactoring
//  1.2.02  2015-03-06  stricter interface
//  1.2.03  2015-05-15  bugfix in _pageBlock & example (thanks ifreislich )
//  1.2.4   2017-04-19  remove timeout - issue #63
//  1.2.5   2017-04-20  refactor the removed timeout (Thanks to Koepel)
//  1.2.6   2019-02-01  fix issue #121
//  1.2.7   2019-09-03  fix issue #113 and #128
//  1.3.0   2020-06-19  refactor; removed pre 1.0 support; added ESP32 support.
//  1.3.1   2020-12-22  Arduino-CI + unit tests + updateByte()
//  1.3.2   2021-01-18  cyclic store functionality (Thanks to Tomas Hübner)
//  1.4.0   2021-01-27  rewritten addressing scheme + determineSize
//                      See determineSize for all tested.
//  1.4.1   2021-01-28  fixed addressing bug 24LC04/08/16 equivalents from ST e.g. m24c08w
//                      add Wire1..WireN;
//  1.4.2   2021-01-31  add updateBlock()
//  1.4.3   2021-05-05  adjust buffer size AVR / ESP +rename
//  1.5.0   2021-06-30  #28 fix addressing 24LC04/08/16
//  1.5.1   2021-10-14  function to add extra for write cycle (experimental)
//  1.5.2   2021-12-19  update library.json, license, minor edits


#include <I2C_eeprom.h>

// Not used directly
#define I2C_PAGESIZE_24LC512          128
#define I2C_PAGESIZE_24LC256           64
#define I2C_PAGESIZE_24LC128           64
#define I2C_PAGESIZE_24LC64            32
#define I2C_PAGESIZE_24LC32            32
#define I2C_PAGESIZE_24LC16            16
#define I2C_PAGESIZE_24LC08            16
#define I2C_PAGESIZE_24LC04            16
#define I2C_PAGESIZE_24LC02             8
#define I2C_PAGESIZE_24LC01             8


//  I2C buffer needs max 2 bytes for EEPROM address
//  1 byte for EEPROM register address is available in transmit buffer
#if defined(ESP32) || defined(ESP8266)
#define I2C_BUFFERSIZE           128
#else
#define I2C_BUFFERSIZE           30   //  AVR, STM
#endif


I2C_eeprom::I2C_eeprom(const uint8_t deviceAddress, TwoWire *wire)
{
    I2C_eeprom(deviceAddress, I2C_PAGESIZE_24LC256, wire);
}


I2C_eeprom::I2C_eeprom(const uint8_t deviceAddress, const uint32_t deviceSize, TwoWire *wire)
{
    _deviceAddress = deviceAddress;
    _deviceSize = deviceSize;
    _pageSize = getPageSize(_deviceSize);
    _wire = wire;

    // Chips 16Kbit (2048 Bytes) or smaller only have one-word addresses.
    this->_isAddressSizeTwoWords = deviceSize > I2C_DEVICESIZE_24LC16;
}


#if defined (ESP8266) || defined(ESP32)
bool I2C_eeprom::begin(uint8_t sda, uint8_t scl)
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


bool I2C_eeprom::begin()
{
  _wire->begin();
  _lastWrite = 0;
  return isConnected();
}


bool I2C_eeprom::isConnected()
{
  _wire->beginTransmission(_deviceAddress);
  return (_wire->endTransmission() == 0);
}


int I2C_eeprom::writeByte(const uint16_t memoryAddress, const uint8_t data)
{
  int rv = _WriteBlock(memoryAddress, &data, 1);
  return rv;
}


int I2C_eeprom::setBlock(const uint16_t memoryAddress, const uint8_t data, const uint16_t length)
{
  uint8_t buffer[I2C_BUFFERSIZE];
  for (uint8_t i = 0; i < I2C_BUFFERSIZE; i++)
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
    uint8_t cnt = I2C_BUFFERSIZE;
    if (cnt > len) cnt = len;
    rv     += _ReadBlock(addr, buffer, cnt);
    addr   += cnt;
    buffer += cnt;
    len    -= cnt;
    yield();    // For OS scheduling
  }
  return rv;
}


int I2C_eeprom::updateByte(const uint16_t memoryAddress, const uint8_t data)
{
  if (data == readByte(memoryAddress)) return 0;
  return writeByte(memoryAddress, data);
}

int I2C_eeprom::updateBlock(const uint16_t memoryAddress, const uint8_t* buffer, const uint16_t length)
{
  uint16_t addr = memoryAddress;
  uint16_t len = length;
  uint16_t rv = 0;
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
    yield();    // For OS scheduling
  }
  return rv;
}


// returns size in bytes
// returns 0 if not connected
//
//   tested for
//   2 byte address
//   24LC512     64 KB    YES
//   24LC256     32 KB    YES
//   24LC128     16 KB    YES
//   24LC64       8 KB    YES
//   24LC32       4 KB    YES* - no hardware test, address scheme identical to 24LC64.
//
//   1 byte address (uses part of deviceAddress byte)
//   24LC16       2 KB    YES
//   24LC08       1 KB    YES
//   24LC04      512 B    YES
//   24LC02      256 B    YES
//   24LC01      128 B    YES
uint32_t I2C_eeprom::determineSize(const bool debug)
{
  // try to read a byte to see if connected
  if (! isConnected()) return 0;

  uint8_t patAA = 0xAA;
  uint8_t pat55 = 0x55;

  for (uint32_t size = 128; size <= 65536; size *= 2)
  {
    bool folded = false;

    // store old values
    bool addressSize = _isAddressSizeTwoWords;
    _isAddressSizeTwoWords = size > I2C_DEVICESIZE_24LC16;  // 2048
    uint8_t buf = readByte(size);

    // test folding
    uint8_t cnt = 0;
    writeByte(size, pat55);
    if (readByte(0) == pat55) cnt++;
    writeByte(size, patAA);
    if (readByte(0) == patAA) cnt++;
    folded = (cnt == 2);
    if (debug)
    {
      Serial.print(size, HEX);
      Serial.print('\t');
      Serial.println(readByte(size), HEX);
    }

    // restore old values
    writeByte(size, buf);
    _isAddressSizeTwoWords = addressSize;

    if (folded) return size;
  }
  return 0;
}


uint8_t I2C_eeprom::getPageSize(uint32_t deviceSize)
{
    // determine page size from device size - based on Microchip 24LCXX data sheets.
    if (deviceSize <= I2C_DEVICESIZE_24LC02) return 8;
    if (deviceSize <= I2C_DEVICESIZE_24LC16) return 16;
    if (deviceSize <= I2C_DEVICESIZE_24LC64) return 32;
    if (deviceSize <= I2C_DEVICESIZE_24LC256) return 64;
    // I2C_DEVICESIZE_24LC512
    return 128;
}


////////////////////////////////////////////////////////////////////
//
// PRIVATE
//

//  _pageBlock aligns buffer to page boundaries for writing.
//  and to I2C buffer size
//  returns 0 = OK otherwise error
int I2C_eeprom::_pageBlock(const uint16_t memoryAddress, const uint8_t* buffer, const uint16_t length, const bool incrBuffer)
{
  uint16_t addr = memoryAddress;
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


//  supports one and two bytes addresses
void I2C_eeprom::_beginTransmission(const uint16_t memoryAddress)
{
  if (this->_isAddressSizeTwoWords)
  {
  _wire->beginTransmission(_deviceAddress);
    // Address High Byte
    _wire->write((memoryAddress >> 8));
  }
  else
  {
    uint8_t addr = _deviceAddress | ((memoryAddress >> 8) & 0x07);
    _wire->beginTransmission(addr);
  }

  // Address Low Byte (or single byte for chips 16K or smaller that have one-word addresses)
  _wire->write((memoryAddress & 0xFF));
}


//  pre: length <= this->_pageSize  && length <= I2C_BUFFERSIZE;
//  returns 0 = OK otherwise error
int I2C_eeprom::_WriteBlock(const uint16_t memoryAddress, const uint8_t* buffer, const uint8_t length)
{
  _waitEEReady();

  this->_beginTransmission(memoryAddress);
  _wire->write(buffer, length);
  int rv = _wire->endTransmission();
  yield();

  _lastWrite = micros();
  return rv;
}


//  pre: buffer is large enough to hold length bytes
//  returns bytes read
uint8_t I2C_eeprom::_ReadBlock(const uint16_t memoryAddress, uint8_t* buffer, const uint8_t length)
{
  _waitEEReady();

  this->_beginTransmission(memoryAddress);
  int rv = _wire->endTransmission();
  if (rv != 0) return 0;  // error

  // readBytes will always be equal or smaller to length

  uint8_t readBytes = 0;
  if (this->_isAddressSizeTwoWords)
  {
    readBytes = _wire->requestFrom(_deviceAddress, length);
  }
  else
  {
    uint8_t addr = _deviceAddress | ((memoryAddress >> 8) & 0x07);
    readBytes = _wire->requestFrom(addr, length);
  }
  uint8_t cnt = 0;
  while (cnt < readBytes)
  {
    buffer[cnt++] = _wire->read();
    yield();
  }
  return readBytes;
}


void I2C_eeprom::_waitEEReady()
{
#define I2C_WRITEDELAY  5000
  //  Wait until EEPROM gives ACK again.
  //  this is a bit faster than the hardcoded 5 milliSeconds
  //  TWR = WriteCycleTime
  uint32_t waitTime = I2C_WRITEDELAY + _extraTWR * 1000UL;  // do the math once.
  while ((micros() - _lastWrite) <= waitTime)
  {
    _wire->beginTransmission(_deviceAddress);
    int x = _wire->endTransmission();
    if (x == 0) return;
    yield();
  }
  return;
}


// -- END OF FILE --

