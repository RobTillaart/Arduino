#pragma once
//
//    FILE: ACD10.h
//  AUTHOR: Rob Tillaart
//    DATE: 2023-09-25
// VERSION: 0.2.0
// PURPOSE: Arduino library for for I2C ACD10 CO2 sensor
//     URL: https://github.com/RobTillaart/ACD10
//          http://www.aosong.com/en/products-77.html


#include "Arduino.h"
#include "Wire.h"


#define ACD10_LIB_VERSION         (F("0.2.0"))
#define ACD10_DEFAULT_ADDRESS     0x2A

//  ERROR CODES
//  values <> 0 are errors.
#define ACD10_OK                  0x00
#define ACD10_CRC_ERROR           0x01
#define ACD10_NOT_READY           0x10
#define ACD10_REQUEST_ERROR       0x11


class ACD10
{
public:
  ACD10(TwoWire *wire = &Wire);

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
  //       0 = manual  1 = auto
  bool     setCalibrationMode(uint8_t mode);
  uint8_t  readCallibrationMode();
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
  uint8_t  _address = 0x2A;       //  fixed
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





