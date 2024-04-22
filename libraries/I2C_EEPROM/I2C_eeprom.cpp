//
//    FILE: I2C_eeprom.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 1.8.5
// PURPOSE: Arduino Library for external I2C EEPROM 24LC256 et al.
//     URL: https://github.com/RobTillaart/I2C_EEPROM


#include "I2C_eeprom.h"


//  Not used directly
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
#if defined(ESP32) || defined(ESP8266) || defined(PICO_RP2040)
#define I2C_BUFFERSIZE           128
#else
#define I2C_BUFFERSIZE           30   //  AVR, STM
#endif


////////////////////////////////////////////////////////////////////
//
//  PUBLIC FUNCTIONS
//
I2C_eeprom::I2C_eeprom(const uint8_t deviceAddress, TwoWire * wire) :
            I2C_eeprom(deviceAddress, I2C_PAGESIZE_24LC256, wire)
{
}


I2C_eeprom::I2C_eeprom(const uint8_t deviceAddress, const uint32_t deviceSize, TwoWire * wire)
{
  _deviceAddress = deviceAddress;
  _deviceSize = setDeviceSize(deviceSize);
  _pageSize = getPageSize(_deviceSize);
  _wire = wire;

  //  Chips 16 Kbit (2048 Bytes) or smaller only have one-word addresses.
  this->_isAddressSizeTwoWords = deviceSize > I2C_DEVICESIZE_24LC16;
}


bool I2C_eeprom::begin(int8_t writeProtectPin)
{
  //  if (_wire == 0) SPRNL("zero");  //  test #48
  _lastWrite = 0;
  _writeProtectPin = writeProtectPin;
  if (_writeProtectPin >= 0)
  {
    _autoWriteProtect = EN_AUTO_WRITE_PROTECT;
    pinMode(_writeProtectPin, OUTPUT);
    preventWrite();
  }
  return isConnected();
}


bool I2C_eeprom::isConnected()
{
  _wire->beginTransmission(_deviceAddress);
  return (_wire->endTransmission() == 0);
}


uint8_t I2C_eeprom::getAddress()
{
  return _deviceAddress;
}


/////////////////////////////////////////////////////////////
//
//  WRITE SECTION
//

//  returns I2C status, 0 = OK
int I2C_eeprom::writeByte(const uint16_t memoryAddress, const uint8_t data)
{
  int rv = _WriteBlock(memoryAddress, &data, 1);
  return rv;
}


//  returns I2C status, 0 = OK
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


//  returns I2C status, 0 = OK
int I2C_eeprom::writeBlock(const uint16_t memoryAddress, const uint8_t * buffer, const uint16_t length)
{
  int rv = _pageBlock(memoryAddress, buffer, length, true);
  return rv;
}


/////////////////////////////////////////////////////////////
//
//  READ SECTION
//

//  returns the value stored in memoryAddress
uint8_t I2C_eeprom::readByte(const uint16_t memoryAddress)
{
  uint8_t rdata;
  _ReadBlock(memoryAddress, &rdata, 1);
  return rdata;
}


//  returns bytes read.
uint16_t I2C_eeprom::readBlock(const uint16_t memoryAddress, uint8_t * buffer, const uint16_t length)
{
  uint16_t address = memoryAddress;
  uint16_t len = length;
  uint16_t bytes = 0;
  while (len > 0)
  {
    uint8_t count = I2C_BUFFERSIZE;
    if (count > len) count = len;
    bytes   += _ReadBlock(address, buffer, count);
    address += count;
    buffer  += count;
    len     -= count;
  }
  return bytes;
}


//  returns true or false.
bool I2C_eeprom::verifyBlock(const uint16_t memoryAddress, const uint8_t * buffer, const uint16_t length)
{
  uint16_t address = memoryAddress;
  uint16_t len = length;
  while (len > 0)
  {
    uint8_t count = I2C_BUFFERSIZE;
    if (count > len) count = len;
    if (_verifyBlock(address, buffer, count) == false)
    {
      return false;
    }
    address += count;
    buffer  += count;
    len     -= count;
  }
  return true;
}


