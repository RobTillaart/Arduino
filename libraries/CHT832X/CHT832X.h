#pragma once
//
//    FILE: CHT832X.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.1
//    DATE: 2024-12-29
// PURPOSE: Arduino library for CHT832X temperature and humidity sensor
//     URL: https://github.com/RobTillaart/CHT832X


#include "Arduino.h"
#include "Wire.h"


#define CHT832X_LIB_VERSION              (F("0.3.1"))

//  CONVERSION TIMING
//  To configure compile time, datasheet states 60 ms for conversion.
const uint8_t CHT832X_READ_DELAY = 60;


//  DEFAULT ADDRESS
#ifndef CHT832X_DEFAULT_ADDRESS
#define CHT832X_DEFAULT_ADDRESS          0x44
#endif


//  ERRORS
#define CHT832X_OK                       0
#define CHT832X_ERROR_ADDR               -10
#define CHT832X_ERROR_I2C                -11
#define CHT832X_ERROR_CONNECT            -12
#define CHT832X_ERROR_LASTREAD           -20
#define CHT832X_ERROR_CRC                -21


class CHT832X
{
public:
  CHT832X(const uint8_t address = CHT832X_DEFAULT_ADDRESS, TwoWire *wire = &Wire);

  int      begin();
  bool     isConnected();
  uint8_t  getAddress();

  //  ASYNC INTERFACE
  int      requestData();   //  triggers single shot conversion
  bool     dataReady();     //  conversion ready
  int      readData();      //  fetch T + H

  //  SYNC INTERFACE
  int      read();             //  read T and H from device; blocks 60 ms.
  uint32_t lastRead();         //  milliSeconds since start sketch

  //  ACCESS last read TEMPERATURE + HUMIDITY
  float    getTemperature();   //  get cached value
  float    getHumidity();      //  get cached value

  //  adding offsets works well in normal range
  //  might introduce under- or overflow at the ends of the sensor range
  void     setHumidityOffset(float offset);
  void     setTemperatureOffset(float offset);
  float    getHumidityOffset();
  float    getTemperatureOffset();

  //  HEATER - datasheet P16/17
  //  not tested, to be investigated
  //  use with care
  //  heater must be disabled when making measurements,
  //  max period?
  void     enableHeater();
  void     enableHeaterFull();
  void     enableHeaterHalf();
  void     enableHeaterQuarter();
  void     disableHeater();

  //  STATUS - datasheet P17
  //
  //  bit 13:   heater status   0 = Heater disabled, 1 = heater enabled
  //  bit  4:   reset detected  0 = no reset, 1 reset since last clearStatus
  //  bit  1:   command status  0 = executed, 1 = not executed
  //  bit  0:   checksum        0 = pass, 1 = fail
  //  other :   reserved
  uint16_t getStatusRegister();
  void     clearStatusRegister();

  //  SOFTWARE RESET
  //  not tested, to be investigated
  void     softwareReset();

  //  META DATA
  //  getNIST() is possibly not unique, see readme.md.
  uint16_t getNIST(uint8_t id);  //  id = 0, 1, 2
  uint16_t getManufacturer();    //  expect 0x5959

  //  ERROR
  int      getError();

protected:
  float    _humOffset       = 0.0f;
  float    _tempOffset      = 0.0f;
  float    _humidity        = 0.0f;
  float    _temperature     = 0.0f;
  uint32_t _lastRead        = 0;
  uint32_t _lastRequest     = 0;
  uint32_t _heatStart       = 0;
  int      _error           = CHT832X_OK;

  TwoWire* _wire;
  uint8_t  _address         = CHT832X_DEFAULT_ADDRESS;


  int      _writeCommand(uint16_t command, uint8_t * buffer = NULL, uint8_t size = 0);
  int      _readBytes(uint8_t * buffer, uint8_t size);


  uint8_t  _crc8(uint16_t data);
};


//////////////////////////////////////////////////////////////////
//
//  DERIVED CLASSES
//
class CHT8320 : public CHT832X
{
public:
  CHT8320(const uint8_t address = CHT832X_DEFAULT_ADDRESS, TwoWire *wire = &Wire);
};

class CHT8325 : public CHT832X
{
public:
  CHT8325(const uint8_t address = CHT832X_DEFAULT_ADDRESS, TwoWire *wire = &Wire);
};


//  -- END OF FILE --

