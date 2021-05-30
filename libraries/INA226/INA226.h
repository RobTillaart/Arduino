#pragma once
//    FILE: INA266.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2021-05-18
// PURPOSE: Arduino library for INA266 power sensor
//     URL: https://github.com/RobTillaart/INA226
//
//  Read the datasheet for the details
//


#include "Arduino.h"
#include "Wire.h"


#define INA226_LIB_VERSION         (F("0.1.0"))


// set by setAlertRegister
#define INA226_SHUNT_OVER_VOLTAGE        0x8000
#define INA226_SHUNT_UNDER_VOLTAGE       0x4000
#define INA226_BUS_OVER_VOLTAGE          0x2000
#define INA226_BUS_UNDER_VOLTAGE         0x1000
#define INA226_POWER_OVER_LIMIT          0x0800
#define INA226_CONVERSION_READY          0x0400

// returned by getAlertFlag
#define INA226_ALERT_FUNCTION_FLAG       0x0010
#define INA226_CONVERSION_READY_FLAG     0x0008
#define INA226_MATH_OVERFLOW_FLAG        0x0004
#define INA226_ALERT_POLARITY_FLAG       0x0002
#define INA226_ALERT_LATCH_ENABLE_FLAG   0x0001


class INA226
{
public:
  // address between 0x40 and 0x4F
  explicit INA226(const int8_t address, TwoWire *wire = &Wire);

#if defined (ESP8266) || defined(ESP32)
  bool     begin(const uint8_t sda, const uint8_t scl);
#endif

  bool     begin();
  bool     isConnected();

  // Core functions
  float    getShuntVoltage();
  float    getBusVoltage();
  float    getPower();
  float    getCurrent();

  // Configuration
  void     reset();
  void     setAverage(uint8_t avg = 0);
  uint8_t  getAverage();
  void     setBusVoltageConversionTime(uint8_t bvct = 4);
  uint8_t  getBusVoltageConversionTime();
  void     setShuntVoltageConversionTime(uint8_t svct = 4);
  uint8_t  getShuntVoltageConversionTime();

  // Calibration
  void     setMaxCurrentShunt(float ampere = 10.0, float ohm = 0.1);
  float    getCurrentLSB() { return _current_LSB; };


  // Operating mode
  void     setMode(uint8_t mode = 7);
  uint8_t  getMode();
  void     shutDown()                  { setMode(0); };
  void     setModeShuntTrigger()       { setMode(1); };
  void     setModeBusTrigger()         { setMode(2); };
  void     setModeShuntBusTrigger()    { setMode(3); };
  void     setModeShuntContinuous()    { setMode(5); };
  void     setModeBusContinuous()      { setMode(6); };
  void     setModeShuntBusContinuous() { setMode(7); };  // default.


  // Alert
  // - separate functions per flag?
  // - what is a reasonable limit?
  // - which units to define a limit per mask ?
  //   same as voltage registers ?
  // - how to test 
  void     setAlertRegister(uint16_t mask);
  uint16_t getAlertFlag();
  void     setAlertLimit(uint16_t limit);
  uint16_t getAlertLimit();


  // Meta information
  uint16_t getManufacturerID();   // should return 0x5449
  uint16_t getDieID();            // should return 0x2260


private:

  uint16_t _readRegister(uint8_t reg);
  uint16_t _writeRegister(uint8_t reg, uint16_t value);
  float    _current_LSB;

  uint8_t   _address;
  TwoWire * _wire;

};

// -- END OF FILE --