/////////////////////////////////////////////////////////////
//
//  UPDATE SECTION
//

//  returns 0 == OK
int I2C_eeprom::updateByte(const uint16_t memoryAddress, const uint8_t data)
{
  if (data == readByte(memoryAddress)) return 0;
  return writeByte(memoryAddress, data);
}


//  returns bytes written.
uint16_t I2C_eeprom::updateBlock(const uint16_t memoryAddress, const uint8_t * buffer, const uint16_t length)
{
  uint16_t address = memoryAddress;
  uint16_t len = length;
  uint16_t bytes = 0;
  while (len > 0)
  {
    uint8_t buf[I2C_BUFFERSIZE];
    uint8_t count = I2C_BUFFERSIZE;

    if (count > len) count = len;
    bytes += _ReadBlock(address, buf, count);
    if (memcmp(buffer, buf, count) != 0)
    {
      _pageBlock(address, buffer, count, true);
    }
    address += count;
    buffer  += count;
    len     -= count;
  }
  return bytes;
}


/////////////////////////////////////////////////////////////
//
//  VERIFY SECTION
//

//  return false if write or verify failed.
bool I2C_eeprom::writeByteVerify(const uint16_t memoryAddress, const uint8_t value)
{
  if (writeByte(memoryAddress, value) != 0 ) return false;
  uint8_t data = readByte(memoryAddress);
  return (data == value);
}


//  return false if write or verify failed.
bool I2C_eeprom::writeBlockVerify(const uint16_t memoryAddress, const uint8_t * buffer, const uint16_t length)
{
  if (writeBlock(memoryAddress, buffer, length) != 0) return false;
  return verifyBlock(memoryAddress, buffer, length);
}


//  return false if write or verify failed.
bool I2C_eeprom::setBlockVerify(const uint16_t memoryAddress, const uint8_t value, const uint16_t length)
{
  if (setBlock(memoryAddress, value, length) != 0) return false;
  uint8_t * data = (uint8_t *) malloc(length);
  if (data == NULL) return false;
  if (readBlock(memoryAddress, data, length) != length) return false;
  for (uint16_t i = 0; i < length; i++)
  {
    if (data[i] != value)
    {
      free(data);
      return false;
    }
  }
  free(data);
  return true;
}


//  return false if write or verify failed.
bool I2C_eeprom::updateByteVerify(const uint16_t memoryAddress, const uint8_t value)
{
  if (updateByte(memoryAddress, value) != 0 ) return false;
  uint8_t data = readByte(memoryAddress);
  return (data == value);
}


//  return false if write or verify failed.
bool I2C_eeprom::updateBlockVerify(const uint16_t memoryAddress, const uint8_t * buffer, const uint16_t length)
{
  if (updateBlock(memoryAddress, buffer, length) != length) return false;
  return verifyBlock(memoryAddress, buffer, length);
}


/////////////////////////////////////////////////////////////
//
//  METADATA SECTION
//

//  returns size in bytes
//  returns 0 if not connected
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

    //  store old values
    bool addressSize = _isAddressSizeTwoWords;
    _isAddressSizeTwoWords = size > I2C_DEVICESIZE_24LC16;  // 2048
    uint8_t buf = readByte(size);

    //  test folding
    uint8_t count = 0;
    writeByte(size, pat55);
    if (readByte(0) == pat55) count++;
    writeByte(size, patAA);
    if (readByte(0) == patAA) count++;
    folded = (count == 2);
    if (debug)
    {
      SPRNH(size, HEX);
      SPRN('\t');
      SPRNLH(readByte(size), HEX);
    }

    //  restore old values
    writeByte(size, buf);
    _isAddressSizeTwoWords = addressSize;

    if (folded) return size;
  }
  return 0;
}


