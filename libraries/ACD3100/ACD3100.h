#pragma once
//
//    FILE: ACD3100.h
//  AUTHOR: Rob Tillaart
//    DATE: 2024-10-29
// VERSION: 0.1.2
// PURPOSE: Arduino library for I2C ACD3100 CO2 sensor
//     URL: https://github.com/RobTillaart/ACD3100
//          http://www.aosong.com/products-220.html


#include "Arduino.h"
#include "Wire.h"


#define ACD3100_LIB_VERSION         (F("0.1.2"))
#define ACD3100_DEFAULT_ADDRESS     0x2A          //  0x54 ?

//  ERROR CODES
//  values <> 0 are errors.
#define ACD3100_OK                  0x00
#define ACD3100_CRC_ERROR           0x01
#define ACD3100_NOT_READY           0x10
#define ACD3100_REQUEST_ERROR       0x11


class ACD3100
{
public:
  ACD3100(TwoWire *wire = &Wire);

  bool     begin();
  bool     isConnected();
  uint8_t  getAddress();


  //       READ
  bool     preHeatDone();
  uint32_t preHeatMillisLeft();

  int      requestSensor();
  bool     requestReady();
  int      readSensor();
  uint32_t getCO2Concentration();
  uint16_t getTemperature();
  uint32_t lastRead();

  void     setRequestTime(uint8_t milliseconds = 80);
  uint8_t  getRequestTime();


  //       CALIBRATION  (! read datasheet)
  bool     setManualCalibration(uint16_t value);
  uint16_t readManualCalibration();


  //       MISCELLANEOUS
  void     factoryReset();
  bool     readFactorySet();
  void     readFirmwareVersion(char * arr);  //  length(arr) > 11
  void     readSensorCode(char * arr);       //  length(arr) > 11


  //       DEBUG
  int      getLastError();


private:
  uint8_t  _address = ACD3100_DEFAULT_ADDRESS;       //  fixed
  TwoWire* _wire;

  int      _command(uint8_t * arr, uint8_t size);
  int      _request(uint8_t * arr, uint8_t size);
  uint8_t  _crc8(uint8_t * arr, uint8_t size);

  uint32_t _preHeatStart;
  uint32_t _lastRead;
  uint32_t _concentration;  //  why datasheet states 32 bit as 400-5000 fit in 16 bit??
  uint16_t _temperature;
  uint8_t  _requestTime;
  uint32_t _requestStart;
  uint8_t  _error;
};


//  -- END OF FILE --

