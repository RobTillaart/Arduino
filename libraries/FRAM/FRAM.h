//
//    FILE: FRAM.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
// PURPOSE: Class for FRAM memory
//     URL:
//
// HISTORY:
// see FRAM.cpp file
//

#ifndef FRAM_H
#define FRAM_H

#include "Arduino.h"
#include "Wire.h"

#define FRAM_LIB_VERSION (F("0.1.1"))

#define FRAM_OK               0
#define FRAM_ERROR_ADDR       -10

class FRAM
{
public:
  FRAM();

  int   begin(const int address);  // defaults to 0x50

  void  write8(uint16_t memaddr, uint8_t value);
  void  write16(uint16_t memaddr, uint16_t value);
  void  write32(uint16_t memaddr, uint32_t value);
  void  write(uint16_t memaddr, uint8_t * obj, uint16_t size);

  uint8_t  read8(uint16_t memaddr);
  uint16_t read16(uint16_t memaddr);
  uint32_t read32(uint16_t memaddr);
  void     read(uint16_t memaddr, uint8_t * obj, uint16_t size);

  uint16_t getManufacturerID();
  uint16_t getProductID();
  uint16_t getSize() { return _size; };

private:
  int8_t    _address;
  uint16_t  _size;   // unknown

  void writeBlock(uint16_t memaddr, uint8_t * obj, uint16_t size);
  void readBlock(uint16_t memaddr, uint8_t * obj, uint16_t size);
};

#endif

// END OF FILE