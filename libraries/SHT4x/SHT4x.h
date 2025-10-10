#pragma once
//
//    FILE: SHT4x.h
//  AUTHOR: Samuel Cuerrier Auclair
//  AUTHOR: Rob Tillaart
// VERSION: 0.0.3
//    DATE: 2025-08-11
// PURPOSE: Arduino library for the SHT4x temperature and humidity sensor. High precision sensor with I2C interface.
//          This is a fork of the SHT31 library by Rob Tillaart, modified to work with the SHT4x series.
//          https://www.adafruit.com/product/2857
//     URL: https://github.com/RobTillaart/SHT4x


#include "Arduino.h"
#include "Wire.h"


#define SHT4x_LIB_VERSION                   (F("0.0.3"))

#ifndef SHT_DEFAULT_ADDRESS
#define SHT_DEFAULT_ADDRESS                 0x44
#endif

// SHT4x measurement commands
typedef enum
{
  SHT4x_MEASUREMENT_SLOW                    = 0xFD,
  SHT4x_MEASUREMENT_MEDIUM                  = 0xF6,
  SHT4x_MEASUREMENT_FAST                    = 0xE0,
  // SHT4x measurement commands with heater on
  SHT4x_MEASUREMENT_LONG_HIGH_HEAT          = 0x39,
  SHT4x_MEASUREMENT_SHORT_HIGH_HEAT         = 0x32,
  SHT4x_MEASUREMENT_LONG_MEDIUM_HEAT        = 0x2F,
  SHT4x_MEASUREMENT_SHORT_MEDIUM_HEAT       = 0x24,
  SHT4x_MEASUREMENT_LONG_LOW_HEAT           = 0x1E,
  SHT4x_MEASUREMENT_SHORT_LOW_HEAT          = 0x15
} measType;

//  error codes
#define SHT4x_OK                            0x00
#define SHT4x_ERR_WRITECMD                  0x81
#define SHT4x_ERR_READBYTES                 0x82
#define SHT4x_ERR_HEATER_OFF                0x83
#define SHT4x_ERR_NOT_CONNECT               0x84
#define SHT4x_ERR_CRC_TEMP                  0x85
#define SHT4x_ERR_CRC_HUM                   0x86
#define SHT4x_ERR_CRC_STATUS                0x87
#define SHT4x_ERR_HEATER_COOLDOWN           0x88
#define SHT4x_ERR_HEATER_ON                 0x89
#define SHT4x_ERR_SERIAL_NUMBER_CRC         0x8A
#define SHT4x_ERR_INVALID_ADDRESS           0x8B


class SHT4x
{
public:
  SHT4x(uint8_t address = SHT_DEFAULT_ADDRESS, TwoWire *wire = &Wire);

  bool begin();
  uint8_t getAddress();
  //  check sensor is reachable over I2C
  virtual bool isConnected();

  //  blocks for the required time and read after
  bool read(measType measurementType = SHT4x_MEASUREMENT_SLOW, bool CRCCheck = true);

  //  lastRead is in milliSeconds since start
  uint32_t lastRead();

  bool reset(bool fast = false);

  //  getHumidity returns 0..100%
  float getHumidity();
  //  getTemperature returns degrees Celsius
  float getTemperature();
  float getFahrenheit();
  //  raw data e.g. debugging or efficient logging / transmit.
  uint16_t getRawHumidity();
  uint16_t getRawTemperature();


  //  ASYNC INTERFACE
  bool requestData(measType measurementType = SHT4x_MEASUREMENT_SLOW);
  bool dataReady();
  bool readData(bool CRCCheck = true);

  //  MISC
  int getError();  //  clears error flag
  //  CRCCheck == false, => skips CRC check
  bool getSerialNumber(uint32_t &serial, bool CRCCheck = true);

  //  Heat protection
  bool heatingReady();
  void setHeatProtection(bool activateHeatProtection);


protected:
  uint8_t  _address;
  uint16_t _delay;
  uint32_t _lastRead;
  //        for async interface
  uint32_t _lastRequest;

  //        for overheating protection
  uint16_t _heatInterval;
  uint32_t _lastHeatRequest;

  uint16_t _rawHumidity;
  uint16_t _rawTemperature;
  uint8_t  _error;
  bool     _heatProtection;

  void     setDelay(measType measurementType);

  //       for overheating protection
  bool     isHeatCmd(measType measurementType);
  void     setHeatInterval(measType measurementType);

  uint8_t  crc8(const uint8_t *data, uint8_t length);
  virtual bool writeCommand(uint8_t command);
  virtual bool readBytes(uint8_t length, uint8_t *data);
  TwoWire* _wire;
};


//  -- END OF FILE --