//  new 1.8.1 #61
//  updated 1.8.2 #63
//
// Returns:
//  0 if device size cannot be determined or device is not online
//  1 if device has default bytes in first dataFirstBytes bytes [0-BUFSIZE]
//      Write some dataFirstBytes to the first bytes and retry or use the determineSize method
//  2 if device has all the same bytes in first dataFirstBytes bytes [0-BUFSIZE]
//      Write some random dataFirstBytes to the first bytes and retry or use the determineSize method
//  >= 128 Device size in bytes
uint32_t I2C_eeprom::determineSizeNoWrite()
{
  #define BUFSIZE (32)
  //  try to read a byte to see if connected
  if (!isConnected()) return 0;

  bool addressSize = _isAddressSizeTwoWords;
  _isAddressSizeTwoWords = true;  //  Otherwise reading large EEPROMS fails
  bool isModifiedFirstSector = false;
  bool dataIsDifferent = false;

  byte dataFirstBytes[BUFSIZE];
  byte dataMatch[BUFSIZE];
  readBlock(0, dataFirstBytes, BUFSIZE);

  for (uint8_t pos = 0; pos < BUFSIZE; pos++)
  {
      if (dataIsDifferent || pos == 0)
      {
          //  ignore further comparison if dataFirstBytes is not the same in buffer
          //  Ignore first byte
      }
      else if (dataFirstBytes[pos - 1] != dataFirstBytes[pos])
      {
          dataIsDifferent = true;
      }

      if (dataFirstBytes[pos] != 0xFF && dataFirstBytes[pos] != 0x00)
      {
          //  Default dataFirstBytes value is 0xFF or 0x00
          isModifiedFirstSector = true;
      }

      if (dataIsDifferent && isModifiedFirstSector)
          break;
  }

  if (!isModifiedFirstSector)
  {
      //  Cannot determine diff, at least one of the first bytes within 0 - len [BUFSIZE] needs to be changed
      //  to something other than 0x00 and 0xFF
      _isAddressSizeTwoWords = addressSize;
      return 1;
  }
  if (!dataIsDifferent)
  {
      //  Data in first bytes within 0 - len [BUFSIZE] are all the same.
      _isAddressSizeTwoWords = addressSize;
      return 2;
  }

  //  Read from largest to smallest size
  for (uint32_t size = 32768; size >= 64; size /= 2)
  {
    _isAddressSizeTwoWords = (size >= I2C_DEVICESIZE_24LC16);  //  == 2048

    //  Try to read last byte of the block, should return length of 0 when fails for single byte devices
    //  Will return the same dataFirstBytes as initially read on other devices 
    //  as the data pointer could not be moved to the requested position
    delay(2);
    uint16_t bSize = readBlock(size, dataMatch, BUFSIZE);

    if (bSize == BUFSIZE && memcmp(dataFirstBytes, dataMatch, BUFSIZE) != 0)
    {
        //  Read is performed just over size (size + BUFSIZE), 
        //  this will only work for devices with mem > size;
        //  therefore return size * 2
        _isAddressSizeTwoWords = addressSize;
        return size * 2;
    }
  }
  _isAddressSizeTwoWords = addressSize;
  return 0;
}


uint32_t I2C_eeprom::getDeviceSize()
{
  return _deviceSize;
}


uint8_t I2C_eeprom::getPageSize()
{
  return _pageSize;
}


uint8_t I2C_eeprom::getPageSize(uint32_t deviceSize)
{
    //  determine page size from device size
    //  based on Microchip 24LCXX data sheets.
    if (deviceSize <= I2C_DEVICESIZE_24LC02) return 8;
    if (deviceSize <= I2C_DEVICESIZE_24LC16) return 16;
    if (deviceSize <= I2C_DEVICESIZE_24LC64) return 32;
    if (deviceSize <= I2C_DEVICESIZE_24LC256) return 64;
    //  I2C_DEVICESIZE_24LC512
    return 128;
}


