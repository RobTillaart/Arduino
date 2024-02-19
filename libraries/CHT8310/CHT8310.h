#pragma once
//
//    FILE: CHT8310.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.0
// PURPOSE: Arduino library for CHT8310 temperature and humidity sensor
//     URL: https://github.com/RobTillaart/CHT8310
//


#include "Arduino.h"
#include "Wire.h"


#define CHT8310_LIB_VERSION              (F("0.2.0"))


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
#define CHT8310_ERROR_HUMIDITY           -30


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
  float    getTemperature();   //  get cached value
  float    getHumidity();      //  get cached value

  //  (not functional yet)
  void     setConversionDelay(uint8_t cd = 14);
  uint8_t  getConversionDelay();


  //  adding offsets works well in normal range
  //  might introduce under- or overflow at the ends of the sensor range
  void     setHumidityOffset(float offset);
  void     setTemperatureOffset(float offset);
  float    getHumidityOffset();
  float    getTemperatureOffset();


  //  CONFIGURATION (elementary, see datasheet for bits);
  void     setConfiguration(uint16_t mask);
  uint16_t getConfiguration();  // returns mask


  //  CONVERT RATE
  void     setConvertRate(uint8_t rate = 4);
  uint8_t  getConvertRate();


  //  ALERT (not tested, under development)
  void     setTemperatureHighLimit(float temperature);
  void     setTemperatureLowLimit(float temperature);
  void     setHumidityHighLimit(float humidity);
  void     setHumidityLowLimit(float humidity);


  //  STATUS (not tested, under development)
  uint16_t getStatusRegister();


  //  ONE SHOT (not tested, under development)
  void     oneShotConversion();


  //  SOFTWARE RESET (not tested, under development)
  void     softwareReset();


  //  META DATA
  uint16_t getManufacturer();  //  expect 0x5959


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

