#pragma once
//
//    FILE: FRAM.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.8.1
//    DATE: 2018-01-24
// PURPOSE: Arduino library for I2C FRAM
//     URL: https://github.com/RobTillaart/FRAM_I2C


#include "Arduino.h"
#include "Wire.h"


#define FRAM_LIB_VERSION              (F("0.8.1"))


#define FRAM_OK                         0
#define FRAM_ERROR_ADDR               -10
#define FRAM_ERROR_I2C                -11
#define FRAM_ERROR_CONNECT            -12

//  Size known types (Fujitsu)
#define FRAM_MB85RC04                 512
#define FRAM_MB85RC16                2048
#define FRAM_MB85RC64T               8192
#define FRAM_MB85RC64V               8192
#define FRAM_MB85RC128A             16384
#define FRAM_MB85RC256V             32768
#define FRAM_MB85RC512T             65536
#define FRAM_MB85RC1MT             131072


class FRAM
{
public:
  FRAM(TwoWire *wire = &Wire);

  //  address and writeProtectPin is optional
  //  user has to call Wire.begin() before FRAM.begin().
  int      begin(const uint8_t address = 0x50,
                 const int8_t writeProtectPin = -1);
  bool     isConnected();


  //  WRITE DATA TYPES
  void     write8(uint16_t memAddr, uint8_t value);
  void     write16(uint16_t memAddr, uint16_t value);
  void     write32(uint16_t memAddr, uint32_t value);
  void     write64(uint16_t memAddr, uint64_t value);
  void     writeFloat(uint16_t memAddr, float value);
  void     writeDouble(uint16_t memAddr, double value);
  void     write(uint16_t memAddr, uint8_t * obj, uint16_t size);

  //  fills FRAM with value, default 0.
  uint32_t clear(uint8_t value = 0);


  //  READ DATA TYPES
  uint8_t  read8(uint16_t memAddr);
  uint16_t read16(uint16_t memAddr);
  uint32_t read32(uint16_t memAddr);
  uint64_t read64(uint16_t memAddr);
  float    readFloat(uint16_t memAddr);
  double   readDouble(uint16_t memAddr);
  void     read(uint16_t memAddr, uint8_t * obj, uint16_t size);


  //  Experimental 0.5.1
  //  readUntil returns length 0.. n of the buffer.
  //  readUntil does NOT include the separator character.
  //  readUntil returns -1 if data does not fit into buffer,
  //  =>  separator not encountered.
  int32_t readUntil(uint16_t memAddr, char * buffer, uint16_t bufferLength, char separator);
  //  readLine returns length 0.. n of the buffer.
  //  readLine does include '\n' as end character.
  //  readLine returns -1 if data does not fit into buffer.
  //  buffer needs one place for end char '\0'.
  int32_t readLine(uint16_t memAddr, char * buffer, uint16_t bufferLength);


  //  template function must be in .h file
  template <class T> uint16_t writeObject(uint16_t memAddr, T &obj)
  {
    write(memAddr, (uint8_t *) &obj, sizeof(obj));
    return memAddr + sizeof(obj);
  };
  template <class T> uint16_t readObject(uint16_t memAddr, T &obj)
  {
    read(memAddr, (uint8_t *) &obj, sizeof(obj));
    return memAddr + sizeof(obj);
  }


  //  WRITEPROTECT
  //  works only if pin is defined in begin().
  bool     setWriteProtect(bool b);
  bool     getWriteProtect();


  //  MEAT INFO
  //  may not work for devices with no deviceID register.
  //  Fujitsu = 0x000A, Ramtron et al = 0x004
  uint16_t getManufacturerID();
  //  Proprietary product ID
  uint16_t getProductID();
  //  virtual so derived classes FRAM9/11 use their implementation.
  //  Returns size in KILO-BYTE (or 0)
  //  Verify for all manufacturers.
  virtual uint16_t getSize();
  //  Returns size in BYTE
  uint32_t getSizeBytes();
  //  override when getSize() fails == 0 (see readme.md)
  void     setSizeBytes(uint32_t value);


