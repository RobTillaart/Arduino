#pragma once
//
//    FILE: I2C_eeprom.h
//  AUTHOR: Rob Tillaart
// VERSION: 1.5.2
// PURPOSE: Arduino Library for external I2C EEPROM 24LC256 et al.
//     URL: https://github.com/RobTillaart/I2C_EEPROM.git
//
// HISTORY: See I2C_eeprom.cpp


#include "Arduino.h"
#include "Wire.h"


#define I2C_EEPROM_VERSION          (F("1.5.2"))


#define I2C_DEVICESIZE_24LC512      65536
#define I2C_DEVICESIZE_24LC256      32768
#define I2C_DEVICESIZE_24LC128      16384
#define I2C_DEVICESIZE_24LC64        8192
#define I2C_DEVICESIZE_24LC32        4096
#define I2C_DEVICESIZE_24LC16        2048
#define I2C_DEVICESIZE_24LC08        1024
#define I2C_DEVICESIZE_24LC04         512
#define I2C_DEVICESIZE_24LC02         256
#define I2C_DEVICESIZE_24LC01         128


#ifndef UNIT_TEST_FRIEND
#define UNIT_TEST_FRIEND
#endif


class I2C_eeprom
{
public:
  /**
    * Initializes the EEPROM with a default deviceSize of I2C_DEVICESIZE_24LC256  (32K EEPROM)
    */
  I2C_eeprom(const uint8_t deviceAddress, TwoWire *wire = &Wire);

  /**
    * Initializes the EEPROM for the given device address.
    *
    * It will try to guess page size and address word size based on the size of the device.
    *
    * @param deviceAddress Byte address of the device.
    * @param deviceSize    Max size in bytes of the device (divide your device size in Kbits by 8)
    * @param wire          Select alternative Wire interface
    */
  I2C_eeprom(const uint8_t deviceAddress, const uint32_t deviceSize, TwoWire *wire = &Wire);

#if defined (ESP8266) || defined(ESP32)
  bool     begin(uint8_t sda, uint8_t scl);
#endif
  bool     begin();

  bool     isConnected();

  //  writes a byte to memoryAddress
  int      writeByte(const uint16_t memoryAddress, const uint8_t value);
  //  writes length bytes from buffer to EEPROM
  int      writeBlock(const uint16_t memoryAddress, const uint8_t* buffer, const uint16_t length);
  //  set length bytes in the EEPROM to the same value.
  int      setBlock(const uint16_t memoryAddress, const uint8_t value, const uint16_t length);


  //  returns the value stored in memoryAddress
  uint8_t  readByte(const uint16_t memoryAddress);
  //  reads length bytes into buffer
  uint16_t readBlock(const uint16_t memoryAddress, uint8_t* buffer, const uint16_t length);


  //  updates a byte at memoryAddress, writes only if there is a new value.
  //  return 0 if data is same or written OK, error code otherwise.
  int      updateByte(const uint16_t memoryAddress, const uint8_t value);
  //  updates a block in memory, writes only if there is a new value.
  //  only to be used when you expect to write same buffer multiple times.
  //  test your performance gains!
  int      updateBlock(const uint16_t memoryAddress, const uint8_t* buffer, const uint16_t length);

  uint32_t determineSize(const bool debug = false);

  uint32_t getDeviceSize() { return _deviceSize; };
  uint8_t  getPageSize()   { return _pageSize; };
  uint8_t  getPageSize(uint32_t deviceSize);
  uint32_t getLastWrite()  { return _lastWrite; };

  //  TWR = WriteCycleTime
  //  5 ms is minimum, one can add extra ms here to adjust timing of both read() and write()
  void     setExtraWriteCycleTime(uint8_t ms) { _extraTWR = ms; };
  uint8_t  getExtraWriteCycleTime() { return _extraTWR; };

private:
  uint8_t  _deviceAddress;
  uint32_t _lastWrite;       // for waitEEReady
  uint32_t _deviceSize;
  uint8_t  _pageSize;
  uint8_t  _extraTWR = 0;    // milliseconds

  //  24LC32..24LC512 use two bytes for memory address
  //  24LC01..24LC16  use one-byte addresses + part of device address
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

  //  to optimize the write latency of the EEPROM
  void     _waitEEReady();

  TwoWire * _wire;

  UNIT_TEST_FRIEND;
};


// -- END OF FILE --

