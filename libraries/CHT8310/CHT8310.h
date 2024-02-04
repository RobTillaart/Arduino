#pragma once
//
//    FILE: CHT8310.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: Arduino library for CHT8310 temperature and humidity sensor
//     URL: https://github.com/RobTillaart/CHT8310
//


#include "Arduino.h"
#include "Wire.h"


#define CHT8310_LIB_VERSION              (F("0.1.0"))

//  DEFAULT ADDRESS
#ifndef CHT8310_DEFAULT_ADDRESS
#define CHT8310_DEFAULT_ADDRESS          0x40
#endif

//  ERRORS
#define CHT8310_OK                       0
#define CHT8310_ERROR_ADDR               -10
#define CHT8310_ERROR_I2C                -11
#define CHT8310_ERROR_CONNECT            -12
#define CHT8310_ERROR_LASTREAD           -20

//  REGISTERS
#define CHT8310_REG_TEMPERATURE          0x00
#define CHT8310_REG_HUMIDITY             0x01

#define CHT8310_REG_SWRESET              0xFC
#define CHT8310_REG_MANUFACTURER         0xFF


//  not implemented in 0.1.0
#define CHT8310_REG_STATUS               0x02
#define CHT8310_REG_CONFIG               0x03
#define CHT8310_REG_CONVERT_RATE         0x04
#define CHT8310_REG_TEMP_HIGH_LIMIT      0x05
#define CHT8310_REG_TEMP_LOW_LIMIT       0x06
#define CHT8310_REG_HUM_HIGH_LIMIT       0x07
#define CHT8310_REG_HUM_LOW_LIMIT        0x08
#define CHT8310_REG_ONESHOT              0x0F


//  REGISTER MASKS
//  not implemented in 0.1.0



class CHT8310
{
public:
  //  default address =  AD0 to GND.
  CHT8310(const uint8_t address = CHT8310_DEFAULT_ADDRESS, TwoWire *wire = &Wire);

  int      begin();
  bool     isConnected();
  uint8_t  getAddress();


  //  read both the temperature and humidity.
  int      read();
  //  read only temperature (slightly faster)
  int      readTemperature();
  //  read only humidity (slightly faster)
  int      readHumidity();

  //  lastRead is in MilliSeconds since start sketch
  uint32_t lastRead();
  float    getHumidity();      //  get cached value
  float    getTemperature();   //  get cached value

  //  for read function
  void     setConversionDelay(uint8_t cd = 14);
  uint8_t  getConversionDelay();


  //  adding offsets works well in normal range
  void     setHumidityOffset(float offset);
  //  might introduce under- or overflow at the ends of the sensor range
  void     setTemperatureOffset(float offset);
  float    getHumidityOffset();
  float    getTemperatureOffset();


  //  META DATA
  uint16_t getManufacturer();     //  expect 0x5959

  //  PATCH TO ACCESS REGISTERS
  uint16_t readRegister(uint8_t reg);
  int      writeRegister(uint8_t reg, uint16_t value);
  

private:
  float    _humOffset       = 0.0;
  float    _tempOffset      = 0.0;
  float    _humidity        = 0.0;
  float    _temperature     = 0.0;
  uint32_t _lastRead        = 0;
  uint8_t  _conversionDelay = 14;  //  11  datasheet P8

  uint8_t  _resolution      = 13;  //  configuration register EM

  TwoWire* _wire;
  uint8_t  _address         = CHT8310_DEFAULT_ADDRESS;

  int      _readRegister(uint8_t reg, uint8_t * buf, uint8_t size);
  int      _writeRegister(uint8_t reg, uint8_t * buf, uint8_t size);
};


//  -- END OF FILE --

