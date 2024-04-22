#pragma once
//
//    FILE: I2C_eeprom.h
//  AUTHOR: Rob Tillaart
// VERSION: 1.8.5
// PURPOSE: Arduino Library for external I2C EEPROM 24LC256 et al.
//     URL: https://github.com/RobTillaart/I2C_EEPROM


#include "Arduino.h"
#include "Wire.h"


#define I2C_EEPROM_VERSION          (F("1.8.5"))

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


//  AT24C32 has a WriteCycle Time of max 20 ms
//  so one need to set I2C_WRITEDELAY to 20000.
//  can also be done on command line.
//  (see private _waitEEReady() function)
#ifndef I2C_WRITEDELAY
#define I2C_WRITEDELAY              5000
#endif


//  set the flag EN_AUTO_WRITE_PROTECT to 1 to enable the Write Control at compile time 
//  used if the write_protect pin is explicitly set in the begin() function.
//  the flag can be set as command line option.
#ifndef EN_AUTO_WRITE_PROTECT
#define EN_AUTO_WRITE_PROTECT       0
#endif


#ifndef UNIT_TEST_FRIEND
#define UNIT_TEST_FRIEND
#endif

//#define ENABLE_DEBUG

#ifdef ENABLE_DEBUG
#define SPRN Serial.print
#define SPRNL Serial.println
#define SPRNH Serial.print
#define SPRNLH Serial.println
#else
#define SPRN(MSG)
#define SPRNH(MSG,MSG2)
#define SPRNL(MSG)
#define SPRNLH(MSG,MSG2)
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

  //  use default I2C pins.
  bool     begin(int8_t writeProtectPin = -1);
  bool     isConnected();
  uint8_t  getAddress();


  //  writes a byte to memoryAddress
  //  returns I2C status, 0 = OK
  int      writeByte(const uint16_t memoryAddress, const uint8_t value);
  //  writes length bytes from buffer to EEPROM
  //  returns I2C status, 0 = OK
  int      writeBlock(const uint16_t memoryAddress, const uint8_t * buffer, const uint16_t length);
  //  set length bytes in the EEPROM to the same value.
  //  returns I2C status, 0 = OK
  int      setBlock(const uint16_t memoryAddress, const uint8_t value, const uint16_t length);


  //  returns the value stored in memoryAddress
  uint8_t  readByte(const uint16_t memoryAddress);
  //  reads length bytes into buffer
  //  returns bytes read.
  uint16_t readBlock(const uint16_t memoryAddress, uint8_t * buffer, const uint16_t length);
  bool     verifyBlock(const uint16_t memoryAddress, const uint8_t * buffer, const uint16_t length);

  //  updates a byte at memoryAddress, writes only if there is a new value.
  //  return 0 if data is same or written OK, error code otherwise.
  int      updateByte(const uint16_t memoryAddress, const uint8_t value);
  //  updates a block in memory, writes only if there is a new value.
  //  only to be used when you expect to write same buffer multiple times.
  //  test your performance gains!
  //  returns bytes written.
  uint16_t updateBlock(const uint16_t memoryAddress, const uint8_t * buffer, const uint16_t length);


  //  same functions as above but with verify
  //  return false if write or verify failed.
  bool     writeByteVerify(const uint16_t memoryAddress, const uint8_t value);
  bool     writeBlockVerify(const uint16_t memoryAddress, const uint8_t * buffer, const uint16_t length);
  bool     setBlockVerify(const uint16_t memoryAddress, const uint8_t value, const uint16_t length);
  bool     updateByteVerify(const uint16_t memoryAddress, const uint8_t value);
  bool     updateBlockVerify(const uint16_t memoryAddress, const uint8_t * buffer, const uint16_t length);


  //  Meta data functions
  uint32_t determineSize(const bool debug = false);
  uint32_t determineSizeNoWrite();
  uint32_t getDeviceSize();
  uint8_t  getPageSize();
  uint8_t  getPageSize(uint32_t deviceSize);
  uint32_t getLastWrite();


  //  for overruling and debugging.
  //  forces a power of 2
  uint32_t setDeviceSize(uint32_t deviceSize);  //  returns set size
  uint8_t  setPageSize(uint8_t pageSize);       //  returns set size


  //  TWR = WriteCycleTime
  //  5 ms is minimum, one can add extra ms here to adjust timing of both read() and write()
  void     setExtraWriteCycleTime(uint8_t ms);
  uint8_t  getExtraWriteCycleTime();


  //  WRITEPROTECT
  //  works only if WP pin is defined in begin().
  //  see readme.md
  inline bool hasWriteProtectPin();
  void     allowWrite();
  void     preventWrite();
  void     setAutoWriteProtect(bool b);
  bool     getAutoWriteProtect();


private:
  uint8_t  _deviceAddress;
  uint32_t _lastWrite  = 0;  //  for waitEEReady
  uint32_t _deviceSize = 0;
  uint8_t  _pageSize   = 0;
  uint8_t  _extraTWR   = 0;  //  milliseconds


  //  24LC32..24LC512 use two bytes for memory address
  //  24LC01..24LC16  use one-byte addresses + part of device address
  bool     _isAddressSizeTwoWords;

  void     _beginTransmission(const uint16_t memoryAddress);

  //  returns I2C status, 0 = OK
  //  TODO incrBuffer is an implementation name, not a functional name.
  int      _pageBlock(const uint16_t memoryAddress, const uint8_t * buffer, const uint16_t length, const bool incrBuffer);
  //  returns I2C status, 0 = OK
  int      _WriteBlock(const uint16_t memoryAddress, const uint8_t * buffer, const uint16_t length);
  //  returns bytes read.
  uint8_t  _ReadBlock(const uint16_t memoryAddress, uint8_t * buffer, const uint16_t length);
  //  compare bytes in EEPROM.
  bool     _verifyBlock(const uint16_t memoryAddress, const uint8_t * buffer, const uint16_t length);

  //  to optimize the write latency of the EEPROM
  void     _waitEEReady();

  TwoWire * _wire;

  bool     _debug = false;

  int8_t   _writeProtectPin = -1;
  bool     _autoWriteProtect = EN_AUTO_WRITE_PROTECT;

  UNIT_TEST_FRIEND;
};


//  -- END OF FILE --

