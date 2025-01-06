#pragma once
//
//    FILE: CHT832X.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: Arduino library for CHT832X temperature and humidity sensor
//     URL: https://github.com/RobTillaart/CHT832X
//


#include "Arduino.h"
#include "Wire.h"


#define CHT832X_LIB_VERSION              (F("0.1.0"))


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
//  #define CHT832X_ERROR_CRC    TODO?


class CHT832X
{
public:
  CHT832X(const uint8_t address = CHT832X_DEFAULT_ADDRESS, TwoWire *wire = &Wire);

  int      begin();
  bool     isConnected();
  uint8_t  getAddress();


  //  read both the temperature and humidity.
  int      read();             //  read T and H from device
  uint32_t lastRead();         //  milliSeconds since start sketch
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
  void    enableHeater();
  void    enableHeaterFull();
  void    enableHeaterHalf();
  void    enableHeaterQuarter();
  void    disableHeater();


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
  uint16_t getNIST(uint8_t id);  //  id = 0,1,2
  uint16_t getManufacturer();    //  expect 0x5959


private:
  float    _humOffset       = 0.0;
  float    _tempOffset      = 0.0;
  float    _humidity        = 0.0;
  float    _temperature     = 0.0;
  uint32_t _lastRead        = 0;
  uint32_t _heatStart       = 0;  //  TODO investigate

  TwoWire* _wire;
  uint8_t  _address         = CHT832X_DEFAULT_ADDRESS;

  int      _readRegister(uint16_t command, uint8_t * buf, uint8_t size);
  int      _writeRegister(uint16_t command, uint8_t * buf, uint8_t size);
};


//  -- END OF FILE --