  //  SLEEP - 0.3.6
  void sleep();
  //  timeRecover <= 400us  see trec P12
  bool wakeup(uint32_t timeRecover = 400);


protected:
  uint8_t  _address;
  uint32_t _sizeBytes;
  //  default no pin = -1 ==> no write protect.
  int8_t   _writeProtectPin = -1;
  TwoWire* _wire;

  uint32_t      _getMetaData();
  //  virtual so derived classes FRAM9/11 use their implementation.
  virtual void  _writeBlock(uint16_t memAddr, uint8_t * obj, uint8_t size);
  virtual void  _readBlock(uint16_t memAddr, uint8_t * obj, uint8_t size);
};



/////////////////////////////////////////////////////////////////////////////
//
//  FRAM32
//
class FRAM32 : public FRAM
{
public:
  FRAM32(TwoWire *wire = &Wire);

  void     write8(uint32_t memAddr, uint8_t value);
  void     write16(uint32_t memAddr, uint16_t value);
  void     write32(uint32_t memAddr, uint32_t value);
  void     write64(uint32_t memAddr, uint64_t value);
  void     writeFloat(uint32_t memAddr, float value);
  void     writeDouble(uint32_t memAddr, double value);
  void     write(uint32_t memAddr, uint8_t * obj, uint16_t size);


  uint8_t  read8(uint32_t memAddr);
  uint16_t read16(uint32_t memAddr);
  uint32_t read32(uint32_t memAddr);
  uint64_t read64(uint32_t memAddr);
  float    readFloat(uint32_t memAddr);
  double   readDouble(uint32_t memAddr);
  void     read(uint32_t memAddr, uint8_t * obj, uint16_t size);


  //  readUntil returns length 0.. n of the buffer.
  //  readUntil returns -1 if data does not fit into buffer,
  //  =>  separator not encountered.
  int32_t readUntil(uint32_t memAddr, char * buffer, uint16_t bufferLength, char separator);
  //  buffer needs one place for end char '\0'.
  int32_t readLine(uint32_t memAddr, char * buffer, uint16_t bufferLength);


  //  template function must be in .h file
  template <class T> uint32_t writeObject(uint32_t memAddr, T &obj)
  {
    write(memAddr, (uint8_t *) &obj, sizeof(obj));
    return memAddr + sizeof(obj);
  };

  template <class T> uint32_t readObject(uint32_t memAddr, T &obj)
  {
    read(memAddr, (uint8_t *) &obj, sizeof(obj));
    return memAddr + sizeof(obj);
  }

  uint32_t clear(uint8_t value = 0);  // fills FRAM with value


protected:
  void     _writeBlock(uint32_t memAddr, uint8_t * obj, uint8_t size);
  void     _readBlock(uint32_t memAddr, uint8_t * obj, uint8_t size);
};



/////////////////////////////////////////////////////////////////////////////
//
//  FRAM11  for FRAM that use 11 bits addresses - e.g. MB85RC16
//
class FRAM11 : public FRAM
{
public:
  FRAM11(TwoWire *wire = &Wire);

  //  address and writeProtectPin is optional
  int      begin(const uint8_t address = 0x50,
                 const int8_t writeProtectPin = -1);

  uint16_t getSize();


protected:
  void     _writeBlock(uint16_t memAddr, uint8_t * obj, uint8_t size);
  void     _readBlock(uint16_t memAddr, uint8_t * obj, uint8_t size);
};



/////////////////////////////////////////////////////////////////////////////
//
//  FRAM9  for FRAM that use 9 bits addresses - e.g. MB85RC04
//
class FRAM9 : public FRAM
{
public:
  FRAM9(TwoWire *wire = &Wire);

  //  address and writeProtectPin is optional
  int      begin(const uint8_t address = 0x50,
                 const int8_t writeProtectPin = -1);

  uint16_t getSize();


protected:
  void     _writeBlock(uint16_t memAddr, uint8_t * obj, uint8_t size);
  void     _readBlock(uint16_t memAddr, uint8_t * obj, uint8_t size);
};


//  -- END OF FILE --

