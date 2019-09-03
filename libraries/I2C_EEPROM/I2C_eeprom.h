#ifndef I2C_EEPROM_H
#define I2C_EEPROM_H
//
//    FILE: I2C_eeprom.h
//  AUTHOR: Rob Tillaart
// PURPOSE: I2C_eeprom library for Arduino with EEPROM 24LC256 et al.
// VERSION: 1.2.7
// HISTORY: See I2C_eeprom.cpp
//     URL: http://arduino.cc/playground/Main/LibraryForI2CEEPROM
//
// Released to the public domain
//

#include "Wire.h"

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#include "Wstring.h"
#include "Wiring.h"
#endif

#define I2C_EEPROM_VERSION "1.2.7"

// The DEFAULT page size. This is overriden if you use the second constructor.
// I2C_EEPROM_PAGESIZE must be multiple of 2 e.g. 16, 32 or 64
// 24LC256 -> 64 bytes
#define I2C_EEPROM_PAGESIZE 64

// TWI buffer needs max 2 bytes for eeprom address
// 1 byte for eeprom register address is available in txbuffer
#define I2C_TWIBUFFERSIZE  30

// comment next line to keep lib small (idea a read only lib?)
#define I2C_EEPROM_EXTENDED

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

  void begin();
  int writeByte(const uint16_t memoryAddress, const uint8_t value);
  int writeBlock(const uint16_t memoryAddress, const uint8_t* buffer, const uint16_t length);
  int setBlock(const uint16_t memoryAddress, const uint8_t value, const uint16_t length);

  uint8_t readByte(const uint16_t memoryAddress);
  uint16_t readBlock(const uint16_t memoryAddress, uint8_t* buffer, const uint16_t length);

#ifdef I2C_EEPROM_EXTENDED
  int determineSize();
#endif

private:
  uint8_t _deviceAddress;
  uint32_t _lastWrite;     // for waitEEReady
  uint8_t _pageSize;

  // for some smaller chips that use one-word addresses
  bool _isAddressSizeTwoWords;

  /**
    * Begins wire transmission and selects the given address to write/read.
    * 
    * @param memoryAddress Address to write/read
    */
  void _beginTransmission(const uint16_t memoryAddress);

  int _pageBlock(const uint16_t memoryAddress, const uint8_t* buffer, const uint16_t length, const bool incrBuffer);
  int _WriteBlock(const uint16_t memoryAddress, const uint8_t* buffer, const uint8_t length);
  uint8_t _ReadBlock(const uint16_t memoryAddress, uint8_t* buffer, const uint8_t length);

  void waitEEReady();
};

#endif
// END OF FILE