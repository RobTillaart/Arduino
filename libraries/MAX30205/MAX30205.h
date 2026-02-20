#pragma once
//
//    FILE: MAX30205.h
//  AUTHOR: Rob Tillaart
//    DATE: 2026-02-19
// VERSION: 0.1.1
// PURPOSE: Arduino library for
//     URL: https://github.com/RobTillaart/MAX30205
//


#include "Arduino.h"
#include "Wire.h"


#define MAX30205_LIB_VERSION         (F("0.1.1"))

//  ERROR CODES
//  values <> 0 are errors.
#define MAX30205_OK                  0x00
#define MAX30205_CRC_ERROR           0x01
#define MAX30205_NOT_READY           0x10
#define MAX30205_REQUEST_ERROR       0x11


class MAX30205
{
public:
  MAX30205(uint8_t address, TwoWire *wire = &Wire);

  bool     begin();
  bool     isConnected();
  uint8_t  getAddress();


  //       READ
  //  read temperature from device
  bool     read();
  //  get temperature from lastRead
  float    getTemperature();
  float    getAccuracy();


  //       CONFIG
  //  read the datasheet for detailed behaviour
  void     setConfig(uint8_t mask = 0x00);
  uint8_t  getConfig();
  void     shutDown();
  void     wakeUp();
  void     setModeComparator();
  void     setModeInterrupt();
  //  polarity = LOW HIGH
  void     setPolarity(uint8_t polarity = LOW);
  //  level = 0..3; see datasheet
  void     setFaultQueLevel(uint8_t level = 0);
  //  range = 0 => 0..50; see dataSheet
  //  range = 1 => extended and slower.
  void     setDataFormat(uint8_t range = 0);
  //  timeout = 0, 1
  void     setTimeout(uint8_t timeout = 0);
  //  one shot versus continuous
  void     setModeContinuous();
  //  OneShot implies shutdown.
  void     setModeOneShot();


  //       HYSTERESIS & OS
  bool     setHysteresis(float Celsius = 75.0f);
  float    getHysteresis();
  bool     setOverTemperature(float Celsius = 80.0f);
  float    getOverTemperature();


  //       DEBUG
  uint32_t lastRead();
  uint16_t lastError();


  //  Public for develop
  uint16_t writeRegister(uint8_t reg, uint16_t value, uint8_t bytes);
  uint16_t readRegister(uint8_t reg, uint8_t bytes);

private:
  uint8_t  _address;
  TwoWire* _wire;

  uint32_t _lastRead;
  uint16_t _temperature;
  uint16_t _error;
};


//  -- END OF FILE --





