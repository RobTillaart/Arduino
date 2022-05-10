#pragma once
//
//    FILE: FRAM.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.4.0
//    DATE: 2018-01-24
// PURPOSE: Arduino library for I2C FRAM
//     URL: https://github.com/RobTillaart/FRAM_I2C
//


#include "Arduino.h"
#include "Wire.h"


#define FRAM_LIB_VERSION              (F("0.4.0"))


#define FRAM_OK                       0
#define FRAM_ERROR_ADDR               -10
#define FRAM_ERROR_I2C                -11
#define FRAM_ERROR_CONNECT            -12

// Size known types
#define FRAM_MB85RC04                 512  
#define FRAM_MB85RC16                2048
#define FRAM_MB85RC64T               8192
#define FRAM_MB85RC128A             16384
#define FRAM_MB85RC256V             32768
#define FRAM_MB85RC512T             65536
#define FRAM_MB85RC1MT             131072


class FRAM
{
public:
  FRAM(TwoWire *wire = &Wire);

#if defined (ESP8266) || defined(ESP32)
  // address and writeProtectPin is optional
  int      begin(uint8_t sda, uint8_t scl, const uint8_t address = 0x50, int8_t writeProtectPin = -1);
#endif
  // address and writeProtectPin is optional
  int      begin(const uint8_t address = 0x50, int8_t writeProtectPin = -1);
  bool     isConnected();

  void     write8(uint16_t memaddr, uint8_t value);
  void     write16(uint16_t memaddr, uint16_t value);
  void     write32(uint16_t memaddr, uint32_t value);
  void     write(uint16_t memaddr, uint8_t * obj, uint16_t size);

  uint8_t  read8(uint16_t memaddr);
  uint16_t read16(uint16_t memaddr);
  uint32_t read32(uint16_t memaddr);
  void     read(uint16_t memaddr, uint8_t * obj, uint16_t size);

  template <class T> uint16_t writeObject(uint16_t memaddr, T &obj)
  {
    write(memaddr, (uint8_t *) &obj, sizeof(obj));
    return memaddr + sizeof(obj);
  };
  template <class T> uint16_t readObject(uint16_t memaddr, T &obj)
  {
    read(memaddr, (uint8_t *) &obj, sizeof(obj));
    return memaddr + sizeof(obj);
  }

  //  works only if pin is defined in begin.
  bool     setWriteProtect(bool b);
  bool     getWriteProtect();

  //  meta info
  uint16_t getManufacturerID();   //  Fujitsu = 0x000A
  uint16_t getProductID();        //  Proprietary
  uint16_t getSize();             //  Returns size in KILO-BYTE (or 0)
  uint32_t getSizeBytes() { return _sizeBytes; };  //  Returns size in BYTE
  void     setSizeBytes(uint32_t value);           //  override when getSize() fails == 0

  uint32_t clear(uint8_t value = 0);  // fills FRAM with value

  //  0.3.6
  void sleep();
  bool wakeup(uint32_t trec = 400);  // trec <= 400us  P12


protected:
  uint8_t  _address;
  uint32_t _sizeBytes;
  //  default no pin = -1 ==> no write protect.
  int8_t   _writeProtectPin = -1;
  TwoWire* _wire;

  uint16_t _getMetaData(uint8_t id);
  void     _writeBlock(uint16_t memaddr, uint8_t * obj, uint8_t size);
  void     _readBlock(uint16_t memaddr, uint8_t * obj, uint8_t size);

};


/////////////////////////////////////////////////////////////////
//
//  FRAM32
//


class FRAM32 : public FRAM
{
public:
  FRAM32(TwoWire *wire = &Wire);

  void     write8(uint32_t memaddr, uint8_t value);
  void     write16(uint32_t memaddr, uint16_t value);
  void     write32(uint32_t memaddr, uint32_t value);
  void     write(uint32_t memaddr, uint8_t * obj, uint16_t size);

  uint8_t  read8(uint32_t memaddr);
  uint16_t read16(uint32_t memaddr);
  uint32_t read32(uint32_t memaddr);
  void     read(uint32_t memaddr, uint8_t * obj, uint16_t size);

  template <class T> uint32_t writeObject(uint32_t memaddr, T &obj)
  {
    write(memaddr, (uint8_t *) &obj, sizeof(obj));
    return memaddr + sizeof(obj);
  };
  template <class T> uint32_t readObject(uint32_t memaddr, T &obj)
  {
    read(memaddr, (uint8_t *) &obj, sizeof(obj));
    return memaddr + sizeof(obj);
  }

  uint32_t clear(uint8_t value = 0);  // fills FRAM with value

protected:
  void     _writeBlock(uint32_t memaddr, uint8_t * obj, uint8_t size);
  void     _readBlock(uint32_t memaddr, uint8_t * obj, uint8_t size);
};


// -- END OF FILE --