uint32_t I2C_eeprom::getLastWrite()
{
  return _lastWrite;
}


uint32_t I2C_eeprom::setDeviceSize(uint32_t deviceSize)
{
  uint32_t size = 128;
  //  force power of 2.
  while ((size <= 65536) && ( size <= deviceSize))
  {
    _deviceSize = size;
    size *= 2;
  }
  //  Chips 16 Kbit (2048 Bytes) or smaller only have one-word addresses.
  this->_isAddressSizeTwoWords = _deviceSize > I2C_DEVICESIZE_24LC16;
  return _deviceSize;
}


uint8_t I2C_eeprom::setPageSize(uint8_t pageSize)
{
  // force power of 2.
  if (pageSize >= 128) {
      _pageSize = 128;
  }
  else if (pageSize >= 64) {
      _pageSize = 64;
  }
  else if (pageSize >= 32) {
      _pageSize = 32;
  }
  else if (pageSize >= 16) {
      _pageSize = 16;
  }
  else {
      _pageSize = 8;
  }
  return _pageSize;
}


void I2C_eeprom::setExtraWriteCycleTime(uint8_t ms)
{
  _extraTWR = ms;
}


uint8_t I2C_eeprom::getExtraWriteCycleTime()
{
  return _extraTWR;
}


//
//  WRITEPROTECT
//
bool I2C_eeprom::hasWriteProtectPin()
{
  return (_writeProtectPin >= 0);
}


void I2C_eeprom::allowWrite()
{
  if (hasWriteProtectPin())
  {
    digitalWrite(_writeProtectPin, LOW);
  }
}


void I2C_eeprom::preventWrite()
{
  if (hasWriteProtectPin())
  {
    digitalWrite(_writeProtectPin, HIGH);
  }
}


void I2C_eeprom::setAutoWriteProtect(bool b)
{
  if (hasWriteProtectPin())
  {
    _autoWriteProtect = b;
  }
}


bool I2C_eeprom::getAutoWriteProtect()
{
  return _autoWriteProtect;
}


////////////////////////////////////////////////////////////////////
//
//  PRIVATE
//

//  _pageBlock aligns buffer to page boundaries for writing.
//  and to I2C buffer size
//  returns 0 = OK otherwise error
int I2C_eeprom::_pageBlock(const uint16_t memoryAddress, const uint8_t * buffer, const uint16_t length, const bool incrBuffer)
{
  uint16_t address = memoryAddress;
  uint16_t len = length;
  while (len > 0)
  {
    uint8_t bytesUntilPageBoundary = this->_pageSize - address % this->_pageSize;

    uint8_t count = I2C_BUFFERSIZE;
    if (count > len) count = len;
    if (count > bytesUntilPageBoundary) count = bytesUntilPageBoundary;

    int rv = _WriteBlock(address, buffer, count);
    if (rv != 0) return rv;

    address += count;
    if (incrBuffer) buffer += count;
    len -= count;
  }
  return 0;
}


//  supports one and two bytes addresses
void I2C_eeprom::_beginTransmission(const uint16_t memoryAddress)
{
  if (this->_isAddressSizeTwoWords)
  {
  _wire->beginTransmission(_deviceAddress);
    //  Address High Byte
    _wire->write((memoryAddress >> 8));
  }
  else
  {
    uint8_t address = _deviceAddress | ((memoryAddress >> 8) & 0x07);
    _wire->beginTransmission(address);
  }

  //  Address Low Byte
  //  (or single byte for chips 16K or smaller that have one-word addresses)
  _wire->write((memoryAddress & 0xFF));
}


