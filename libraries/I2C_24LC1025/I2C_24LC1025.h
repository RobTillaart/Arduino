#pragma once
//
//    FILE: I2C_24LC1025.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.3
// PURPOSE: I2C_24LC1025 library for Arduino with EEPROM 24FC1025 et al.
// HISTORY: See I2C_24LC1025.cpp
//     URL: https://github.com/RobTillaart/I2C_24LC1025


#include "Arduino.h"
#include "Wire.h"


#define I2C_24LC1025_VERSION        (F("0.1.3"))


#define I2C_DEVICESIZE_24LC512      131072
#define I2C_24LC1025_PAGESIZE       128


class I2C_24LC1025
{
public:

  I2C_24LC1025(uint8_t deviceAddress, TwoWire *wire = &Wire);

#if defined (ESP8266) || defined(ESP32)
  bool      begin(uint8_t sda, uint8_t scl);
#endif
  bool      begin();
  bool      isConnected();


  // writes a byte to memaddr
  int       writeByte(const uint32_t memoryAddress, const uint8_t value);
  // writes length bytes from buffer to EEPROM
  int       writeBlock(const uint32_t memoryAddress, const uint8_t *buffer, const uint32_t length);
  // set length bytes in the EEPROM to the same value.
  int       setBlock(const uint32_t memoryAddress, const uint8_t value, const uint32_t length);


  // returns the value stored in memaddr
  uint8_t   readByte(const uint32_t memoryAddress);
  // reads length bytes into buffer
  uint32_t  readBlock(const uint32_t memoryAddress, uint8_t *buffer, const uint32_t length);

  // updates a byte at memory address, writes only if there is a new value.
  // return 0 if data is same or written OK, error code otherwise.
  int      updateByte(const uint32_t memoryAddress, const uint8_t value);
  // updates a block in memory, writes only if there is a new value.
  // only to be used when you expect to write same buffer multiple times. 
  // test your performance gains!
  int      updateBlock(const uint32_t memoryAddress, const uint8_t* buffer, const uint32_t length);


  uint32_t getDeviceSize() { return _deviceSize; };
  uint8_t  getPageSize()   { return _pageSize; };
  uint32_t getLastWrite()  { return _lastWrite; };


private:
  uint8_t  _deviceAddress;
  uint8_t  _actualAddress;   // a.k.a. controlByte
  uint32_t _lastWrite;
  uint32_t _deviceSize = I2C_DEVICESIZE_24LC512;
  uint8_t  _pageSize = I2C_24LC1025_PAGESIZE;
  int      _error;  // TODO.


  void      _beginTransmission(uint32_t memoryAddress);

  int       _pageBlock(uint32_t memoryAddress, const uint8_t* buffer, const uint16_t length, const bool incrBuffer);
  int       _WriteBlock(uint32_t memoryAddress, const uint8_t* buffer, const uint8_t length);
  int       _ReadBlock(uint32_t memoryAddress, uint8_t* buffer, const uint8_t length);

  TwoWire * _wire;

  bool      _debug = true;
};

// -- END OF FILE --
