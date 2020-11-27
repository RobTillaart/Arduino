#pragma once
//
//    FILE: I2C_eeprom.h
//  AUTHOR: Rob Tillaart
// VERSION: 1.3.0
// PURPOSE: Arduino Library for external I2C EEPROM 24LC256 et al.
//     URL: https://github.com/RobTillaart/I2C_EEPROM.git
//
// HISTORY: See I2C_eeprom.cpp


#include "Wire.h"
#include "Arduino.h"

#define I2C_EEPROM_VERSION "1.3.0"

// The DEFAULT page size. This is overriden if you use the second constructor.
// I2C_EEPROM_PAGESIZE must be multiple of 2 e.g. 16, 32 or 64
// 24LC256 -> 64 bytes
#define I2C_EEPROM_PAGESIZE 64

// TWI buffer needs max 2 bytes for eeprom address
// 1 byte for eeprom register address is available in txbuffer
#define I2C_TWIBUFFERSIZE  30

class I2C_eeprom
{
public:
  /**
    * Initializes the EEPROM with a default pagesize of I2C_EEPROM_PAGESIZE.
    */
  I2C_eeprom(const uint8_t deviceAddress);

  /**
    * Initializes the EEPROM for the given device address.
    *
    * It will try to guess page size and address word size based on the size of the device.
    *
    * @param deviceAddress Byte address of the device.
    * @param deviceSize    Max size in bytes of the device (divide your device size in Kbits by 8)
    */
  I2C_eeprom(const uint8_t deviceAddress, const unsigned int deviceSize);

#if defined (ESP8266) || defined(ESP32)
  void begin(uint8_t sda, uint8_t scl);
#endif
  void begin();

  // writes a byte to memaddr
  int writeByte(const uint16_t memoryAddress, const uint8_t value);
  // writes length bytes from buffer to EEPROM
  int writeBlock(const uint16_t memoryAddress, const uint8_t* buffer, const uint16_t length);
  // set length bytes in the EEPROM to the same value.
  int setBlock(const uint16_t memoryAddress, const uint8_t value, const uint16_t length);

  // returns the value stored in memaddr
  uint8_t  readByte(const uint16_t memoryAddress);
  // reads length bytes into buffer
  uint16_t readBlock(const uint16_t memoryAddress, uint8_t* buffer, const uint16_t length);

  int      determineSize();


private:
  uint8_t  _deviceAddress;
  uint32_t _lastWrite;     // for waitEEReady
  uint8_t  _pageSize;

  // for some smaller chips that use one-word addresses
  bool     _isAddressSizeTwoWords;

  /**
    * Begins wire transmission and selects the given address to write/read.
    *
    * @param memoryAddress Address to write/read
    */
  void     _beginTransmission(const uint16_t memoryAddress);

  int      _pageBlock(const uint16_t memoryAddress, const uint8_t* buffer, const uint16_t length, const bool incrBuffer);
  int      _WriteBlock(const uint16_t memoryAddress, const uint8_t* buffer, const uint8_t length);
  uint8_t  _ReadBlock(const uint16_t memoryAddress, uint8_t* buffer, const uint8_t length);

  void     _waitEEReady();
};

// -- END OF FILE --
