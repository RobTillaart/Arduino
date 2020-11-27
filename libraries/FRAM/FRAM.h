#pragma once
//
//    FILE: FRAM.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.1
//    DATE: 2018-01-24
// PURPOSE: Arduino library for I2C FRAM
//     URL: https://github.com/RobTillaart/FRAM_I2C
//
// HISTORY:
// see FRAM.cpp file
//

#include "Arduino.h"
#include "Wire.h"

#define FRAM_LIB_VERSION (F("0.2.1"))

#define FRAM_OK               0
#define FRAM_ERROR_ADDR       -10

class FRAM
{
public:
  FRAM();

  // writeProtectPin is optional
  int   begin(const uint8_t address = 0x50, int8_t writeProtectPin = -1);

  void  write8(uint16_t memaddr, uint8_t value);
  void  write16(uint16_t memaddr, uint16_t value);
  void  write32(uint16_t memaddr, uint32_t value);
  void  write(uint16_t memaddr, uint8_t * obj, uint16_t size);

  uint8_t  read8(uint16_t memaddr);
  uint16_t read16(uint16_t memaddr);
  uint32_t read32(uint16_t memaddr);
  void     read(uint16_t memaddr, uint8_t * obj, uint16_t size);

  bool     setWriteProtect(bool b);

  uint16_t getManufacturerID();
  uint16_t getProductID();
  uint16_t getSize();

private:
  uint8_t   _address;
  int8_t    _writeProtectPin = -1;  // default no pin ==> no write protect.

  uint16_t getMetaData(uint8_t id);
  void writeBlock(uint16_t memaddr, uint8_t * obj, uint8_t size);
  void readBlock(uint16_t memaddr, uint8_t * obj, uint8_t size);
};

// -- END OF FILE --