//  pre: length <= this->_pageSize  && length <= I2C_BUFFERSIZE;
//  returns 0 = OK otherwise error
int I2C_eeprom::_WriteBlock(const uint16_t memoryAddress, const uint8_t * buffer, const uint16_t length)
{
  _waitEEReady();
  if (_autoWriteProtect)
  {
    digitalWrite(_writeProtectPin, LOW);
  }

  this->_beginTransmission(memoryAddress);
  _wire->write(buffer, length);
  int rv = _wire->endTransmission();

  if (_autoWriteProtect)
  {
    digitalWrite(_writeProtectPin, HIGH);
  }

  _lastWrite = micros();

  yield();     // For OS scheduling

//  if (rv != 0)
//  {
//    if (_debug)
//    {
//      SPRN("mem addr w: ");
//      SPRNH(memoryAddress, HEX);
//      SPRN("\t");
//      SPRNL(rv);
//    }
//    return -(abs(rv));  // error
//  }
  return rv;
}


//  pre: buffer is large enough to hold length bytes
//  returns bytes read
uint8_t I2C_eeprom::_ReadBlock(const uint16_t memoryAddress, uint8_t * buffer, const uint16_t length)
{
  _waitEEReady();

  this->_beginTransmission(memoryAddress);
  int rv = _wire->endTransmission();
  if (rv != 0)
  {
//    if (_debug)
//    {
//      SPRN("mem addr r: ");
//      SPRNH(memoryAddress, HEX);
//      SPRN("\t");
//      SPRNL(rv);
//    }
    return 0;  //  error
  }

  //  readBytes will always be equal or smaller to length
  uint8_t readBytes = 0;
  if (this->_isAddressSizeTwoWords)
  {
    readBytes = _wire->requestFrom((int)_deviceAddress, (int)length);
  }
  else
  {
    uint8_t address = _deviceAddress | ((memoryAddress >> 8) & 0x07);
    readBytes = _wire->requestFrom((int)address, (int)length);
  }
  yield();     //  For OS scheduling
  uint8_t count = 0;
  while (count < readBytes)
  {
    buffer[count++] = _wire->read();
  }
  return readBytes;
}


//  compares content of EEPROM with buffer.
//  returns true if equal.
bool I2C_eeprom::_verifyBlock(const uint16_t memoryAddress, const uint8_t * buffer, const uint16_t length)
{
  _waitEEReady();

  this->_beginTransmission(memoryAddress);
  int rv = _wire->endTransmission();
  if (rv != 0)
  {
//    if (_debug)
//    {
//      SPRN("mem addr r: ");
//      SPRNH(memoryAddress, HEX);
//      SPRN("\t");
//      SPRNL(rv);
//    }
    return false;  //  error
  }

  //  readBytes will always be equal or smaller to length
  uint8_t readBytes = 0;
  if (this->_isAddressSizeTwoWords)
  {
    readBytes = _wire->requestFrom((int)_deviceAddress, (int)length);
  }
  else
  {
    uint8_t address = _deviceAddress | ((memoryAddress >> 8) & 0x07);
    readBytes = _wire->requestFrom((int)address, (int)length);
  }
  yield();     //  For OS scheduling
  uint8_t count = 0;
  while (count < readBytes)
  {
    if (buffer[count++] != _wire->read())
    {
      return false;
    }
  }
  return true;
}


void I2C_eeprom::_waitEEReady()
{
  //  Wait until EEPROM gives ACK again.
  //  this is a bit faster than the hardcoded 5 milliSeconds
  //  TWR = WriteCycleTime
  uint32_t waitTime = I2C_WRITEDELAY + _extraTWR * 1000UL;
  while ((micros() - _lastWrite) <= waitTime)
  {
    if (isConnected()) return;
    //  TODO remove pre 1.7.4 code
    // _wire->beginTransmission(_deviceAddress);
    // int x = _wire->endTransmission();
    // if (x == 0) return;
    yield();     //  For OS scheduling
  }
  return;
}


//  -- END OF FILE --

